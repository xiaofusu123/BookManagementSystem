#include "BookMapper.h"
#include "BorrowRecordMapper.h"

BookMapper::BookMapper()
{
	const char* filename = "../data/Book.dat";
	fileManager.set_filename(filename);
	fileManager.create();
	create_list();
}

BookMapper::BookMapper(const std::string& filename)
{
	fileManager.set_filename(filename);
	create_list();
}

BookMapper::~BookMapper()
{
	fileManager.save(books, book_count);

	free(books);
	books = NULL;
}

bool BookMapper::create_list()
{
	books = (book_t*)malloc(sizeof(book_t) * MAXNUMBER);
	if (!books)
		return false;

	std::vector<book_t> book_array = fileManager.load<book_t>();

	int i;
	for (i = 0; i < book_array.size(); i++) {
		books[i] = book_array[i];
	}
	book_count = i;

	return true;
}

book_t* BookMapper::getbyId(int id)
{
	book_t* book = (book_t*)malloc(sizeof(book_t));
	if (!book)
		return nullptr;

	for (int i = 0; i < book_count; i++) {
		if (books[i].book_id == id) {
			*book = books[i];
			return book;
		}
	}

	free(book);
	book = NULL;
	return nullptr;
}

book_t* BookMapper::getbyBookName(const char bookName[])
{
	book_t* book = (book_t*)malloc(sizeof(book_t));
	if (!book)
		return nullptr;

	for (int i = 0; i < book_count; i++) {
		if (books[i].book_name == bookName) {
			*book = books[i];
			return book;
		}
	}

	return nullptr;
}

bool BookMapper::addbyOne(book_t* book)
{
	if (!book || book_count + 1 > MAXNUMBER)
		return false;

	books[book_count++] = *book;
	return true;
}

bool BookMapper::addbyBatch(book_t book[], int n)
{
	if (!book || book_count + n > MAXNUMBER)
		return false;

	for (int i = 0; i < n; i++)
		books[book_count++] = book[i];

	return true;
}

bool BookMapper::deletebyId(int id)
{
	int i;
	bool exist = false;

	for (i = 0; i < book_count; i++) {
		if (!exist) {
			if (books->book_id == id)
				exist = true;
		}
		else {
			books[i - 1] = books[i];
		}
	}
	book_count--;

	return exist;
}

bool BookMapper::deletebyBookName(const char bookName[])
{
	int i;
	bool exist = false;

	for (i = 0; i < book_count; i++) {
		if (!exist) {
			if (strcmp(books[i].book_name, bookName) == 0)
				exist = true;
		}
		else {
			books[i - 1] = books[i];
		}
	}
	book_count--;

	return exist;
}

bool BookMapper::deletebyAll()
{
	book_count = 0;
	return true;
}

bool BookMapper::updatebyOne(book_t* book)
{
	for (int i = 0; i < book_count; i++) {
		if (books[i].book_id == book->book_id) {
			books[i] = *book;
			return true;
		}
	}

	return false;
}

bool BookMapper::updatebyBatch(book_t book[], int n)
{
	int j;
	for (int i = 0; i < n; i++) {
		for (j = 0; j < book_count; j++) {
			if (books[j].book_id == book[i].book_id) {
				books[j] = book[i];
				break;
			}
		}
	}

	return true;
}

bool BookMapper::SaveBookData()
{
	return fileManager.save(books, book_count);
}
