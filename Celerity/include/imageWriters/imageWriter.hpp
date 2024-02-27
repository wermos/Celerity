#pragma once

#include <cstddef>
#include <string>

#include "color.hpp"
#include "stb_image_write.h"

class imageWriter {
   public:
    imageWriter(const std::size_t imageWidth, const std::size_t imageHeight);

    void writeToPNGBuffer(const color c) {
        m_pngData[m_pngDataCounter++] = static_cast<uint8_t>(c.r());
        m_pngData[m_pngDataCounter++] = static_cast<uint8_t>(c.g());
        m_pngData[m_pngDataCounter++] = static_cast<uint8_t>(c.b());
    }

    void writeToPNGBuffer(std::size_t idx, const color c) {
        m_pngData[idx++] = static_cast<uint8_t>(c.r());
        m_pngData[idx++] = static_cast<uint8_t>(c.g());
        m_pngData[idx] = static_cast<uint8_t>(c.b());
    }

    void writeToJPGBuffer(const color c) {
        m_jpgData[m_jpgDataCounter++] = static_cast<uint8_t>(c.r());
        m_jpgData[m_jpgDataCounter++] = static_cast<uint8_t>(c.g());
        m_jpgData[m_jpgDataCounter++] = static_cast<uint8_t>(c.b());
    }

    void writeToJPGBuffer(std::size_t idx, const color c) {
        m_jpgData[idx++] = static_cast<uint8_t>(c.r());
        m_jpgData[idx++] = static_cast<uint8_t>(c.g());
        m_jpgData[idx] = static_cast<uint8_t>(c.b());
    }

    // TODO: Explore the stbi_write_png_func and stbi_write_jpg_func functions
    // which might not require having the entire image in memory while writing
    // it.
    int writePNG() {
        return stbi_write_png(m_pngFileName.c_str(),
                              static_cast<int>(m_imageWidth),
                              static_cast<int>(m_imageHeight), m_pngComp,
                              m_pngData, m_strideInBytes);
    }

    int writeJPG() {
        return stbi_write_jpg(
            m_jpgFileName.c_str(), static_cast<int>(m_imageWidth),
            static_cast<int>(m_imageHeight), m_jpgComp, m_jpgData, 80);
    }

    ~imageWriter();

   private:
    // Image File Data

    // number of channels in the JPG image
    static constexpr int m_jpgComp = 3;
    // number of channels in the PNG image
    static constexpr int m_pngComp = 3;
    const std::size_t m_imageWidth;
    const std::size_t m_imageHeight;

    static constexpr std::string m_jpgFileName{"pic.jpg"};
    static constexpr std::string m_pngFileName{"pic.png"};
    const int m_strideInBytes;

    // Constant pointer to non-const data
    uint8_t *const m_jpgData;
    uint8_t *const m_pngData;

    std::size_t m_jpgDataCounter, m_pngDataCounter;
};
