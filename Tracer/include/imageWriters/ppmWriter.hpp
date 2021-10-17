#ifndef PPM_WRITER_HPP
#define PPM_WRITER_HPP

#include <iostream>
#include <string>
#include <fstream>

#include "color.hpp"

class ppmWriter {
	public:
		ppmWriter(const int imageWidth, const int imageHeight);

		void write(const color c) {
			if (m_useStandardOutput) {
				std::cout << c << "\n";
			} else {
				m_file << c << "\n";
			}
		}

		void write(const int r, const int g, const int b) {
			if (m_useStandardOutput) {
				std::cout << r << " " << g << " " << b << "\n";
			} else {
				m_file << r << " " << g << " " << b << "\n";
			}
		}

	private:
		const std::string m_fileName = "pic.ppm";
		std::ofstream m_file;
		bool m_useStandardOutput = false;

		const int m_imageWidth, m_imageHeight;
};

#endif // PPM_WRITER_HPP
