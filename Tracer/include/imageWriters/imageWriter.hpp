#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <iostream>
#include <string>

#include "color.hpp"
#include "stb_image_write.h"

class imageWriter {
	public:
		imageWriter(const int imageWidth, const int imageHeight);

		void writeToPNG(const color c) {
			m_pngData[m_pngDataCounter++] = static_cast<unsigned char>(c.r());
			m_pngData[m_pngDataCounter++] = static_cast<unsigned char>(c.g());
			m_pngData[m_pngDataCounter++] = static_cast<unsigned char>(c.b());
			// m_pngDataCounter += 3;
		}

		void writeToJPG(const color c) {
			m_jpgData[m_jpgDataCounter++] = static_cast<unsigned char>(c.r());
			m_jpgData[m_jpgDataCounter++] = static_cast<unsigned char>(c.g());
			m_jpgData[m_jpgDataCounter++] = static_cast<unsigned char>(c.b());
			// m_jpgDataCounter += 3;
		}

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

		unsigned char* const m_jpgData;
		unsigned char* const m_pngData;
		int m_jpgDataCounter, m_pngDataCounter;
};

#endif // IMAGE_WRITER_HPP
