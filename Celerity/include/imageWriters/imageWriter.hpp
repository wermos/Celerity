#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <iostream>
#include <string>

#include "color.hpp"
#include "stb_image_write.h"

class ImageWriter {
	public:
		ImageWriter(const int imageWidth, const int imageHeight);

		void writeToImageBuffer(const color c);

		void writeToImageBuffer(int index, const color c);

		// TODO: Explore the stbi_write_png_func and stbi_write_jpg_func functions
		// which might not require having the entire image in memory while writing
		// it.
		void writeToPNGFile(const std::string& filename = "pic.png");

		void writeToJPGFile(const std::string& filename = "pic.jpg");

		void writeToPPMFile(const std::string& filename = "pic.ppm");

		~ImageWriter();
	private:
		// Image File Data
		const int m_imgComp = 3; // number of channels in the image
		const int m_imgWidth, m_imgHeight;
		const int m_strideInBytes;

		// Constant pointer to non-const data
		uint8_t* const m_imgData;

		int m_imgDataCounter;
};

#endif // IMAGE_WRITER_HPP
