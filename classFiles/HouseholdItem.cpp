#include "HouseholdItem.h"
#include <iostream>
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
	cout << "Price: " << getPrice() << endl;
	cout << "Quantity: " << getQuantity() << endl << endl;
}