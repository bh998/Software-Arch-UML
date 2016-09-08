#include "HouseholdItem.h"

//constructors
HouseholdItem::HouseholdItem(char* name, float price, int quantity, int itemId, char* type, char* brand) {
	setName(name);
	setPrice(price);
	setQuantity(quantity);
	setItemId(itemId);
	setType(type);
	setBrand(brand);
	return;
}

//getters and setters
char* HouseholdItem::getType() {
	return type;
}
void HouseholdItem::setType(char* newType) {
	type = newType;
}

char* HouseholdItem::getBrand() {
	return brand;
}
void HouseholdItem::setBrand(char* newBrand) {
	brand = newBrand;
}

//operations