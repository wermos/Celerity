#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <string>

#include "color.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

class imageWriter {
	public:
		imageWriter(int imageWidth, int imageHeight);

		inline void write(color c);
		inline void write(int r, int g, int b);

	private:
		//Image File Data
		const int jpgComp = 3; //number of channels in the JPG image
		const int pngComp = 3; //number of channels in the PNG image
		const std::string jpgFileName = "pic.jpg";
		const std::string pngFileName = "pic.png";
		const int strideInBytes = sizeof(unsigned char) * imageWidth * imageHeight;

		unsigned char jpgData[imageWidth * imageHeight * jpgComp];
		unsigned char pngData[imageWidth * imageHeight * pngComp];
};

#endif // IMAGE_WRITER_HPP
