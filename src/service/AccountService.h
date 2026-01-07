#pragma once
#include"../Mapper/AccountMapper.h"
#include"../Mapper/BillMapper.h"
#include"../Mapper/BorrowRecordMapper.h"
bool Register( int account_id, char password[MAXSIZE], float balance, char phone[MAXSIZE], int role);
int Login(int account, char password[MAXSIZE]);
bool Delete_Account(int account_id);
account_t SearchOne(int account_id);