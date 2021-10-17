#include "imageWriter.hpp"

imageWriter::imageWriter(int imageWidth, int imageHeight) : m_imageWidth(imageWidth),
	m_imageHeight(imageHeight) {

	if (m_file.good()) {
		m_file << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	} else {
		useStandardOutput = true;
		std::cerr << "Error opening file. Switching to standard output.\n";
		std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	}
}

inline void write(color c) {
	if (useStandardOutput) {
		std::cout << c;
	} else {
		m_file << c;
	}
}

inline void write(int r, int g, int b) {
	if (useStandardOutput) {
		std::cout << r << " " << g << " " << b << "\n";
	else {
		m_file << r << " " << g << " " << b << "\n";
	}
}
