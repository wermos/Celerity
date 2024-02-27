#include "imageWriters/imageWriter.hpp"

imageWriter::imageWriter(const std::size_t imageWidth, const std::size_t imageHeight) :
	m_imageWidth(imageWidth), m_imageHeight(imageHeight),
	m_strideInBytes(static_cast<int>(m_imageWidth * m_pngComp)),
	m_jpgData(new uint8_t[m_imageWidth * m_imageHeight * m_jpgComp]),
	m_pngData(new uint8_t[m_imageWidth * m_imageHeight * m_pngComp]),
	m_jpgDataCounter(0), m_pngDataCounter(0)
	{}

imageWriter::~imageWriter() {
	delete[] m_jpgData;
	delete[] m_pngData;
}
