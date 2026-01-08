#define  _CRT_SECURE_NO_WARNINGS
#include"BookService.h"
#include <string.h>

//创建图书：成功返回 true，失败返回 false
bool Create_Book(int book_id, char book_name[MAXSIZE], float price, int total, int borrow,char type[MAXSIZE], char author[MAXSIZE], char publish_date[MAXSIZE]) {
    // 参数合法性检查
    if (book_id <= 0 || price < 0 || total < 0 || borrow < 0) {
        return false;
    }

    // 检查是否已存在相同 ID 的书
    book_t* existing = bookMapper.getbyId(book_id);
    if (existing != nullptr) {
        printf("图书编号 %d 已存在！\n", book_id);
        return false;
    }

    // 构造新书
    book_t newBook;
    newBook.book_id = book_id;
    strcpy_s(newBook.book_name, MAXSIZE, book_name);
    newBook.price = price;
    newBook.total = total;
    newBook.borrow = borrow;
    strcpy_s(newBook.type, MAXSIZE, type);
    strcpy_s(newBook.author, MAXSIZE, author);
    strcpy_s(newBook.pubish_date, MAXSIZE, publish_date);  // 注意：拼写错误，应为 publish_date

    // 添加到数据库
    return bookMapper.addbyOne(&newBook);
}

// 删除图书：成功返回 true，失败返回 false
bool Delete_Book(int book_id) {
    if (book_id <= 0) {
        return false;
    }

    // 检查是否存在
    book_t* book = bookMapper.getbyId(book_id);
    if (book == nullptr) {
        printf("图书编号 %d 不存在！\n", book_id);
        return false;
    }

    // 删除操作
    return bookMapper.deletebyId(book_id);
}

// 修改图书：成功返回 true，失败返回 false
bool Revise_Book(int book_id, char book_name[MAXSIZE], float price, int total, int borrow,char type[MAXSIZE], char author[MAXSIZE], char publish_date[MAXSIZE]) {
    // 1. 参数合法性校验
    if (book_id <= 0 || price < 0 || total < 0 || borrow < 0) {
        printf("参数错误：book_id=%d, price=%.2f, total=%d, borrow=%d\n",
            book_id, price, total, borrow);
        return false;
    }

    // 2. 获取原图书信息
    book_t* book = bookMapper.getbyId(book_id);
    if (book == nullptr) {
        printf("图书编号 %d 不存在！\n", book_id);
        return false;
    }

    // 3. 更新字段（使用 strcpy_s 防止越界）
    strcpy_s(book->book_name, MAXSIZE, book_name);
    book->price = price;
    book->total = total;
    book->borrow = borrow;
    strcpy_s(book->type, MAXSIZE, type);
    strcpy_s(book->author, MAXSIZE, author);
    strcpy_s(book->pubish_date, MAXSIZE, publish_date);  // 注意拼写：pubish_date

    // 4. 保存到文件
    if (!bookMapper.updatebyOne(book)) {
        printf("图书更新失败！\n");
        return false;
    }

    printf("图书修改成功！ID: %d\n", book_id);
    return true;
}

//根据类型和书名和作者查找图书：成功返回 true，失败返回 false
bool Search_Book(char type[MAXSIZE], char book_name[MAXSIZE], char author[MAXSIZE]) {
    // 获取所有图书
    int count = bookMapper.get_bookcount();
    book_t* books = bookMapper.getbyAll();

    if (count <= 0 || !books) {
        printf("暂无图书数据。\n");
        return false;
    }

    bool found = false;
    for (int i = 0; i < count; i++) {
        book_t* book = &books[i];
        bool match = true;

        // 判断是否匹配条件（任意一个条件满足即可）
        if (type[0] != '\0' && strcmp(book->type, type) != 0) match = false;
        if (book_name[0] != '\0' && strcmp(book->book_name, book_name) != 0) match = false;
        if (author[0] != '\0' && strcmp(book->author, author) != 0) match = false;

        if (match) {
            printf("=== 找到图书 ===\n");
            printf("ID: %d, 名称: %s, 价格: %.2f, 总数: %d, 借阅: %d\n",
                book->book_id, book->book_name, book->price, book->total, book->borrow);
            printf("类别: %s, 作者: %s, 出版日期: %s\n\n",
                book->type, book->author, book->pubish_date);
            found = true;
        }
    }

    if (!found) {
        printf("未找到符合条件的图书。\n");
    }

    return found;
}


// 查询所有书籍，返回指向图书数组的指针
// 若无书籍则返回 nullptr
bool SearchAll() {
    // 获取所有图书
    int count = bookMapper.get_bookcount();
    book_t* books = bookMapper.getbyAll();

    if (count <= 0 || !books) {
        printf("暂无图书数据。\n");
        return false;
    }

    for (int i = 0; i < count; i++) {
        book_t* book = &books[i];
            printf("=== 找到图书 ===\n");
            printf("ID: %d, 名称: %s, 价格: %.2f, 总数: %d, 借阅: %d\n",
                book->book_id, book->book_name, book->price, book->total, book->borrow);
            printf("类别: %s, 作者: %s, 出版日期: %s\n\n",
                book->type, book->author, book->pubish_date);     
    }
    return true;
}
