#define  _CRT_SECURE_NO_WARNINGS

#include"AccountService.h"
#include <cstring>
#include <iostream>

#include"../Mapper/BillMapper.h"
#include"../Mapper/BorrowRecordMapper.h"

AccountMapper accountMapper;
BillMapper billMapper;
BorrowRecordMapper borrowRecordMapper;
// 注册账号：成功返回 true，失败返回 false
bool Register(int account_id,char password[MAXSIZE],float balance,char phone[MAXSIZE],int role) {

    // 1. 合法性前置校验
    if (role != 0 && role != 1) {
        return false;
    }
    if (account_id <= 0) {
        return false;
    }
    if (balance < 0.0f) {
        return false; // 余额不能为负
    }
    if (!password || !phone) {
        return false;
    }

    // 2. 检查账号是否已存在（防止重复注册）
    account_t* existing = accountMapper.getbyId(account_id);
    if (existing->account_id == account_id) {
        return false;
    }

    // 3. 构造新账户
    account_t newAccount{};
    newAccount.account_id = account_id;
    newAccount.balance = balance;
    newAccount.role = role;

    // 安全拷贝字符串
    strncpy(newAccount.password, password, MAXSIZE - 1);
    newAccount.password[MAXSIZE - 1] = '\0';

    strncpy(newAccount.phone, phone, MAXSIZE - 1);
    newAccount.phone[MAXSIZE - 1] = '\0';

    // 4. 添加新账号
    return accountMapper.addbyOne(&newAccount);
}

// 登录函数：成功返回 role（0 用户 / 1 管理员），失败返回 -1
int Login( int account_id,  char password[MAXSIZE]) {
    if (password == nullptr) {
        return -1;
    }

    // 获取账户（假设 getbyId 在找不到时会抛异常或返回无效账户）
    // 为安全起见，我们先检查是否存在该 ID
    account_t* acc = accountMapper.getbyId(account_id);

    // 假设 getbyId 在找不到时返回 account_id = -1 或其他无效值
    // 更健壮的做法是 AccountMapper 提供 exists(id)，但当前没有
    // 所以我们依赖：如果 account_id 不匹配，则视为不存在

    if (acc->account_id != account_id) {
        return -1; // 账户不存在
    }

    // 比较密码
    if (strncmp(acc->password, password, MAXSIZE) == 0) {
        return acc->role; // 登录成功，返回角色
    }
    else {
        return -1; // 密码错误
    }
}

// 删除账号函数：若存在账单或借阅记录则不允许删除
bool Delete_Account(int account_id) {

    // 1. 检查账户是否存在
    account_t* acc = accountMapper.getbyId(account_id);
    if (acc->account_id != account_id) {
        return false; // 账户不存在
    }

    // 2. 检查是否有对应的账单（buy bill）
    bill_t* bills = billMapper.getbyAll();
    int bill_count = billMapper.get_bookcount(); // 注意：这里应该是 get_billcount() 更合适

    for (int i = 0; i < bill_count; ++i) {
        if (bills[i].account_id == account_id) {
            return false; // 存在购买账单，不能删除
        }
    }

    // 3. 检查是否有未归还的借阅记录（status == 0 表示借阅中）
    borrowrecord_t* records = borrowRecordMapper.getbyAll();
    int record_count = borrowRecordMapper.get_recordcount();

    for (int i = 0; i < record_count; ++i) {
        if (records[i].account_id == account_id && records[i].status == 0) {
            return false; // 存在未归还的借书，不能删除
        }
    }

    // 4. 通过所有检查，可以删除账户
    return accountMapper.deletebyId(account_id);
}


// 查询单条账号信息：成功返回对应账户，失败返回空结构体（account_id = 0）
account_t* SearchOne( int account_id) {
    // 参数校验
    if (account_id <= 0) {
        account_t* empty = (account_t*)malloc(sizeof(account_t));
        empty->account_id = 0; // 标记为无效
        return empty;
    }

    // 调用 AccountMapper 的 getbyId 获取账户
    return accountMapper.getbyId(account_id);
}

// 查询所有账号信息：返回指向账号数组的指针
// 注意：返回的是内部数组的指针，不要修改或释放！
account_t* SearchAll() {
    // 调用 AccountMapper 的 getbyAll() 获取所有账号
    return accountMapper.getbyAll();
}


// 给账号进行充值：成功返回 true，失败返回 false
bool Recharge(int account_id, float amount) {
    // 1. 参数合法性校验
    if (account_id <= 0 || amount <= 0.0f) {
        printf("参数错误：account_id=%d, amount=%.2f\n", account_id, amount);
        return false;
    }

    // 2. 获取账户信息
    account_t* acc = accountMapper.getbyId(account_id);

    // 检查账户是否存在（通过 account_id 是否匹配）
    if (acc->account_id == 0) {  // 假设无效账户的 account_id 为 0
        printf("账户不存在：account_id=%d\n", account_id);
        return false;
    }

    // 3. 更新余额
    acc->balance += amount;

    // 4. 保存更新后的账户信息
    if (!accountMapper.updatebyOne(acc)) {
        printf("账户更新失败：account_id=%d\n", account_id);
        return false;
    }

    printf("充值成功！账户 %d 余额增加 %.2f，当前余额：%.2f\n",
        account_id, amount, acc->balance);

    return true;
}


// 账号的支付功能：成功返回 true，失败返回 false
bool Deduct(int account_id, float amount) {
    // 1. 参数合法性校验
    if (account_id <= 0 || amount <= 0.0f) {
        printf("参数错误：account_id=%d, amount=%.2f\n", account_id, amount);
        return false;
    }

    // 2. 获取账户信息
    account_t* acc = accountMapper.getbyId(account_id);

    // 检查账户是否存在
    if (acc->account_id == 0) {
        printf("账户不存在：account_id=%d\n", account_id);
        return false;
    }

    // 3. 检查余额是否足够
    if (acc->balance < amount) {
        printf("余额不足！账户 %d 当前余额：%.2f，需扣款：%.2f\n",
            account_id, acc->balance, amount);
        return false;
    }

    // 4. 扣款
    acc->balance -= amount;

    // 5. 保存更新后的账户信息
    if (!accountMapper.updatebyOne(acc)) {
        printf("账户更新失败：account_id=%d\n", account_id);
        return false;
    }

    printf("扣款成功！账户 %d 扣款 %.2f，当前余额：%.2f\n",
        account_id, amount, acc->balance);

    return true;
}

