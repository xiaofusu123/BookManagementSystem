#define  _CRT_SECURE_NO_WARNINGS
#include"AccountService.h"
#include <string.h>
#include <stdlib.h>

BillMapper billMapper;
//创建账单：成功返回 true，失败返回 false
bool Create_Bill(int bill_id, int account_id, int book_id, int num, float total_price) {

    if (bill_id <= 0 || account_id <= 0 || book_id <= 0 || num <= 0 || total_price < 0) {
        return false;
    }

    bill_t newBill;
    newBill.bill_id = bill_id;
    newBill.account_id = account_id;
    newBill.book_id = book_id;
    newBill.num = num;
    newBill.total_price = total_price;

    return billMapper.addbyOne(&newBill);
}

// 删除账单：成功返回 true，失败返回 false
bool Delete_Bill( int bill_id) {
    // 参数校验
    if (bill_id <= 0) {
        return false;
    }

    // 调用 BillMapper 的 deletebyId 方法
    return billMapper.deletebyId(bill_id);
}

// 查询单条账单：返回账单信息，若不存在则返回空结构体（bill_id = 0）
bill_t Search_Bill_One( int bill_id) {
    if (bill_id <= 0) {
        bill_t empty;
        empty.bill_id = 0; // 标记为无效
        return empty;
    }

    return billMapper.getbyBillId(bill_id);
}

// 修改账单：根据 bill_id 更新账单的全部字段
// 成功返回 true，失败（如账单不存在或参数非法）返回 false
bool Revise_Bill(int bill_id,int account_id,int book_id,int num,float total_price) {

    // 1. 参数合法性校验
    if (bill_id <= 0 || account_id <= 0 || book_id <= 0) {
        return false;
    }
    if (num <= 0) {
        return false; // 数量必须大于 0
    }
    if (total_price < 0.0f) {
        return false; // 总价不能为负
    }

    // 2. 检查账单是否存在
    bill_t existing = billMapper.getbyBillId(bill_id);
    if (existing.bill_id != bill_id) {
        return false; // 账单不存在，无法修改
    }

    // 3. 构造更新后的账单对象
    bill_t updated;
    updated.bill_id = bill_id;         // 保持原 ID 不变
    updated.account_id = account_id;
    updated.book_id = book_id;
    updated.num = num;
    updated.total_price = total_price;

    // 4. 执行更新
    return billMapper.updatebyOne(&updated);
}

// 比较函数：按 total_price 升序
static int compare_by_amount(const void* a, const void* b) {
    const bill_t* x = (const bill_t*)a;
    const bill_t* y = (const bill_t*)b;
    if (x->total_price < y->total_price) return -1;
    if (x->total_price > y->total_price) return 1;
    return 0;
}

// 查询并返回按金额升序排序的账单副本
// 调用方必须 free() 返回的指针
bill_t* Search_Bill_All_Sorted() {

    int count = billMapper.get_bookcount();
    const bill_t* src = billMapper.getbyAll();



    if (count <= 0 || !src) {
        return NULL;
    }

    size_t size = sizeof(bill_t) * count;
    bill_t* sorted = (bill_t*)malloc(size);
    if (!sorted) {
        return NULL;
    }

    memcpy(sorted, src, size);
    qsort(sorted, count, sizeof(bill_t), compare_by_amount);

    return sorted;
}