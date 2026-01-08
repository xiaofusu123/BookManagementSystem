#define  _CRT_SECURE_NO_WARNINGS
#include"AccountService.h"

#include <string.h>
#include <stdlib.h>

//获取自增id
int get_next_bill_id(bill_t* bills) {
    int count = billMapper.get_bookcount();
    if (count == 0) return 1;
    int max_id = bills[0].bill_id;
    for (int i = 1; i < count; i++) {
        if (bills[i].bill_id > max_id) {
            max_id = bills[i].bill_id;
        }
    }
    return max_id + 1;
}

//创建账单：成功返回 true，失败返回 false
bool Create_Bill(int account_id, char book_name[MAXSIZE], int num) {
    // 1. 校验参数
    if (account_id <= 0 || strlen(book_name) == 0 || num <= 0) {
        printf("参数错误！\n");
        return false;
    }

    // 2. 获取用户账户
    account_t* account = accountMapper.getbyId(account_id);
    if (!account) {
        printf("账号 %d 不存在！\n", account_id);
        return false;
    }

    // 3. 获取图书信息
    book_t* book = bookMapper.getbyBookName(book_name);
    if (!book) {
        printf("图书《%s》不存在！\n", book_name);
        return false;
    }

    // 4. 检查库存是否足够
    if (book->total < num) {
        printf("库存不足！《%s》剩余：%d，您要借：%d\n", book_name, book->total, num);
        return false;
    }

    // 5. 计算总价
    float total_price = num * book->price;

    // 6. 检查余额是否足够
    if (account->balance < total_price) {
        printf("余额不足！需支付 %.2f，当前余额 %.2f\n", total_price, account->balance);
        return false;
    }

    // 7. 生成唯一的 bill_id（自增）
    int new_bill_id = get_next_bill_id(billMapper.getbyAll());  // 假设你有这个方法

    // 8. 创建账单
    bill_t* new_bill = new bill_t;
    new_bill->bill_id = new_bill_id;
    new_bill->account_id = account_id;
    new_bill->book_id = book->book_id;
    new_bill->num = num;
    new_bill->total_price = total_price;

    // 9. 扣减用户余额
    account->balance -= total_price;

    // 10. 减少书籍库存
    book->total -= num;

    // 11. 添加账单到数据库
    bool added = billMapper.addbyOne(new_bill);

    // 12. 保存所有变更
    bool account_saved = accountMapper.updatebyOne(account);
    bool book_saved = bookMapper.updatebyOne(book);

    if (added && account_saved && book_saved) {
        printf(" 账单创建成功！\n");
        printf("账单ID：%d，书名：《%s》，数量：%d，总价：%.2f\n",
            new_bill_id, book_name, num, total_price);
        return true;
    }
    else {
        printf(" 创建失败！请检查文件权限或数据一致性。\n");
        delete new_bill;  // 防止内存泄漏
        return false;
    }
}

// 删除账单(相当于退款)：成功返回 true，失败返回 false
bool Delete_Bill(int bill_id) {
    // 1. 查找账单
    bill_t* bill = billMapper.getbyBillId(bill_id);
    if (!bill) {
        printf(" 错误：账单ID %d 不存在。\n", bill_id);
        return false;
    }

    // 2. 获取用户账户
    account_t* account = accountMapper.getbyId(bill->account_id);
    if (!account) {
        printf(" 错误：用户ID %d 不存在。\n", bill->account_id);
        return false;
    }

    // 3. 获取图书信息
    book_t* book = bookMapper.getbyId(bill->book_id);
    if (!book) {
        printf(" 错误：图书ID %d 不存在。\n", bill->book_id);
        return false;
    }

    // 4. 退款：用户余额增加
    account->balance += bill->total_price;

    // 5. 归还书籍：库存增加
    book->total += bill->num;

    // 6. 删除账单记录
    bool deleted = billMapper.deletebyId(bill_id);

    // 7. 保存所有更改
    bool account_ok = accountMapper.updatebyOne(account);
    bool book_ok = bookMapper.updatebyOne(book);
  

    if (deleted && account_ok && book_ok) {
        printf(" 删除成功！\n");
        printf(" 用户 %d 余额 +%.2f\n", account->account_id, bill->total_price);
        printf(" 图书《%s》库存 +%d\n", book->book_name, bill->num);
        return true;
    }
    else {
        printf(" 操作失败！请检查数据是否一致或文件权限。\n");
        return false;
    }
}

// 查询单条账单：返回账单信息，若不存在则返回空结构体（bill_id = 0）
bill_t* Search_Bill_One( int account_id) {
    // 参数校验
    if (account_id <= 0) {
        return NULL;
    }
    // 调用 BillMapper 的 getbyBillId 方法
    bill_t* bill = billMapper.getbyBillId(account_id);
    if (!bill) {
        return NULL; // 账单不存在
    }
    return bill;
}


// 修改账单相当于退款后重新创建账单
// 成功返回 true，失败（如账单不存在或参数非法）返回 false
bool Revise_Bill(int account_id, char book_name[MAXSIZE]) {
    if (account_id <= 0 || strlen(book_name) == 0) {
        printf("参数错误！\n");
        return false;
    }

    // 1. 获取账户
    account_t* account = accountMapper.getbyId(account_id);
    if (!account) {
        printf("账号 %d 不存在！\n", account_id);
        return false;
    }

    // 2. 查找匹配账单
    int total_bills = billMapper.get_bookcount();
    bool found = false;

    for (int i = 1; i <= total_bills; i++) {
        bill_t* bill = billMapper.getbyBookId(i);
        if (!bill || bill->account_id != account_id) continue;

        book_t* old_book = bookMapper.getbyId(bill->book_id);
        if (!old_book) continue;

        if (strcmp(old_book->book_name, book_name) == 0) {
            found = true;
            int old_num = bill->num;

            printf("找到账单：《%s》，当前数量：%d\n", book_name, old_num);

            // 3. 输入新书名和数量
            char new_book_name[MAXSIZE];
            int new_num;
            printf("请输入新的书籍名称：");
            scanf("%s", new_book_name);
            printf("请输入新的借阅数量：");
            scanf("%d", &new_num);

            if (strlen(new_book_name) == 0 || new_num <= 0) {
                printf("输入非法！\n");
                return false;
            }

            // 4. 查找新书
            book_t* new_book = bookMapper.getbyBookName(new_book_name);
            if (!new_book) {
                printf("新书《%s》不存在！\n", new_book_name);
                return false;
            }

            // 5. 【关键校验】新书库存是否足够？
            if (new_book->total == new_num) {
                printf(" 库存不足！\n");
                printf("《%s》剩余：%d，您想借：%d\n", new_book_name, new_book->total, new_num);
                return false;
            }

            // 6. 计算价格变化
            float old_total_price = bill->total_price;
            float new_total_price = new_num * new_book->price;
            float delta = new_total_price - old_total_price;

            // 7. 检查余额
            if (delta > 0 && account->balance < delta) {
                printf("余额不足！需支付 %.2f，当前余额 %.2f\n", delta, account->balance);
                return false;
            }

            // 8. 【关键更新】调整书籍库存
            // 原书：归还（库存增加）
            old_book->total += old_num;
            // 新书：借出（库存减少）
            new_book->total -= new_num;

            // 9. 更新账单
            bill->book_id = new_book->book_id;
            bill->num = new_num;
            bill->total_price = new_total_price;

            // 10. 更新账户余额
            account->balance -= delta;

            // 11. 保存所有数据
            bool ok1 = billMapper.updatebyOne(bill);
            bool ok2 = bookMapper.updatebyOne(old_book);  // 原书库存增加
            bool ok3 = bookMapper.updatebyOne(new_book);  // 新书库存减少
            bool ok4 = accountMapper.updatebyOne(account);

            if (ok1 && ok2 && ok3 && ok4) {
                printf(" 修改成功！\n");
                printf("新书名：《%s》，新数量：%d，新总价：%.2f，账户余额：%.2f\n",
                    new_book_name, new_num, new_total_price, account->balance);
                return true;
            }
            else {
                printf("保存失败！请检查文件权限或 Mapper 实现。\n");
                return false;
            }
        }
    }

    if (!found) {
        printf("未找到账单！\n");
    }
    return false;
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

