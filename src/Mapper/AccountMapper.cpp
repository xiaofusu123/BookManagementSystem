#include "AccountMapper.h"

AccountMapper::AccountMapper()
{
	const char* filename = "Account.dat";
	fileManager.set_filename(filename);
	fileManager.create();
	create_list();
}

AccountMapper::AccountMapper(const char* filename)
{
	fileManager.set_filename(filename);
	create_list();
}

bool AccountMapper::create_list()
{
	accounts = (account_t*)malloc(sizeof(account_t) * MAXNUMBER);
	if (!accounts)
		return false;

	std::vector<account_t> account_array = fileManager.load<account_t>();

	int i;
	for (i = 0; i < account_array.size(); i++) {
		accounts[i] = account_array[i];
	}
	account_count = i;

	return true;
}

account_t* AccountMapper::getbyId(int id)
{
	account_t* account = (account_t*)malloc(sizeof(account_t));
	if (!account)
		return nullptr;

	for (int i = 0; i < account_count; i++) {
		if (accounts[i].account_id == id) {
			*account = accounts[i];
			return account;
		}
	}

	free(account);
	account = NULL;
	return nullptr;
}

bool AccountMapper::addbyOne(account_t* account)
{
	if (!account || account_count + 1 > MAXNUMBER)
		return false;

	accounts[account_count++] = *account;
	return true;
}

bool AccountMapper::addbyBatch(account_t account[], int n)
{
	if (!account || account_count + n > MAXNUMBER)
		return false;

	for (int i = 0; i < n; i++)
		accounts[account_count++] = account[i];

	return true;
}

bool AccountMapper::deletebyId(int id)
{
	int i;
	bool exist = false;

	for (i = 0; i < account_count; i++) {
		if (!exist) {
			if (accounts->account_id == id)
				exist = true;
		}
		else {
			accounts[i - 1] = accounts[i];
		}
	}
	account_count--;

	return exist;
}

bool AccountMapper::deletebyAll()
{
	account_count = 0;
	return true;
}

bool AccountMapper::updatebyOne(account_t* account)
{
	for (int i = 0; i < account_count; i++) {
		if (accounts[i].account_id == account->account_id) {
			accounts[i] = *account;
			return true;
		}
	}

	return false;
}

bool AccountMapper::updatebyBatch(account_t account[], int n)
{
	int j;
	for (int i = 0; i < n; i++) {
		for (j = 0; j < account_count; j++) {
			if (accounts[j].account_id == account[i].account_id) {
				accounts[j] = account[i];
				break;
			}
		}
	}

	return true;
}
