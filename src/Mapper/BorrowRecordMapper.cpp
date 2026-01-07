#include "BorrowRecordMapper.h"

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