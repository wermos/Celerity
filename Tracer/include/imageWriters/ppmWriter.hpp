#ifndef PPM_WRITER_HPP
#define PPM_WRITER_HPP

#include <iostream>
#include <string>
#include <fstream>

#include "color.hpp"

class ppmWriter {
	public:
		ppmWriter(int imageWidth, int imageHeight);

		inline void write(color c);
		inline void write(int r, int g, int b);

	private:
		const std::string m_fileName = "pic.ppm";
		std::ofstream m_file;
		bool useStandardOutput = false;

		int imageWidth, imageHeight;
};

#endif // PPM_WRITER_HPP
