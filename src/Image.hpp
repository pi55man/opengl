#pragma once
#include <stb_image.h>
#include <iostream>
class Image{
private:
	int nrChannels, dChannels;
	const char* filename;
public:
	int width, height;
	Image(const char* filename, int dChannels);
	unsigned char* load();

};
