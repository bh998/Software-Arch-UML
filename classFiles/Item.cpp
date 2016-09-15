#include "Item.h"
#include <string.h>

//constructor
Item::Item() {
	setItemId(0);
	return;
}
Item::Item(char* name, float price, int quantity, int itemId) {
	setName(name);
	setPrice(price);
	setQuantity(quantity);
	setItemId(itemId);
}


//getters and setters
char* Item::getName() {
	return name;
}
void Item::setName(char* newName) {
	strcpy(name, newName);
	return;
}

float Item::getPrice() {
	return price;
};
void Item::setPrice(float newPrice) {
	price = newPrice;
	return;
}

int Item::getQuantity() {
	return quantity;
}
void Item::setQuantity(int newQuantity) {
	quantity = newQuantity;
}

int Item::getItemId() {
	return itemId;
}
void Item::setItemId(int newItemId) {
	itemId = newItemId;
}


//operations