#include "Loader.h"

Loader::Loader(std::string directory) {
	for (const auto& file : std::filesystem::directory_iterator(directory)) {
		this->paths.push_back(file.path().u8string());
	}
}

size_t Loader::load(Point*& points, std::string filename)
{
	auto fileContents = std::ifstream(filename);
	auto lines = (size_t)std::count(std::istreambuf_iterator<char>(fileContents), std::istreambuf_iterator<char>(), '\n');

	points = new Point[lines];

	std::ifstream file;
	file.open(filename.c_str());

	auto i = 0;
	long double x, y;
	while (file >> x >> y && i < lines) {
		points[i++] = Point(x, y);
	}

	file.close();

	return lines;
}

std::vector<std::string> Loader::getPaths()
{
	return paths;
}

