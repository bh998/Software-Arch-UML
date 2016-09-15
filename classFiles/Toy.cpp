#include "Toy.h"
#include <iostream>
using namespace std;

//constructors

//getters and setters
char* Toy::getType() {
	return type;
}
void Toy::setType(char* newType) {
	strcpy(type, newType);
}

int Toy::getAges() {
	return ages;
}
void Toy::setAges(int newAge) {
	ages = newAge;
}

char* Toy::getBrand() {
	return brand;
}
void Toy::setBrand(char* newBrand) {
	strcpy(brand, newBrand);
}

//operations
void Toy::printContents() {
	cout << "Item Id: " << getItemId() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Type: " << getType() << endl;
	cout << "Ages: " << getAges() << "+" << endl;
	cout << "Brand: " << getBrand() << endl;
	cout << "Price: " << getPrice() << endl;
	cout << "Quantity: " << getQuantity() << endl << endl;
}
