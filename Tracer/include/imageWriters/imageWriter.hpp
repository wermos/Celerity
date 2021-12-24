#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <iostream>
#include <string>

#include "color.hpp"
#include "stb_image_write.h"

class imageWriter {
	public:
		imageWriter(const int imageWidth, const int imageHeight);

		void writeToPNGBuffer(const color c) {
			m_pngData[m_pngDataCounter++] = static_cast<uint8_t>(c.r());
			m_pngData[m_pngDataCounter++] = static_cast<uint8_t>(c.g());
			m_pngData[m_pngDataCounter++] = static_cast<uint8_t>(c.b());
		}

		void writeToJPGBuffer(const color c) {
			m_jpgData[m_jpgDataCounter++] = static_cast<uint8_t>(c.r());
			m_jpgData[m_jpgDataCounter++] = static_cast<uint8_t>(c.g());
			m_jpgData[m_jpgDataCounter++] = static_cast<uint8_t>(c.b());
		}

		//TODO: Explore the stbi_write_png_func and stbi_write_jpg_func functions
		//which might not require having the entire image in memory while writing
		//it.
		int writePNG() {
			return stbi_write_png(m_pngFileName.c_str(), m_imageWidth,
								  m_imageHeight, m_pngComp, m_pngData, m_strideInBytes);
		}

		int writeJPG() {
			return stbi_write_jpg(m_jpgFileName.c_str(), m_imageWidth,
								  m_imageHeight, m_jpgComp, m_jpgData, 80);
		}

		~imageWriter();
	private:
		//Image File Data
		const int m_jpgComp = 3; //number of channels in the JPG image
		const int m_pngComp = 3; //number of channels in the PNG image
		const int m_imageWidth, m_imageHeight;

		const std::string m_jpgFileName = "pic.jpg";
		const std::string m_pngFileName = "pic.png";
		const int m_strideInBytes;

		//Constant pointer to non-const data
		uint8_t* const m_jpgData;
		uint8_t* const m_pngData;

		int m_jpgDataCounter, m_pngDataCounter;
};

#endif // IMAGE_WRITER_HPP
