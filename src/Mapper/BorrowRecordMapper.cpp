#include "BorrowRecordMapper.h"

BorrowRecordMapper::BorrowRecordMapper()
{
	const char* filename = "BorrowRecord.dat";
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
	records = (borrowrecord_t*)malloc(sizeof(borrowrecord_t) * MAX_RECORD);
	if (!records)
		return false;

	std::vector<borrowrecord_t> book_array = fileManager.load<borrowrecord_t>();

	int i;
	for (i = 0; i < book_array.size(); i++) {
		records[i] = book_array[i];
	}
	record_count = i;

	return true;
}

borrowrecord_t* BorrowRecordMapper::getbyBillId(int bill_id)
{
	borrowrecord_t* record = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
	if (!record)
		return nullptr;

	for (int i = 0; i < record_count; i++) {
		if (records[i].book_id == bill_id) {
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
	if (!record || record_count + 1 > MAX_RECORD)
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

