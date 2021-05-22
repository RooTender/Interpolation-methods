#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "Point.h"

class Loader
{
private:
	std::vector<std::string> paths;

public:
	Loader(std::string directory);

	size_t load(Point*& points, std::string filename);
	std::vector<std::string> getPaths();
};

