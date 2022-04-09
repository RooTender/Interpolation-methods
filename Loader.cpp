#include "Loader.h"
#include <fstream>

std::string Loader::GetFilename(std::string path)
{
	if (const auto lastSlashIndex = path.find_last_of("\\/"); std::string::npos != lastSlashIndex)
	{
		path.erase(0, lastSlashIndex + 1);
	}

	return path;
}

std::string Loader::GetRawFilename(std::string filename)
{
	if (const auto lastIndex = filename.find_last_of('.'); lastIndex != std::string::npos)
	{
		return filename.substr(0, lastIndex);
	}
	return filename;
}

void Loader::UpdateFunctionsDatabase(const std::string& filename) const
{
	if (!std::filesystem::is_directory(this->outputDirectory))
	{
		std::filesystem::create_directory(this->outputDirectory);
	}

	const std::string functionFolder = this->outputDirectory + "//" + GetRawFilename(filename);
	std::filesystem::remove_all(functionFolder);

	if (!std::filesystem::is_directory(functionFolder))
	{
		std::filesystem::create_directory(functionFolder);
	}
}

Loader::Loader(const std::string& inputDirectory, const std::string& outputDirectory) : inputDirectory(inputDirectory),
                                                                                      outputDirectory(outputDirectory)
{
	if (!std::filesystem::is_directory(outputDirectory))
	{
		std::filesystem::create_directory(outputDirectory);
	}

	for (const auto& file : std::filesystem::directory_iterator(inputDirectory))
	{
		this->paths.push_back(this->GetFilename(file.path().u8string()));
	}
}

PointArray Loader::Load(const std::string& filename) const
{
	auto path = this->inputDirectory + "\\" + filename;
	auto fileContents = std::ifstream(path);
	auto lines = static_cast<int>(std::count(std::istreambuf_iterator<char>(fileContents),
	                                         std::istreambuf_iterator<char>(), '\n'));

	auto points = PointArray(lines);

	std::ifstream file;
	file.open(path.c_str());

	int i = 0;
	long double x, y;
	while (file >> x >> y && i < lines)
	{
		points.arr[i++] = Point(x, y);
	}

	file.close();

	return PointArray{points};
}

std::vector<std::string> Loader::GetPaths()
{
	return paths;
}

void Loader::Unload(const PointArray& points, const Matrix1d& factors, const std::string& prefix,
                    const std::string& filename) const
{
	const std::string functionFolder = this->outputDirectory + "//" + GetRawFilename(filename);

	// Lagrange points
	std::ofstream ofs;
	ofs.open(
		functionFolder + "//" + prefix + "_points.txt",
		std::ofstream::out
	);

	for (int i = 0; i < points.getLength(); ++i)
	{
		ofs << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::fixed
			<< points.arr[i].x << ' ' << points.arr[i].y << '\n';
	}
	ofs.close();

	// Lagrange interpolation
	ofs.open(
		functionFolder + "//" + prefix + "_factors.txt",
		std::ofstream::out
	);

	for (int i = 0; i < factors.size(); ++i)
	{
		ofs << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::scientific
			<< factors.matrix[i] << '\n';
	}
	ofs.close();
}
