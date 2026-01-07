#include "BillMapper.h"

BillMapper::BillMapper()
{
	const char* filename = "Bill.dat";
	fileManager.set_filename(filename);
	fileManager.create();
	create_list();
}

BillMapper::BillMapper(const std::string& filename)
{
	fileManager.set_filename(filename);
	create_list();
}

bool BillMapper::create_list()
{
	bills = (bill_t*)malloc(sizeof(bill_t) * MAXNUMBER);
	if (!bills)
		return false;

	std::vector<bill_t> bill_array = fileManager.load<bill_t>();

	int i;
	for (i = 0; i < bill_array.size(); i++) {
		bills[i] = bill_array[i];
	}
	bill_count = i;

	return true;
}

bill_t* BillMapper::getbyBillId(int bill_id)
{
	bill_t* bill = (bill_t*)malloc(sizeof(bill_t));
	if (!bill)
		return nullptr;

	for (int i = 0; i < bill_count; i++) {
		if (bills[i].bill_id == bill_id) {
			*bill = bills[i];
			return bill;
		}
	}

	free(bill);
	bill = NULL;
	return nullptr;
}

bill_t* BillMapper::getbyAccountId(int account_id)
{
	bill_t* bill = (bill_t*)malloc(sizeof(bill_t));
	if (!bill)
		return nullptr;

	for (int i = 0; i < bill_count; i++) {
		if (bills[i].account_id == account_id) {
			*bill = bills[i];
			return bill;
		}
	}

	free(bill);
	bill = NULL;
	return nullptr;
}

bill_t* BillMapper::getbyBookId(int book_id)
{
	bill_t* bill = (bill_t*)malloc(sizeof(bill_t));
	if (!bill)
		return nullptr;

	for (int i = 0; i < bill_count; i++) {
		if (bills[i].book_id == book_id) {
			*bill = bills[i];
			return bill;
		}
	}

	free(bill);
	bill = NULL;
	return nullptr;
}

bool BillMapper::addbyOne(bill_t* bill)
{
	if (!bill || bill_count + 1 > MAXNUMBER)
		return false;

	bills[bill_count++] = *bill;
	return true;
}

bool BillMapper::addbyBatch(bill_t bill[], int n)
{
	if (!bill || bill_count + n > MAXNUMBER)
		return false;

	for (int i = 0; i < n; i++)
		bills[bill_count++] = bill[i];

	return true;
}

bool BillMapper::deletebyId(int id)
{
	int i;
	bool exist = false;

	for (i = 0; i < bill_count; i++) {
		if (!exist) {
			if (bills->bill_id == id)
				exist = true;
		}
		else {
			bills[i - 1] = bills[i];
		}
	}
	bill_count--;

	return exist;
}

bool BillMapper::deletebyAll()
{
	bill_count = 0;
	return true;
}

bool BillMapper::updatebyOne(bill_t* bill)
{
	for (int i = 0; i < bill_count; i++) {
		if (bills[i].bill_id == bill->bill_id) {
			bills[i] = *bill;
			return true;
		}
	}

	return false;
}

bool BillMapper::updatebyBatch(bill_t bill[], int n)
{
	int j;
	for (int i = 0; i < n; i++) {
		for (j = 0; j < bill_count; j++) {
			if (bills[j].bill_id == bill[i].bill_id) {
				bills[j] = bill[i];
				break;
			}
		}
	}

	return true;
}
