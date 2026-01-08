#pragma once
#include"Service.h"

bool Register(int account_id, char password[MAXSIZE], float balance, char phone[MAXSIZE], int role);
int Login(int account, char password[MAXSIZE]);
bool Delete_Account(int account_id);
account_t* SearchOne(int account_id);
account_t* SearchAll();
bool Recharge(int account_id, float amount);
bool Deduct(int account_id, float amount);
float Check_Balance(int account_id);