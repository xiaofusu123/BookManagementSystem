#pragma once
#include "Service.h"

bool Create_Borrow_Book(int account_id, char book_name[MAXSIZE]);
bool Delete_Borrow_Book(int record_id);
//bool Revise_Borrow_Book(int record_id, int account_id, int book_id, char borrow_date[MAXSIZE], char deadline[MAXSIZE], int status);
borrowrecord_t* Search_Borrow_Book_One(int account_id, char book_name[MAXSIZE]);
borrowrecord_t* Search_Borrow_Book_All();
int get_next_record_id(borrowrecord_t* borrowrecords);