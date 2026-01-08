#pragma once

#include "../FileManager/FileManager.h"

typedef struct bill_s {
	int bill_id;
	int account_id;
	int book_id;

	int num;
	float total_price;
}bill_t;

class BillMapper
{
private:
	bill_t* bills;
	int bill_count;

	FileManager fileManager;

	bool create_list();                                 // 创建线性表

public:
	BillMapper();
	~BillMapper();

	bill_t* getbyBillId(int bill_id);                    // 根据账单编号获取
	bill_t* getbyAccountId(int account_id);              // 根据账号获取
	bill_t* getbyBookId(int book_id);                    // 根据图书编号获取

	bool addbyOne(bill_t* bill);                        // 单个增加
	bool addbyBatch(bill_t bill[], int n);              // 批量增加

	bool deletebyId(int id);                            // 根据编号删除
	bool deletebyAll();                                 // 删除所有账单

	bool updatebyOne(bill_t* bill);                     // 单个更新
	bool updatebyBatch(bill_t bill[], int n);           // 批量更新

	// 获取成员变量
	inline bill_t* getbyAll() { return bills; };        // 获取所有账单（整个数组）
	inline int get_bookcount() { return bill_count; }   // 获取账单数量

	bool SaveBillData();                                // 保存账单数据
};
