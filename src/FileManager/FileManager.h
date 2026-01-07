#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class FileManager
{
private:
	std::string filename;
	size_t file_size = 0;
	
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
			return {};

		file.seekg(0, std::ios::end);
		file_size = file.tellg();
		file.seekg(0, std::ios::beg);

		size_t count = file_size / sizeof(T);
		result.resize(count);

		if (count > 0)
			file.read(reinterpret_cast<char*>(result.data()), file_size);

		file.close();
		return result;
	}

	// 保存文件
	template<typename T>
	inline bool save(const T* objects, int n) {
		std::ofstream file(filename, std::ios::binary);
		if (!file)
			return false;

		for (int i = 0; i < n; i++) {
			file.write(reinterpret_cast<const char*>(&objects[i]), sizeof(T));
		}

		file.close();
		return true;
	}
};
