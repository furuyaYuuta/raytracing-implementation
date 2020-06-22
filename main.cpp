
#include <iostream>
#include <random>

#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "hitableList.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "randomUtils.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

using namespace std;

class Image {
	int width, height;
	uint8_t *data;
public:
	Image(int width, int height) {
		this->width = width;
		this->height = height;
		data = new uint8_t[width * height * 3];
	}
	void setPixel(int x, int y, int r, int g, int b) {
		data[3 * (width * y + x)] 	  = (uint8_t)r;
		data[3 * (width * y + x) + 1] = (uint8_t)g;
		data[3 * (width * y + x) + 2] = (uint8_t)b;
	}
	void writeImage() const {
		stbi_write_png("image.png", width, height, 3, data, 3 * width);
	}
};

vec3 getColor(const Ray& ray, Hitable *world, int depth) {
	hit_record record;
	if(world->hit(ray, 0.001, numeric_limits<float>::max(), record)) {
		Ray scattered;
		vec3 attenuation;
		if(depth < 50 && record.mat_ptr->scatter(ray, record, attenuation, scattered))
			return attenuation * getColor(scattered, world, depth + 1);
		else
			return vec3();
	} else {
		vec3 unitDirection = unit_vector(ray.getDirection());
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

Hitable *randomScene() {
	int n = 500;
	Hitable **list = new Hitable*[n+1];
	list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));
	int idx = 1;
	for(int i = -7; i < 7; i++) {
		for(int j = -7; j < 7; j++) {
			float matProb = randomFloat(0.0, 1.0);
			vec3 center(i + randomFloat(0.0, 0.9), 0.2, j + randomFloat(0.0, 0.9));
			if((center - vec3(4, 0.2f, 0)).length() > 0.9) {
				if(matProb < 0.8) {
					float rAlbedo = randomFloat(0.0, 1.0) * randomFloat(0.0, 1.0);
					float gAlbedo = randomFloat(0.0, 1.0) * randomFloat(0.0, 1.0);
					float bAlbedo = randomFloat(0.0, 1.0) * randomFloat(0.0, 1.0);
					list[idx++] = new Sphere(center, 0.2, new Lambertian(vec3(rAlbedo, gAlbedo, bAlbedo)));
				} else if(matProb < 0.95) {
					float rAlbedo = randomFloat(0.0f, 1.0f);
					float gAlbedo = randomFloat(0.0f, 1.0f);
					float bAlbedo = randomFloat(0.0f, 1.0f);
					list[idx++] = new Sphere(center, 0.2, new Metal(vec3(rAlbedo, gAlbedo, bAlbedo)));
				} else list[idx++] = new Sphere(center, 0.2, new Dielectric(1.5));
			}
		}
	}
	list[idx++] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[idx++] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)));
	list[idx++] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5)));

	return new HitableList(list, idx);
}

int main() {
	int nx = 1200, ny = 600;
	int ns = 30;
	Image image(nx, ny);

//	vec3 lookFrom(3, 3, 2);
//	vec3 lookAt(0, 0, -1);
//	float distToFocus = (lookFrom - lookAt).length();
//	float aperture = 1.0;
//	Camera camera(lookFrom, lookAt, vec3(0, 1, 0), 20, float(nx)/float(ny), aperture, distToFocus);
//	Hitable *list[5];
//	list[0] = new Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(vec3(0.8, 0.3, 0.3)));
//	list[1] = new Sphere(vec3(0.0f, -100.5f, -1.0f), 100, new Lambertian(vec3(0.8, 0.8, 0.0)));
//	list[2] = new Sphere(vec3(1.0f, 0.0f, -1.0f), 0.4f, new Metal(vec3(0.8, 0.6, 0.2)));
//	list[3] = new Sphere(vec3(-1.0f, 0.0f, -1.0f), 0.4f, new Dielectric(1.5));
//	list[4] = new Sphere(vec3(-1.0f, 0.0f, -1.0f), -0.35f, new Dielectric(1.5));
//	Hitable *world = new HitableList(list, 5);

    const vec3 lookFrom(13, 2, 3);
    const vec3 lookAt(0, 0, 0);
    const vec3 lookUp(0, 1, 0);
    const float distToFocus = (lookFrom - lookAt).length();
    const float aperture = 0.1;
    Camera camera(lookFrom, lookAt, lookUp, 20, float(nx)/float(ny), aperture, distToFocus);
    Hitable *world = randomScene();

	int i, j, count = 0;
	#pragma omp parallel for private(i)
	for(j = ny - 1; j >= 0; j--) {
		for(i = 0; i < nx; i++) {
			vec3 color = vec3();
			for(int s = 0; s < ns; s++) {
				float u = (i + randomFloat(0.0f, 1.0f)) / float(nx);
				float v = (j + randomFloat(0.0f, 1.0f)) / float(ny);
				Ray ray = camera.getRay(u, v);
				color += getColor(ray, world, 0);
			}
			color /= float(ns);
			sqrt(color);
			int ir = int(255.99 * color.r());
			int ig = int(255.99 * color.g());
			int ib = int(255.99 * color.b());
			image.setPixel(i, ny - j - 1, ir, ig, ib);
		}
		if(j % 4 == 0)
			printf("%.lf%%\n", (double)(count+=4)/ny*100);
	}
	image.writeImage();

	return 0;
}