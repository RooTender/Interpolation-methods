#include "Loader.h"

std::string Loader::getFilename(std::string path)
{
	const size_t lastSlashIndex = path.find_last_of("\\/");
	if (std::string::npos != lastSlashIndex) {
		path.erase(0, lastSlashIndex + 1);
	}

	return path;
}

std::string Loader::getRawFilename(std::string filename)
{
	auto lastindex = filename.find_last_of(".");

	if (lastindex != filename.npos) {
		return filename.substr(0, lastindex);
	}
	return filename;
}

Loader::Loader(std::string inputDirectory, std::string outputDirectory) {
	this->inputDirectory = inputDirectory;
	this->outputDirectory = outputDirectory;

	for (const auto& file : std::filesystem::directory_iterator(inputDirectory)) {
		this->paths.push_back(this->getFilename(file.path().u8string()));
	}
}

PointArray Loader::load(std::string filename)
{
	auto path = this->inputDirectory + "\\" + filename;
	auto fileContents = std::ifstream(path);
	auto lines = (size_t)std::count(std::istreambuf_iterator<char>(fileContents), std::istreambuf_iterator<char>(), '\n');

	PointArray points = PointArray(lines);

	std::ifstream file;
	file.open(path.c_str());

	size_t i = 0;
	long double x, y;
	while (file >> x >> y && i < lines) {
		points.arr[i++] = Point(x, y);
	}

	file.close();

	return PointArray(points);
}

std::vector<std::string> Loader::getPaths()
{
	return paths;
}

void Loader::unload(const Matrix1d& matrix, const PointArray& pointArray, std::string filename)
{
	if (!std::filesystem::is_directory(this->outputDirectory)) {
		std::filesystem::create_directory(this->outputDirectory);
	}

	std::string path = this->outputDirectory + "//" + filename;
	if (std::filesystem::exists(path)) {
		std::filesystem::remove(path);
	}

	path = this->outputDirectory + "//available.txt";
	if (!std::filesystem::exists(path)) {
		std::ofstream ofs(path);
		ofs.close();
	}

	const std::string rawFilename = getRawFilename(filename);

	std::ifstream ifs;
	ifs.open(path);

	bool dataExistsInFile = false;
	std::string line;
	
	while (ifs >> line) {
		if (line == rawFilename) {
			dataExistsInFile = true;
			break;
		}
	}
	ifs.close();

	if (!dataExistsInFile) {
		std::ofstream ofs;
		ofs.open(path, std::ofstream::app);
		ofs << rawFilename << '\n';
		ofs.close();
	}

	std::ofstream ofs;
	ofs.open(
		this->outputDirectory + "//" + getRawFilename(filename) + "_function.txt",
		std::ofstream::out
	);
	
	for (size_t i = 0; i < matrix.size(); ++i) {
		ofs << matrix.matrix[i] << '\n';
	}
	ofs.close();

	ofs.open(
		this->outputDirectory + "//" + getRawFilename(filename) + "_points.txt",
		std::ofstream::out
	);

	for (size_t i = 0; i < pointArray.getLength(); ++i) {
		ofs << pointArray.arr[i].x << ' ' << pointArray.arr[i].y << '\n';
	}
	ofs.close();
}
