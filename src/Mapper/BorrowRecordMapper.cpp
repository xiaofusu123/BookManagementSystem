#include "BorrowRecordMapper.h"

BorrowRecordMapper::BorrowRecordMapper()
{
	const char* filename = "../data/BorrowRecord.dat";
	fileManager.set_filename(filename);
	fileManager.create();
	create_list();
}

BorrowRecordMapper::BorrowRecordMapper(const std::string& filename)
{
	fileManager.set_filename(filename);
	create_list();
}

BorrowRecordMapper::~BorrowRecordMapper()
{
	fileManager.save(records, record_count);

	free(records);
	records = NULL;
}

bool BorrowRecordMapper::create_list()
{
	records = (borrowrecord_t*)malloc(sizeof(borrowrecord_t) * MAXNUMBER);
	if (!records)
		return false;

	std::vector<borrowrecord_t> record_array = fileManager.load<borrowrecord_t>();

	int i;
	for (i = 0; i < record_array.size(); i++) {
		records[i] = record_array[i];
	}
	record_count = i;

	return true;
}

borrowrecord_t* BorrowRecordMapper::getbyBillId(int record_id)
{
	borrowrecord_t* record = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
	if (!record)
		return nullptr;

	for (int i = 0; i < record_count; i++) {
		if (records[i].record_id == record_id) {
			*record = records[i];
			return record;
		}
	}

	free(record);
	record = NULL;
	return nullptr;
}

borrowrecord_t* BorrowRecordMapper::getbyAccountId(int account_id)
{
	borrowrecord_t* record = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
	if (!record)
		return nullptr;

	for (int i = 0; i < record_count; i++) {
		if (records[i].account_id == account_id) {
			*record = records[i];
			return record;
		}
	}

	free(record);
	record = NULL;
	return nullptr;
}

bool BorrowRecordMapper::addbyOne(borrowrecord_t* record)
{
	if (!record || record_count + 1 > MAXNUMBER)
		return false;

	records[record_count++] = *record;
	return true;
}

bool BorrowRecordMapper::addbyBatch(borrowrecord_t record[], int n)
{
	return false;
}

bool BorrowRecordMapper::deletebyId(int bill_id)
{
	int i;
	bool exist = false;

	for (i = 0; i < record_count; i++) {
		if (!exist) {
			if (records->book_id == bill_id)
				exist = true;
		}
		else {
			records[i - 1] = records[i];
		}
	}
	record_count--;

	return exist;
}

bool BorrowRecordMapper::updateStatus(int bill_id, int status)
{
	for (int i = 0; i < record_count; i++) {
		if (records[i].book_id == bill_id) {
			records[i].status = status;
			return true;
		}
	}

	return false;
}

bool BorrowRecordMapper::updatebyOne(borrowrecord_t* record)
{
	for (int i = 0; i < record_count; i++) {
		if (records[i].record_id == record->record_id) {
			records[i] = *record;
			return true;
		}
	}

	return false;
}

bool BorrowRecordMapper::updatebyBatch(borrowrecord_t record[], int n)
{
	int j;
	for (int i = 0; i < n; i++) {
		for (j = 0; j < record_count; j++) {
			if (records[j].record_id == records[i].record_id) {
				records[j] = record[i];
				break;
			}
		}
	}

	return true;
}

bool BorrowRecordMapper::SaveRecordData()
{
	return fileManager.save(records, record_count);
}
