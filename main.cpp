
#include <iostream>
#include <limits>
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

vec3 getColor(const Ray& ray, Hitable *world) {
	hit_record record;
	if(world->hit(ray, 0.0, numeric_limits<float>::max(), record)) {
		return 0.5 * (record.normal + vec3(1.0, 1.0, 1.0));
	} else {
		vec3 unitDirection = unit_vector(ray.getDirection());
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	int nx = 800, ny = 400;
	int ns = 100;
	Image image(nx, ny);

	Camera camera;
	Hitable *list[2];
	list[0] = new Sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new Sphere(vec3(0.0, -100.5, -1.0), 100);
	Hitable *world = new HitableList(list, 2);

	for(int j = ny - 1; j >= 0; j--) {
		for(int i = 0; i < nx; i++) {
			vec3 color = vec3();
			for(int s = 0; s < ns; s++) {
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);
				Ray ray = camera.getRay(u, v);
				vec3 p = ray.point_at_parameter(2.0);
				color += getColor(ray, world);
			}
			color /= float(ns);
			int ir = int(255.99 * color.r());
			int ig = int(255.99 * color.g());
			int ib = int(255.99 * color.b());
			image.setPixel(i, ny - j - 1, ir, ig, ib);
		}
	}
	image.writeImage();

	return 0;
}