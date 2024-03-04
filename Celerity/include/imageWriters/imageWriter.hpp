#pragma once

#include <cstddef>
#include <fstream>
#include <string>

#include "color.hpp"
#include "stb_image_write.h"

// TODO: Add support for RGBA PNG images, and HDR images.
// 
// Currently, the class only supports 3 channel PNGs and JPGs, and binary PPM
// images.
class ImageWriter {
   public:
    ImageWriter(const std::size_t imageWidth, const std::size_t imageHeight);

    void addPixel(const color c) {
        m_imgData[m_imgDataCounter++] = static_cast<std::uint8_t>(c.r());
        m_imgData[m_imgDataCounter++] = static_cast<std::uint8_t>(c.g());
        m_imgData[m_imgDataCounter++] = static_cast<std::uint8_t>(c.b());
    }

    void addPixel(std::size_t idx, const color c) {
        m_imgData[idx++] = static_cast<std::uint8_t>(c.r());
        m_imgData[idx++] = static_cast<std::uint8_t>(c.g());
        m_imgData[idx] = static_cast<std::uint8_t>(c.b());
    }

    int writePNG() {
        // `stbi_write_png` returns 0 on failure and non-0 on success.
        // TODO: Finish the comment
        int result = stbi_write_png(m_pngFileName.c_str(),
                              static_cast<int>(m_imageWidth),
                              static_cast<int>(m_imageHeight), m_pngComp,
                              m_imgData, m_strideInBytes);
        
        if (result == 0) {
            return -1;
        } else {
            return 0;
        }
    }

    int writeJPG() {
        int result = stbi_write_jpg(
            m_jpgFileName.c_str(), static_cast<int>(m_imageWidth),
            static_cast<int>(m_imageHeight), m_jpgComp, m_imgData, 80);
        
        if (result == 0) {
            return -1;
        } else {
            return 0;
        }
    }

    int writePPM() {
        /**
        * PPM Format:
        *
        * P3
        * <width> <height>
        * <max value of color>
        *
        * where "P3" tells the viewer that the colors are in ASCII
        * <width> tells the viewer how many columns there are in the picture,
        * <height> tells the viewer how many rows, and
        * <max value of color> tells the viewer how to normalize the color values
        */

        std::ofstream m_file(m_ppmFileName, std::ofstream::out | std::ofstream::trunc);

        if (m_file.good()) {
            m_file << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

            for (std::size_t i = 0; i < 3 * m_imageHeight * m_imageWidth; i += 3) {
                m_file << static_cast<int>(m_imgData[i]) << ' '
                       << static_cast<int>(m_imgData[i + 1]) << ' '
                       << static_cast<int>(m_imgData[i + 2]) << ' '
                       << '\n';
            }

            m_file.close();

            return 0;
        } else {
            return -1;
        }
    }

    ~ImageWriter();

   private:
    // number of channels in the JPG image
    static constexpr int m_jpgComp = 3;
    // number of channels in the PNG image
    static constexpr int m_pngComp = 3;
    
    const std::size_t m_imageWidth;
    const std::size_t m_imageHeight;
    
    // TODO: explain what this variable does
    const int m_strideInBytes;

    static constexpr std::string m_jpgFileName{"pic.jpg"};
    static constexpr std::string m_pngFileName{"pic.png"};
    static constexpr std::string m_ppmFileName{"pic.ppm"};

    // Constant pointer to non-const data
    std::uint8_t *const m_imgData;

    std::size_t m_imgDataCounter;
};
