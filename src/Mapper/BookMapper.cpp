#include "BookMapper.h"

BookMapper::BookMapper(const std::string& filename)
{
	fileManager.set_filename(filename);
}

bool BookMapper::create_list()
{
	books = (book_t*)malloc(sizeof(book_t) * MAX_BOOKS);
	if (!books)
		return false;

	std::vector<book_t> book_array = fileManager.load<book_t>();

	int i = 0;
	for (book_t book : book_array) {
		books[i] = book;
		i++;
	}
	book_count = i;

	return true;
}

book_t* BookMapper::getbyId(int id)
{
	book_t* book = (book_t*)malloc(sizeof(book_t));

	for (int i = 0; i < book_count; i++) {
		if (books[i].book_id == id) {
			*book = books[i];
			return book;
		}
	}

	free(book);
	return nullptr;
}

book_t* BookMapper::getbyBookName(const char bookName[])
{
	book_t* book = (book_t*)malloc(sizeof(book_t));

	for (int i = 0; i < book_count; i++) {
		if (books[i].book_name == bookName) {
			*book = books[i];
			return book;
		}
	}

	return nullptr;
}

bool BookMapper::addbyOne(book_t book)
{


	return false;
}

