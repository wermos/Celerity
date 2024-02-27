#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "color.hpp"

class ppmWriter {
   public:
    ppmWriter(const std::size_t imageWidth, const std::size_t imageHeight);

    void writeToBuffer(const color c) {
        if (m_useStandardOutput) {
            std::cout << c << "\n";
        } else {
            m_file << c << "\n";
        }
    }

    void writeToBuffer(const int r, const int g, const int b) {
        if (m_useStandardOutput) {
            std::cout << r << " " << g << " " << b << "\n";
        } else {
            m_file << r << " " << g << " " << b << "\n";
        }
    }

   private:
    static constexpr std::string m_fileName{"pic.ppm"};
    std::ofstream m_file;
    bool m_useStandardOutput = false;

    const std::size_t m_imageWidth, m_imageHeight;
};
