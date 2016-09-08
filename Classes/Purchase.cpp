#include "Purchase.h"

//constructor
Purchase::Purchase(Item* itemList, float* priceList, float totalPrice, int creditCardNum, char* address, int user, int id, int* quantityNum) {
	setItems(itemList);
	setPrices(priceList);
	setTotal(totalPrice);
	setCreditCard(creditCardNum);
	setShipAddress(address);
	setUsername(user);
	setPurchaseId(id);
	setQuantities(quantityNum);
}

//getters and setters
Item* Purchase::getItems(){
	return items;
}
void Purchase::setItems(Item* itemList) {
	items = itemList;
	return;
}

float* Purchase::getPrices() {
	return prices;
}
void Purchase::setPrices(float* priceList) {
	prices = priceList;
	return;
}

float Purchase::getTotal() {
	return total;
}
void Purchase::setTotal(float totalPrice) {
	total = totalPrice;
	return;
}

int Purchase::getCreditCard() {
	return creditCard;
}
void Purchase::setCreditCard(int creditCardNum) {
	creditCard = creditCardNum;
	return;
}

char* Purchase::getShipAddress() {
	return shipAddress;
}
void Purchase::setShipAddress(char* address) {
	shipAddress = address;
	return;
}

int Purchase::getUsername() {
	return username;
}
void Purchase::setUsername(int user) {
	username = user;
}

int Purchase::getPurchaseId() {
	return purchaseId;
}
void Purchase::setPurchaseId(int id) {
	purchaseId = id;
	return;
}

int* Purchase::getQuantities() {
	return quantities;
}
void Purchase::setQuantities(int* quantityNum) {
	quantities = quantityNum;
}

//operations
void Purchase::confirmPurchase() {
	//database stuff goes here
	return;
}