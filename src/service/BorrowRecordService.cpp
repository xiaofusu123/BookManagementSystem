#define  _CRT_SECURE_NO_WARNINGS
#include"BorrowRecordService.h"
#include <string.h>
#include <ctime>


//获取自增id
int get_next_record_id(borrowrecord_t* borrowrecords) {
    int count = borrowRecordMapper.get_recordcount();
    if (count == 0) return 1;
    int max_id = borrowrecords[0].record_id;
    for (int i = 1; i < count; i++) {
        if (borrowrecords[i].record_id > max_id) {
            max_id = borrowrecords[i].record_id;
        }
    }
    return max_id + 1;
}

//创建借书记录，成功返回 true，失败返回 false
//这个参数record_id和book_id是自增的，不需要用户输入，这个借书的时间要用时间函数获取当前时间，deadline是根据借书时间加上一个月得到的，status初始为0表示未归还
bool Create_Borrow_Book(int account_id, char book_name[MAXSIZE]) {
    // 1. 参数校验
    if (account_id <= 0 || strlen(book_name) == 0) {
        printf(" 参数错误！\n");
        return false;
    }

    // 2. 获取用户账户
    account_t* account = accountMapper.getbyId(account_id);
    if (!account) {
        printf(" 账号 %d 不存在！\n", account_id);
        return false;
    }

    // 3. 获取图书信息
    book_t* book = bookMapper.getbyBookName(book_name);
    if (!book) {
        printf(" 图书《%s》不存在！\n", book_name);
        return false;
    }

    // 4. 检查库存
    if (book->total <= 0) {
        printf(" 库存不足！《%s》已无可用书籍。\n", book_name);
        return false;
    }

    // 5. 声明日期缓冲区（关键修复）
    char borrow_date[MAXSIZE];
    char deadline[MAXSIZE];

    // 6. 获取当前时间
    time_t now = time(nullptr);
    struct tm* local_time = localtime(&now);
    strftime(borrow_date, MAXSIZE, "%Y-%m-%d", local_time);

    // 7. 计算截止日期（+1个月）
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;  // 0～11 → 1～12
    int day = local_time->tm_mday;

    month += 1;
    if (month > 12) {
        month = 1;
        year++;
    }

    snprintf(deadline, MAXSIZE, "%04d-%02d-%02d", year, month, day);

    borrowrecord_t* borrowrecords =borrowRecordMapper.getbyAll(); //加载现有数据以获取最新ID
    // 8. 生成 record_id
    int new_record_id =get_next_record_id(borrowrecords);

    // 9. 创建记录
    borrowrecord_t* new_record = new borrowrecord_t;
    new_record->record_id = new_record_id;
    new_record->account_id = account_id;
    new_record->book_id = book->book_id;
    strncpy(new_record->borrow_date, borrow_date, MAXSIZE - 1);
    strncpy(new_record->deadline, deadline, MAXSIZE - 1);
    new_record->status = 0;  // 借阅中

    // 10. 更新图书状态（内存）
    book->borrow += 1;
    book->total -= 1;

    // 11. 保存到文件（ 关键：必须调用 updatebyOne 内部保存）
    bool added = borrowRecordMapper.addbyOne(new_record);
    bool book_updated = bookMapper.updatebyOne(book);          // 确保内部调用了 SaveBookData()

    if (added && book_updated) {
        printf(" 借书成功！\n");
        printf("记录ID：%d，书名：《%s》，借阅时间：%s，截止时间：%s\n",
            new_record_id, book_name, borrow_date, deadline);
        delete new_record;  // 如果 addbyOne 复制了数据，可以删；否则不要删
        return true;
    }
    else {
        printf(" 借书失败！请检查文件权限或 Mapper 实现。\n");
        delete new_record;
        return false;
    }
}


//删除借书记录，成功返回 true，失败返回 false
bool Delete_Borrow_Book(int record_id) {
    if (record_id <= 0) {
        return false;
    }

    // 获取记录（返回结构体）
    borrowrecord_t* record = borrowRecordMapper.getbyBillId(record_id);
	if (!record)
	{
		return false;
	}
    // 删除操作
    return borrowRecordMapper.deletebyId(record_id);
}

////修改借书记录，成功返回 true，失败返回 false
//bool Revise_Borrow_Book(int record_id, int account_id, int book_id,char borrow_date[MAXSIZE], char deadline[MAXSIZE], int status) {
//    if (record_id <= 0 || account_id <= 0 || book_id <= 0 ||
//        strlen(borrow_date) == 0 || strlen(deadline) == 0 ||
//        (status != 0 && status != 1)) {
//        printf("参数错误！\n");
//        return false;
//    }
//
//    // 获取原记录
//    borrowrecord_t* record = borrowRecordMapper.getbyBillId(record_id);
//    if (!record) {
//		return false;
//    }
//
//    // 判断是否存在
//    if (record->record_id != record_id) {
//        printf("借阅记录编号 %d 不存在！\n", record_id);
//        return false;
//    }
//
//    // 更新字段
//    record->account_id = account_id;
//    record->book_id = book_id;
//    strcpy_s(record->borrow_date, MAXSIZE, borrow_date);
//    strcpy_s(record->deadline, MAXSIZE, deadline);
//    record->status = status;
//
//    // 保存更新
//    return borrowRecordMapper.updatebyOne(record)&& borrowRecordMapper.SaveRecordData();  // 注意：updatebyOne 接收指针
//}


// 查询单个用户的借阅记录，返回单个用户的所有的未归还借阅记录数组的指针
borrowrecord_t* Search_Borrow_Book_One(int account_id, char book_name[MAXSIZE]) {
    // 1. 获取所有借阅记录
    borrowrecord_t* all_records = borrowRecordMapper.getbyAll();
    int record_count = borrowRecordMapper.get_recordcount();

    if (all_records == nullptr || record_count == 0) {
        return nullptr;
    }

    // 2. 统计符合条件的记录数量
    int valid_count = 0;
    for (int i = 0; i < record_count; i++) {
        borrowrecord_t& rec = all_records[i];
        if (rec.account_id == account_id && rec.status == 0) {
            // 如果 book_name 为空，直接计入
            if (strlen(book_name) == 0) {
                valid_count++;
            }
            else {
                // 否则通过 book_id 查图书，比对书名
                book_t* book = bookMapper.getbyId(rec.book_id);
                if (book != nullptr && strcmp(book->book_name, book_name) == 0) {
                    valid_count++;
                }
            }
        }
    }

    // 3. 无结果则返回 nullptr
    if (valid_count == 0) {
        return nullptr;
    }

    // 4. 分配结果数组
    borrowrecord_t* result = new borrowrecord_t[valid_count];
    int index = 0;

    // 5. 复制符合条件的记录
    for (int i = 0; i < record_count; i++) {
        borrowrecord_t& rec = all_records[i];
        if (rec.account_id == account_id && rec.status == 0) {
            if (strlen(book_name) == 0) {
                result[index++] = rec;
            }
            else {
                book_t* book = bookMapper.getbyId(rec.book_id);
                if (book != nullptr && strcmp(book->book_name, book_name) == 0) {
                    result[index++] = rec;
                }
            }
        }
    }

    return result;
}
// 查询所有借阅记录，返回指向借阅记录数组的指针
// 若无记录则返回 nullptr
borrowrecord_t* Search_Borrow_Book_All() {
    // 获取所有记录
    borrowrecord_t* records = borrowRecordMapper.getbyAll();
    if (!records) {
        return nullptr;
    }
    return records;
}