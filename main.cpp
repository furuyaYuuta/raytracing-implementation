
#include <iostream>
#include <random>

#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "hitableList.hpp"
#include "sphere.hpp"
#include "camera.hpp"

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

int main() {
	int nx = 800, ny = 400;
	int ns = 50;
	Image image(nx, ny);

	Camera camera;
	Hitable *list[4];
	list[0] = new Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5, new Lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new Sphere(vec3(0.0f, -100.5f, -1.0f), 100, new Lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new Sphere(vec3(1.0f, 0.0f, -1.0f), 0.4, new Metal(vec3(0.8, 0.6, 0.2)));
	list[3] = new Sphere(vec3(-1.0f, 0.0f, -1.0f), 0.4, new Metal(vec3(0.8, 0.8, 0.8)));
	Hitable *world = new HitableList(list, 4);

	int i, j, count = 0;
	#pragma omp parallel for private(i)
	for(j = ny - 1; j >= 0; j--) {
		for(i = 0; i < nx; i++) {
			vec3 color = vec3();
			for(int s = 0; s < ns; s++) {
				float u = (i + randomFloat(0.0f, 1.0f)) / float(nx);
				float v = (j + randomFloat(0.0f, 1.0f)) / float(ny);
				Ray ray = camera.getRay(u, v);
//				vec3 p = ray.point_at_parameter(2.0);
				color += getColor(ray, world, 0);
			}
			color /= float(ns);
			sqrt(color);
			int ir = int(255.99 * color.r());
			int ig = int(255.99 * color.g());
			int ib = int(255.99 * color.b());
			image.setPixel(i, ny - j - 1, ir, ig, ib);
		}
		if(j % 20 == 0)
			printf("%.lf%%\n", (double)(count+=20)/ny*100);
	}
	image.writeImage();

	return 0;
}