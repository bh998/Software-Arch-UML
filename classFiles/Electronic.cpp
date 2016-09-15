#include "Electronic.h"
#include <iostream>
using namespace std;

//constructors

//getters and setters
char* Electronic::getType() {
	return type;
}
void Electronic::setType(char* newType) {
	strcpy(type, newType);
}

char* Electronic::getBrand() {
	return brand;
}
void Electronic::setBrand(char* newBrand) {
	strcpy(brand, newBrand);
}

//operations
void Electronic::printContents() {
	cout << "Item Id: " << getItemId() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Type: " << getType() << endl;
	cout << "Brand: " << getBrand() << endl;
	cout << "Price: " << getPrice() << endl;
	cout << "Quantity: " << getQuantity() << endl << endl;
}