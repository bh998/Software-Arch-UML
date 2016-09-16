//this files controls the entire purchase class and is another example of how classes and obejcts work

#include "Purchase.h"
#include <iostream>
#include <iomanip>
using namespace std;

//constructor
Purchase::Purchase() {
	setPurchaseId(0);
}

//getters and setters
Item* Purchase::getItems(){
	return items;
}
void Purchase::setItems(Item* itemList) {
	memcpy(items, itemList, sizeof(items));
	return;
}

float* Purchase::getPrices() {
	return prices;
}
void Purchase::setPrices(float* priceList) {
	memcpy(prices, priceList, sizeof(prices));
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
	memcpy(shipAddress, address, sizeof(shipAddress));
	return;
}

char* Purchase::getUsername() {
	return username;
}
void Purchase::setUsername(char* user) {
	memcpy(username, user, sizeof(username));
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
	memcpy(quantities, quantityNum, sizeof(quantities));
}

//operations
void Purchase::printContents() {
	cout << endl;
	int count = 0;

	cout << "Purchase Id: " << getPurchaseId() << endl << endl;
	while (true) {
		if (getItems()[count].getItemId() == 0 || getPurchaseId() == 0) {
			break;
		}
		cout << "Name: " << getItems()[count].getName() << endl;
		cout << fixed << setprecision(2) << "Price: " << getPrices()[count] << endl;
		cout << "Quantity: " << getQuantities()[count] << endl << endl;
		count++;
	}

	cout << "User: " << getUsername() << endl;
	cout << "Address: " << getShipAddress() << endl;
	cout << "Credit Card: " << getCreditCard() << endl;
	cout << "Total: " << getTotal() << endl << endl;

	return;
}