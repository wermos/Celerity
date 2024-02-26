#include "imageWriters/ppmWriter.hpp"

ppmWriter::ppmWriter(int imageWidth, int imageHeight) : m_imageWidth(imageWidth),
	m_imageHeight(imageHeight) {
	m_file.open(m_fileName, std::ofstream::out | std::ofstream::trunc);

	if (m_file.good()) {
		m_file << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	} else {
		m_useStandardOutput = true;
		std::cerr << "Error opening file. Switching to standard output.\n";
		std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	}
	/**
	 * P3
	 * <width> <height>
	 * <max value of color>
	 *
	 * where "P3" tells the viewer that the colors are in ASCII
	 * <width> tells the viewer how many columns there are in the picture,
	 * <height> tells the viewer how many rows, and
	 * <max value of color> tells the viewer how to normalize the color values
	 */
}
