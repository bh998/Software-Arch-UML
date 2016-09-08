#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

class Toy : public Item {
private:
	char* type;
	int ages;
	char* brand;

public:
	//constructor
	Toy(char* name, float price, int quantity, int itemId, char* type, int ages, char* brand);

	//getters and setters
	char* getType();
	void setType(char* newType);

	int getAges();
	void setAges(int newAge);

	char* getBrand();
	void setBrand(char* newBrand);

	//operations
};