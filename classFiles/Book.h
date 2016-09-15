#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

//book class that demostrates how object-oriented classes are used
//also this class inherites from the Item class which is an example of inheritance
class Book : public Item {
private:
	char genre[20];
	bool fiction;
	char author[20];
	char publisher[20];

public:
	//constructor

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
	void printContents();
};