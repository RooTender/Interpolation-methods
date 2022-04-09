#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include "PointArray.h"
#include "Matrix1d.h"

class Loader
{
private:
	std::vector<std::string> paths;
	std::string inputDirectory, outputDirectory;

	static std::string GetFilename(std::string path);
	static std::string GetRawFilename(std::string filename);

public:
	Loader(const std::string& inputDirectory, const std::string& outputDirectory);

	[[nodiscard]] PointArray Load(const std::string& filename) const;
	std::vector<std::string> GetPaths();

	void UpdateFunctionsDatabase(const std::string& filename) const;
	void Unload(const PointArray& points, const Matrix1d& factors, const std::string& prefix, const std::string&
	            filename) const;
};
