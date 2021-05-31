#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "PointArray.h"
#include "Matrix1d.h"

class Loader
{
private:
	std::vector<std::string> paths;
	std::string inputDirectory, outputDirectory;

	std::string getFilename(std::string path);
	std::string getRawFilename(std::string filename);

public:
	Loader(std::string inputDirectory, std::string outputDirectory);

	PointArray load(std::string filename);
	std::vector<std::string> getPaths();
	void unload(const Matrix1d& matrix, const PointArray& pointArray, const std::string filename);
};

