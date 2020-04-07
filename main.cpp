
#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"

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

vec3 getColor(const Ray& ray) {
	vec3 unitDirection = unit_vector(ray.getDirection());
	float t = 0.5f * (unitDirection.y() + 1.0f);
	return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
	int nx = 800, ny = 400;
	Image image(nx, ny);

	vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for(int j = ny - 1; j >= 0; j--) {
		for(int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
			vec3 color = getColor(ray);
			int ir = int(255.99 * color.r());
			int ig = int(255.99 * color.g());
			int ib = int(255.99 * color.b());
			image.setPixel(i, ny - j - 1, ir, ig, ib);
		}
	}
	image.writeImage();

	return 0;
}