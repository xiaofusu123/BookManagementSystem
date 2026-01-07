#pragma once
#include"../Mapper/BillMapper.h"
bool Create_Bill( int bill_id, int account_id, int book_id, int num, float total_price);
bool Delete_Bill(int bill_id);
bill_t* Search_Bill_One( int bill_id);
bool Revise_Bill(int bill_id, int account_id, int book_id, int num, float total_price);
static int compare_by_amount(const void* a, const void* b);
bill_t* Search_Bill_All_Sorted();