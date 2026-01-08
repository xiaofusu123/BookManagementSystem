#pragma once

#include "../FileManager/FileManager.h"

typedef struct book_s {
	int book_id;                  // 图书编号（索引）
	char book_name[MAXSIZE];      // 书名
	float price;                  // 价格
	int total;                    // 总数量
	int borrow;                   // 借阅数

	char type[MAXSIZE];           // 类别
	char author[MAXSIZE];         // 作者
	char pubish_date[MAXSIZE];    // 出版日期（格式：YYYY-MM-DD）
}book_t;


class BookMapper
{
private:
	book_t* books;    // 图书数组
	int book_count;   // 图书种类数量

	FileManager fileManager;

	bool create_list();                                 // 创建线性表

public:
	BookMapper();
	~BookMapper();

	book_t* getbyId(int id);                            // 根据编号获取
	book_t* getbyBookName(const char bookName[]);       // 根据书名获取

	bool addbyOne(book_t* book);                        // 单个增加
	bool addbyBatch(book_t book[], int n);              // 批量增加

	bool deletebyId(int id);                            // 根据编号删除
	bool deletebyBookName(const char bookName[]);       // 根据书名删除
	bool deletebyAll();                                 // 删除所有图书

	bool updatebyOne(book_t* book);                      // 单个更新
	bool updatebyBatch(book_t book[], int n);            // 批量更新

	// 获取成员变量
	inline book_t* getbyAll() { return books; };        // 获取所有图书（整个数组）
	inline int get_bookcount() { return book_count; }   // 获取图书种类数量

	bool SaveBookData();                                // 保存图书数据
};
