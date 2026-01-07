#pragma once

#include "../FileManager/FileManager.h"

#define MAXSIZE 50
#define MAX_RECORD 1000

typedef struct borrowrecord_s {
	int record_id;               // 借阅记录编号
	char name[MAXSIZE];          // 姓名
	char phone[MAXSIZE];         // 联系电话

	int book_id;                 // 图书编号
	char borrow_date[MAXSIZE];   // 借阅日期
	char deadline[MAXSIZE];      // 归还截止日期
	int status;                  // 借阅状态（0：借阅中  1：已归还）
}borrowrecord_t;   // 借阅记录

class BorrowRecordMapper
{
private:
	borrowrecord_t* records;   // 借阅记录数组
	int record_count;          // 借阅记录数量

	FileManager fileManager;

public:
	BorrowRecordMapper(const std::string& filename);

	bool create_list();                                      // 创建线性表

	borrowrecord_t getbyId(int id);                          // 根据编号获取
	borrowrecord_t getbyName(const char s[]);                // 根据姓名获取

	bool addbyOne(borrowrecord_t record);                    // 单个增加
	bool addbyBatch(borrowrecord_t record[]);                // 批量增加

	bool deletebyId(int id);                                 // 根据编号删除
	bool deletebyName(const char s[]);                       // 根据姓名删除
	bool deletebyAll();                                      // 删除所有记录

	bool updateStatus(int status);                           // 更新借阅记录状态
	bool updatebyOne(borrowrecord_t record);                 // 单个更新
	bool updatebyBatch(borrowrecord_t record[]);             // 批量更新

	// 获取成员变量
	inline borrowrecord_t* getbyAll() { return records; };   // 获取所有借阅记录（整个数组）
	inline int get_recordcount() { return record_count; }    // 获取借阅记录数量
};
