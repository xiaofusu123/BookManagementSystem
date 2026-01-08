#pragma once
#include "Service.h"

bool Create_Bill(int account_id, int book_id, int num);
bool Delete_Bill(int bill_id);
bill_t* Search_Bill_One(int account_id);
bool Revise_Bill( int account_id, char book_name[MAXSIZE]);
static int compare_by_amount(const void* a, const void* b);
bill_t* Search_Bill_All_Sorted();
int get_next_bill_id(bill_t* bills);

