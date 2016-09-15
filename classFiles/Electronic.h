#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

//another example of how objects and inheritance are used to create systems
class Electronic : public Item {
private:
	char type[20];
	char brand[20];

public:

	//getters and setters
	char* getType();
	void setType(char* newType);

	char* getBrand();
	void setBrand(char* newBrand);

	//operations
	void printContents();
};