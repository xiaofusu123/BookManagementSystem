#pragma once

#include "Service.h"

bool Create_Book(int book_id, char book_name[MAXSIZE], float price, int total, int borrow, char type[MAXSIZE], char author[MAXSIZE], char publish_date[MAXSIZE]);
bool Delete_Book(int book_id);
bool Revise_Book(int book_id, char book_name[MAXSIZE], float price, int total, int borrow, char type[MAXSIZE], char author[MAXSIZE], char publish_date[MAXSIZE]);
bool Search_Book(char type[MAXSIZE],char book_name[MAXSIZE],char author[MAXSIZE]);
bool SearchAll();
void shell_sort(book_t* books, int n);
void XeSearchByMoney();
void radix_sort_by_date(book_t* books, int n);
void Js_sort();

void QSearchBytotalAndborrow();
void Q_sort(book_t* books, int n);
void quickSort(book_t* books, int low, int high);
int partition(book_t* books, int low, int high);