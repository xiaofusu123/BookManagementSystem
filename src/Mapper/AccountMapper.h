#pragma once

#include "../FileManager/FileManager.h"

#define MAXSIZE 100

typedef struct account_s {
	int account_id;           // 账号
	char password[MAXSIZE];   // 密码
	float balance;            // 余额
	char phone[MAXSIZE];      // 联系电话
	
	int role;                // 角色（0：用户  1：管理员）
}account_t;


class AccountMapper {
private:
	account_s* accounts;
	int account_count;

	FileManager fileManager;

public:
	AccountMapper(const char* filename);

	bool create_list();                                       // 创建线性表

	account_t getbyId(int id);                                // 根据编号获取

	bool addbyOne(account_t account);                         // 单个增加
	bool addbyBatch(account_t account[]);                     // 批量增加

	bool deletebyId(int id);                                  // 根据编号删除
	bool deletebyAll();                                       // 删除所有账号

	bool updatebyOne(account_t account);                      // 单个更新
	bool updatebyBatch(account_t account[]);                  // 批量更新

	// 获取成员变量
	inline account_t* getbyAll() { return accounts; };        // 获取所有账号（整个数组）
	inline int get_accountcount() { return account_count; }   // 获取账号数量
};
