#include "Toy.h"

//constructors
Toy::Toy(char* name, float price, int quantity, int itemId, char* type, int ages, char* brand){
	setName(name);
	setPrice(price);
	setQuantity(quantity);
	setItemId(itemId);
	setType(type);
	setAges(ages);
	setBrand(brand);
	return;
}

//getters and setters
char* Toy::getType() {
	return type;
}
void Toy::setType(char* newType) {
	type = newType;
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
	brand = newBrand;
}

//operations
