#include "Electronic.h"

//constructors
Electronic::Electronic(char* name, float price, int quantity, int itemId, char* type, int size, char* brand) {
	setName(name);
	setPrice(price);
	setQuantity(quantity);
	setItemId(itemId);
	setType(type);
	setSize(size);
	setBrand(brand);
	return;
}

//getters and setters
char* Electronic::getType() {
	return type;
}
void Electronic::setType(char* newType) {
	type = newType;
}

int Electronic::getSize() {
	return size;
}
void Electronic::setSize(int newSize) {
	size = newSize;
}

char* Electronic::getBrand() {
	return brand;
}
void Electronic::setBrand(char* newBrand) {
	brand = newBrand;
}

//operations