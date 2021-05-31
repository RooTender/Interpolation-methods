#include "Loader.h"

std::string Loader::getFilename(std::string path)
{
	const size_t lastSlashIndex = path.find_last_of("\\/");
	if (std::string::npos != lastSlashIndex) {
		path.erase(0, lastSlashIndex + 1);
	}

	return path;
}

Loader::Loader(std::string directory) {
	this->directory = directory;

	for (const auto& file : std::filesystem::directory_iterator(directory)) {
		this->paths.push_back(this->getFilename(file.path().u8string()));
	}
}

size_t Loader::load(Point*& points, std::string filename)
{
	auto path = this->directory + "\\" + filename;
	auto fileContents = std::ifstream(path);
	auto lines = (size_t)std::count(std::istreambuf_iterator<char>(fileContents), std::istreambuf_iterator<char>(), '\n');

	points = new Point[lines];

	std::ifstream file;
	file.open(path.c_str());

	size_t i = 0;
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

void Loader::unload(const Matrix1d& matrix, std::string directory, std::string filename)
{
	if (!std::filesystem::is_directory(directory)) {
		std::filesystem::create_directory(directory);
	}

	std::string path = directory + "//" + filename;
	if (std::filesystem::exists(path)) {
		std::filesystem::remove(path);
	}

	std::ofstream ofs;
	ofs.open(path, std::ofstream::out);
	
	for (size_t i = 0; i < matrix.size(); ++i) {
		ofs << matrix.matrix[i] << '\n';
	}

	ofs.close();
}

