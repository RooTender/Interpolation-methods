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

	void updateFunctionsDatabase(const std::string filename);
	void unload(const PointArray& points, const Matrix1d& factors, const std::string prefix, const std::string filename);
};

