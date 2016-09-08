#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

class Electronic : public Item {
private:
	char* type;
	int size;
	char* brand;

public:
	//constructors
	Electronic(char* name, float price, int quantity, int itemId, char* type, int size, char* brand);

	//getters and setters
	char* getType();
	void setType(char* newType);

	int getSize();
	void setSize(int newSize);

	char* getBrand();
	void setBrand(char* newBrand);

	//operations
};