#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

//example of modularity and inheritance from the item class
class Toy : public Item {
private:
	char type[20];
	int ages;
	char brand[20];

public:
	//constructor

	//getters and setters
	char* getType();
	void setType(char* newType);

	int getAges();
	void setAges(int newAge);

	char* getBrand();
	void setBrand(char* newBrand);

	//operations
	void printContents();
};