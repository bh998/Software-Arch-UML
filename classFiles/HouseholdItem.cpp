//this file is the cpp file that controls all the methods of the household item class
//this demostrates modularity in that it controls the household item class completely and all of its attributes
//it also shows inheritance since it inherits from items

#include "HouseholdItem.h"
#include <iostream>
#include <iomanip>
using namespace std;

HouseholdItem::HouseholdItem() {
	setItemId(0);
}

//getters and setters
char* HouseholdItem::getType() {
	return type;
}
void HouseholdItem::setType(char* newType) {
	strcpy(type, newType);
}

char* HouseholdItem::getBrand() {
	return brand;
}
void HouseholdItem::setBrand(char* newBrand) {
	strcpy(brand, newBrand);
}

//operations
void HouseholdItem::printContents() {
	cout << "Item Id: " << getItemId() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Type: " << getType() << endl;
	cout << "Brand: " << getBrand() << endl;
	cout << fixed << setprecision(2) << "Price: " << getPrice() << endl;
	cout << "Quantity: " << getQuantity() << endl << endl;
}