#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class FileManager
{
private:
	std::string filename;
	size_t file_size = 0;

	void get_fileSize(std::ifstream file);
	
public:
	FileManager() { };

	FileManager(const std::string& filename)
		: filename(filename) { }

	void set_filename(const std::string& filename);

	bool creat();    // 创建文件
	bool remove();   // 删除文件
	bool clear();    // 清除文件内容

	// 加载文件
	template<typename T>
	inline std::vector<T> load() {
		std::vector<T> result;
		std::ifstream file(filename, std::ios::binary);

		if (!file)
			return false;

		get_fileSize(file);

		size_t count = file_size / sizeof(T);
		result.size(count);

		if (count > 0)
			file.read(reinterpret_cast<char*>(result.data()), file_size);

		file.close();
		return result;
	}

	// 保存文件
	template<typename T>
	inline bool save(const T& objects) {
		std::ofstream file(filename, std::ios::binary);
		if (!file)
			return false;

		for (const auto& obj : objects)
			file.write(reinterpret_cast<const char*>(&obj), sizeof(T));

		file.close();
		return true;
	}
};
