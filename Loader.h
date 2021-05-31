#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "Point.h"
#include "Matrix1d.h"

class Loader
{
private:
	std::vector<std::string> paths;
	std::string directory;

	std::string getFilename(std::string path);

public:
	Loader(std::string directory);

	size_t load(Point*& points, std::string filename);
	std::vector<std::string> getPaths();
	void unload(const Matrix1d& matrix, std::string directory, std::string filename);
};

