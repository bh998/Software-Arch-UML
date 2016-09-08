#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

class HouseholdItem : public Item {
private:
	char* type;
	char* brand;

public:
	//constructors
	HouseholdItem(char* name, float price, int quantity, int itemId, char* type, char* brand);

	//getters and setters
	char* getType();
	void setType(char* newType);
	
	char* getBrand();
	void setBrand(char* newBrand);

	//operations
};