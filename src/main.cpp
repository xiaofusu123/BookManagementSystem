#include "FileManager/FileManager.h"
#include "Mapper/BookMapper.h"

#include "Controller/Controll.h"

void Test()
{
	FileManager fileManager("wkt.dat");
	fileManager.create();

	BookMapper bookMapper("wkt.dat");

	int n = 5;
	book_t* book = (book_t*)malloc(sizeof(book_t) * n);
	if (!book) {
		std::cerr << "ÄÚ´æ·ÖÅäÊ§°Ü" << std::endl;
		return;
	}

	for (int i = 0; i < n; i++) {
		book[i].book_id = i;
		strcpy_s(book[i].book_name, MAXSIZE, "null");
		book[i].total = 0;
		book[i].borrow = 0;
		book[i].price = 0.0f;
		strcpy_s(book[i].author, MAXSIZE, "null");
		strcpy_s(book[i].type, MAXSIZE, "null");
		strcpy_s(book[i].pubish_date, MAXSIZE, "null");
	}

	bookMapper.addbyBatch(book, n);
	bookMapper.deletebyId(0);
	free(book);
}

int main()
{
	Controller();

	return 0;
}
