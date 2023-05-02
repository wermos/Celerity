#include "imageWriter.hpp"

#include <fstream>

ImageWriter::ImageWriter(const int imageWidth, const int imageHeight)
    : m_imgWidth(imageWidth),
      m_imgHeight(imageHeight),
      m_strideInBytes(m_imgWidth * m_imgComp),
      m_imgData(new uint8_t[m_imgWidth * m_imgHeight * m_imgComp]),
      m_imgDataCounter(0) {}

void ImageWriter::writeToImageBuffer(const color c) {
    m_imgData[m_imgDataCounter++] = static_cast<uint8_t>(c.r());
    m_imgData[m_imgDataCounter++] = static_cast<uint8_t>(c.g());
    m_imgData[m_imgDataCounter++] = static_cast<uint8_t>(c.b());
}

void ImageWriter::writeToImageBuffer(int index, const color c) {
    m_imgData[index++] = static_cast<uint8_t>(c.r());
    m_imgData[index++] = static_cast<uint8_t>(c.g());
    m_imgData[index] = static_cast<uint8_t>(c.b());
}

// TODO: Explore the stbi_write_png_func and stbi_write_jpg_func functions
// which might not require having the entire image in memory while writing
// it.
void ImageWriter::writeToPNGFile(const std::string& filename /* = "pic.png" */) {
    int returnValue = stbi_write_png(filename.c_str(), m_imgWidth, m_imgHeight,
                          m_imgComp, m_imgData, m_strideInBytes);
	
	if (returnValue != 0) {
			std::cout << "PNG Image generated successfully.\n";
		} else {
			std::cout << "An error occurred while generating the PNG image.\n";
		}
}

void ImageWriter::writeToJPGFile(const std::string& filename /* = "pic.jpg" */) {
    int returnValue = stbi_write_jpg(filename.c_str(), m_imgWidth, m_imgHeight,
                          m_imgComp, m_imgData, 80);

	if (returnValue != 0) {
			std::cout << "PNG Image generated successfully.\n";
		} else {
			std::cout << "An error occurred while generating the PNG image.\n";
		}
}

void ImageWriter::writeToPPMFile(const std::string& filename /* = "pic.ppm" */) {
	/**
	 * PPM files must have the following information:
	 * 
	 * P3
	 * <width> <height>
	 * <max value of color>
	 *
	 * where "P3" tells the viewer that the colors are in ASCII
	 * <width> tells the viewer how many columns there are in the picture,
	 * <height> tells the viewer how many rows, and <max value of color>
	 * tells the image viewer how to normalize the color values
	 */
	std::ofstream file;

	file.open(filename, std::ofstream::out | std::ofstream::trunc);

	if (!file.good()) {
		std::cerr << "Error opening file. Aborting...\n";
	}

	file << "P3\n" << m_imgWidth << ' ' << m_imgHeight << "\n255\n";

	for (int i = 0; i < m_imgWidth * m_imgHeight * m_imgComp; i += 3) {
		file << m_imgData[i] << m_imgData[i + 1] << m_imgData[i + 2] << '\n';
	}

	file.close();
}

ImageWriter::~ImageWriter() { delete[] m_imgData; }
