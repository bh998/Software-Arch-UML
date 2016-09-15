#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

//another example of inheritance and classes/objects being used in a system
class HouseholdItem : public Item {
private:
	char type[20];
	char brand[20];

public:
	//constructor
	HouseholdItem();

	//getters and setters
	char* getType();
	void setType(char* newType);
	
	char* getBrand();
	void setBrand(char* newBrand);

	//operations
	void printContents();
};