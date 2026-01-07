#pragma once
#include"../Mapper/BorrowRecordMapper.h"
bool Create_Borrow_Book(int record_id, int account_id, int book_id, char borrow_date[MAXSIZE], char deadline[MAXSIZE], int status);
bool Delete_Borrow_Book(int record_id);
bool Revise_Borrow_Book(int record_id);
bool Search_Borrow_Book(int record_id);