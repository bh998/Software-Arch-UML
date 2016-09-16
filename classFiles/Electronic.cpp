//this file is the cpp file that controls all the methods of the electronic class
//this demostrates modularity in that it controls the electronic class completely and all of its attributes
//it also shows inheritance since it inherits from items

#include "Electronic.h"
#include <iostream>
#include <iomanip>
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
	cout << fixed << setprecision(2) << "Price: " << getPrice() << endl;
	cout << "Quantity: " << getQuantity() << endl << endl;
}