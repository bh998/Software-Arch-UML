#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

class Book : public Item {
private:
	char* genre;
	bool fiction;
	char* author;
	char* publisher;

public:
	//constructor
	Book(char* name, float price, int quantity, int itemId, char* genre, bool fiction, char* author, char* publisher);

	//getters and setters
	char* getGenre();
	void setGenre(char* newGenre);

	bool getFiction();
	void setFiction(bool newFiction);

	char* getAuthor();
	void setAuthor(char* newAuthor);

	char* getPublisher();
	void setPublisher(char* newPublisher);

	//operations
};