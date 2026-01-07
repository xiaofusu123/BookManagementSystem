#include "FileManager.h"

void FileManager::set_filename(const std::string& filename)
{
	this->filename = filename;
}

bool FileManager::create()
{
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "创建文件失败 " << filename << std::endl;
		file.close();
		return false;
	}

	std::cout << "创建文件成功 " << filename << std::endl;
	file.close();
	return true;
}

bool FileManager::remove()
{
	if (std::remove(filename.c_str()) == 0) {
		std::cout << "删除文件成功 " << filename << std::endl;
		return true;
	}

	std::cerr << "删除文件失败 " << filename << std::endl;
	return false;
}

bool FileManager::clear()
{
	std::ofstream file(filename, std::ios::trunc);
	file.close();
	return file.good();
}
