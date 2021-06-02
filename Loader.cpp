#include "Loader.h"

std::string Loader::getFilename(std::string path)
{
	const int lastSlashIndex = path.find_last_of("\\/");
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

void Loader::updateFunctionsDatabase(const std::string filename)
{
	if (!std::filesystem::is_directory(this->outputDirectory)) {
		std::filesystem::create_directory(this->outputDirectory);
	}

	const std::string functionFolder = this->outputDirectory + "//" + getRawFilename(filename);
	std::filesystem::remove_all(functionFolder);
	
	if (!std::filesystem::is_directory(functionFolder)) {
		std::filesystem::create_directory(functionFolder);
	}
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
	auto lines = (int)std::count(std::istreambuf_iterator<char>(fileContents), std::istreambuf_iterator<char>(), '\n');

	PointArray points = PointArray(lines);

	std::ifstream file;
	file.open(path.c_str());

	int i = 0;
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

void Loader::unload(const Matrix1d& lagrangeFactors,
					const PointArray& lagrangePoints,
					Matrix1d**& splines,
					const PointArray& splinePoints,
					const std::string filename)
{
	this->updateFunctionsDatabase(filename);

	const std::string functionFolder = this->outputDirectory + "//" + getRawFilename(filename);

	// Lagrange points
	std::ofstream ofs;
	ofs.open(
		functionFolder + "//lagrange_points.txt",
		std::ofstream::out
	);

	for (int i = 0; i < lagrangePoints.getLength(); ++i) {
		ofs << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::fixed
			<< lagrangePoints.arr[i].x << ' ' << lagrangePoints.arr[i].y << '\n';
	}
	ofs.close();

	// Lagrange interpolation
	ofs.open(
		functionFolder + "//lagrange_factors.txt",
		std::ofstream::out
	);
	
	for (int i = 0; i < lagrangeFactors.size(); ++i) {
		ofs << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::scientific
			<< lagrangeFactors.matrix[i] << '\n';
	}
	ofs.close();


	// Spline points
	ofs.open(
		functionFolder + "//spline_points.txt",
		std::ofstream::out
	);

	for (int i = 0; i < splinePoints.getLength(); ++i) {
		ofs << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::fixed
			<< splinePoints.arr[i].x << ' ' << splinePoints.arr[i].y << '\n';
	}
	ofs.close();

	// Spline interpolation
	ofs.open(
		functionFolder + "//spline_factors.txt",
		std::ofstream::out
	);

	for (int i = 0; i < splinePoints.getLength() - 2; ++i) {
		for (int j = 0; j < splines[i]->size(); ++j) {
			ofs << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::scientific
				<< splines[i]->matrix[j] << '\n';
		}
		ofs << ";\n";
	}
	ofs.close();
}
