#include "imageWriters/imageWriter.hpp"

ImageWriter::ImageWriter(const std::size_t imageWidth,
                         const std::size_t imageHeight)
    : m_imageWidth(imageWidth),
      m_imageHeight(imageHeight),
      m_strideInBytes(static_cast<int>(m_imageWidth * m_pngComp)),
      m_imgData(new uint8_t[m_imageWidth * m_imageHeight * m_pngComp]),
      m_imgDataCounter(0) {}

ImageWriter::~ImageWriter() {
    delete[] m_imgData;
}
