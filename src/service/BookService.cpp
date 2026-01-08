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



// 希尔排序实现
void shell_sort(book_t* books, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            book_t temp = books[i];
            int j;
            for (j = i; j >= gap && books[j - gap].price > temp.price; j -= gap) {
                books[j] = books[j - gap];
            }
            books[j] = temp;
        }
    }
}


//用希尔排序对书本按金额排序，升序，打印出来
void XeSearchByMoney() {
    // 1. 获取所有账单
    book_t* all_bills = bookMapper.getbyAll();
    int count = bookMapper.get_bookcount();

    if (all_bills == nullptr || count == 0) {
        printf(" 暂无账单记录！\n");
        return;
    }

    // 2. 创建副本进行排序（避免修改原始数据）
    book_t* sorted_books = new book_t[count];
    for (int i = 0; i < count; i++) {
        sorted_books[i] = all_bills[i];
    }

    // 3. 希尔排序：按 total_price 升序
    shell_sort(sorted_books, count);

    // 4. 打印结果
    for (int i = 0; i < count; i++) {
        book_t* book = &sorted_books[i];
        printf("=== 找到图书 ===\n");
        printf("ID: %d, 名称: %s, 价格: %.2f, 总数: %d, 借阅: %d\n",
            book->book_id, book->book_name, book->price, book->total, book->borrow);
        printf("类别: %s, 作者: %s, 出版日期: %s\n\n",
            book->type, book->author, book->pubish_date);
    }

    // 5. 释放内存
    delete[] sorted_books;
}


// 辅助函数：对 books 数组按 pubish_date 进行 LSD 基数排序（升序）
void radix_sort_by_date(book_t* books, int n) {
    if (n <= 1) return;

    // 排序的位索引顺序：从最低有效数字位到最高
    // 日期格式：YYYY-MM-DD → 索引 0～9
    // 有效数字位（从右到左）：9(D), 8(D), 6(M), 5(M), 3(Y), 2(Y), 1(Y), 0(Y)
    int digit_positions[] = { 9, 8, 6, 5, 3, 2, 1, 0 };
    int num_digits = sizeof(digit_positions) / sizeof(digit_positions[0]);

    book_t* output = new book_t[n];

    // 从最低位到最高位进行计数排序
    for (int d = 0; d < num_digits; d++) {
        int pos = digit_positions[d];

        // 计数数组：'0' 到 '9' → 0～9
        int count[10] = { 0 };

        // 统计每个数字出现次数
        for (int i = 0; i < n; i++) {
            char c = books[i].pubish_date[pos];
            count[c - '0']++;
        }

        // 计算前缀和（变为位置索引）
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // 从后往前填充 output（保证稳定性）
        for (int i = n - 1; i >= 0; i--) {
            char c = books[i].pubish_date[pos];
            int index = --count[c - '0'];
            output[index] = books[i];
        }

        // 将 output 复制回 books
        for (int i = 0; i < n; i++) {
            books[i] = output[i];
        }
    }

    delete[] output;
}

//对书籍的出版日期进行基数排序（升序）
void Js_sort() {
    book_t* all_books = bookMapper.getbyAll();
    int count = bookMapper.get_bookcount();

    if (all_books == nullptr || count == 0) {
        std::cout << " 无图书数据！\n";
        return;
    }

    // 创建副本进行排序
    book_t* sorted_books = new book_t[count];
    for (int i = 0; i < count; i++) {
        sorted_books[i] = all_books[i];
    }

    // 基数排序
    radix_sort_by_date(sorted_books, count);

    // 打印结果
    for (int i = 0; i < count; i++) {
        book_t* book = &sorted_books[i];
        printf("=== 找到图书 ===\n");
        printf("ID: %d, 名称: %s, 价格: %.2f, 总数: %d, 借阅: %d\n",
            book->book_id, book->book_name, book->price, book->total, book->borrow);
        printf("类别: %s, 作者: %s, 出版日期: %s\n\n",
            book->type, book->author, book->pubish_date);
    }

    delete[] sorted_books;
}





// 分区函数：按 total 排序
int partition(book_t* books, int low, int high) {
    int pivot = books[high].total-books[high].borrow;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (books[j].total - books[j].borrow <= pivot) {
            i++;
            // 交换 books[i] 和 books[j]
            book_t temp = books[i];
            books[i] = books[j];
            books[j] = temp;
        }
    }

    // 将 pivot 放到正确位置
    book_t temp = books[i + 1];
    books[i + 1] = books[high];
    books[high] = temp;

    return i + 1;
}

// 递归快速排序
void quickSort(book_t* books, int low, int high) {
    if (low < high) {
        int pi = partition(books, low, high);
        quickSort(books, low, pi - 1);
        quickSort(books, pi + 1, high);
    }
}

// 主函数：对图书数组按 total - borrow 升序排序
void Q_sort(book_t* books, int n) {
    if (n <= 1) return;
    quickSort(books, 0, n - 1);
}

void QSearchBytotalAndborrow() {
    book_t* all_books = bookMapper.getbyAll();
    int count = bookMapper.get_bookcount();

    if (all_books == nullptr || count == 0) {
        std::cout << " 无图书数据！\n";
        return;
    }

    book_t* sorted_books = new book_t[count];
    for (int i = 0; i < count; i++) {
        sorted_books[i] = all_books[i];
    }

    Q_sort(sorted_books, count);

    for (int i = 0; i < count; i++) {
        book_t* book = &sorted_books[i];
        printf("=== 找到图书 ===\n");
        printf("ID: %d, 名称: %s, 价格: %.2f, 剩余数量: %d\n",
            book->book_id, book->book_name, book->price, book->total-book->borrow);
        printf("类别: %s, 作者: %s, 出版日期: %s\n\n",
            book->type, book->author, book->pubish_date);
    }

    delete[] sorted_books;

}