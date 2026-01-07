#define  _CRT_SECURE_NO_WARNINGS
#include"BorrowRecordService.h"
#include <string.h>
static BorrowRecordMapper borrowRecordMapper;
//创建借书记录，成功返回 true，失败返回 false
bool Create_Borrow_Book(int record_id, int account_id, int book_id,char borrow_date[MAXSIZE], char deadline[MAXSIZE], int status) {
    // 参数合法性校验
    if (record_id <= 0 || account_id <= 0 || book_id <= 0 ||
        strlen(borrow_date) == 0 || strlen(deadline) == 0 ||
        (status != 0 && status != 1)) {
        printf("参数错误！\n");
        return false;
    }

    // 检查是否已存在相同 record_id 的记录
    borrowrecord_t* existing = borrowRecordMapper.getbyBillId(record_id);
    // 检查是否“有效”（比如 ID 是否匹配）
    if (existing->record_id == record_id) {  // 假设 ID 是唯一标识
        printf("借阅记录编号 %d 已存在！\n", record_id);
        return false;
    }

    // 构造新记录
    borrowrecord_t newRecord;
    newRecord.record_id = record_id;
    newRecord.account_id = account_id;
    newRecord.book_id = book_id;
    strcpy_s(newRecord.borrow_date, MAXSIZE, borrow_date);
    strcpy_s(newRecord.deadline, MAXSIZE, deadline);
    newRecord.status = status;

    // 添加到数据库
    return borrowRecordMapper.addbyOne(&newRecord);
}

//删除借书记录，成功返回 true，失败返回 false
bool Delete_Borrow_Book(int record_id) {
    if (record_id <= 0) {
        return false;
    }

    // 获取记录（返回结构体）
    borrowrecord_t* record = borrowRecordMapper.getbyBillId(record_id);

    // 判断是否存在：record_id 是否等于输入的 ID
    if (record->record_id != record_id) {
        printf("借阅记录编号 %d 不存在！\n", record_id);
        return false;
    }

    // 删除操作
    return borrowRecordMapper.deletebyId(record_id);
}

//修改借书记录，成功返回 true，失败返回 false
bool Revise_Borrow_Book(int record_id, int account_id, int book_id,char borrow_date[MAXSIZE], char deadline[MAXSIZE], int status) {
    if (record_id <= 0 || account_id <= 0 || book_id <= 0 ||
        strlen(borrow_date) == 0 || strlen(deadline) == 0 ||
        (status != 0 && status != 1)) {
        printf("参数错误！\n");
        return false;
    }

    // 获取原记录
    borrowrecord_t* record = borrowRecordMapper.getbyBillId(record_id);

    // 判断是否存在
    if (record->record_id != record_id) {
        printf("借阅记录编号 %d 不存在！\n", record_id);
        return false;
    }

    // 更新字段
    record->account_id = account_id;
    record->book_id = book_id;
    strcpy_s(record->borrow_date, MAXSIZE, borrow_date);
    strcpy_s(record->deadline, MAXSIZE, deadline);
    record->status = status;

    // 保存更新
    return borrowRecordMapper.updatebyOne(record);  // 注意：updatebyOne 接收指针
}


// 查询单条借阅记录，返回借书记录信息，若不存在则返回空结构体（record_id = 0）
borrowrecord_t* Search_Borrow_Book_One(int record_id) {
    // 参数合法性校验
    if (record_id <= 0) {
        borrowrecord_t* empty = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
        empty->record_id = 0;
        empty->account_id = 0;
        empty->book_id = 0;
        strcpy_s(empty->borrow_date, MAXSIZE, "");
        strcpy_s(empty->deadline, MAXSIZE, "");
        empty->status = -1;  // 标记为无效状态
        return empty;
    }

    // 调用 Mapper 获取记录
    borrowrecord_t* record = borrowRecordMapper.getbyBillId(record_id);

    // 如果获取到的 record_id 不等于输入值，说明没找到
    if (record->record_id != record_id) {
        // 返回空结构体
        borrowrecord_t* empty = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
        empty->record_id = 0;
        empty->account_id = 0;
        empty->book_id = 0;
        strcpy_s(empty->borrow_date, MAXSIZE, "");
        strcpy_s(empty->deadline, MAXSIZE, "");
        empty->status = -1;
        return empty;
    }

    return record;
}


// 查询所有借阅记录，返回指向借阅记录数组的指针
// 若无记录则返回 nullptr
borrowrecord_t* Search_Borrow_Book_All() {
    // 获取所有记录
    borrowrecord_t* records = borrowRecordMapper.getbyAll();

    // 如果记录数量为0，返回nullptr
    if (borrowRecordMapper.get_recordcount() == 0) {
        printf("暂无借阅记录。\n");
        return nullptr;
    }

    return records;
}