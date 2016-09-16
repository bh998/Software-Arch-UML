//this file shows off classes since it is the file that controls the cart class

#ifndef Cart_H
#define Cart_H

#include "Cart.h"

#endif

#ifndef Database_H
#define Database_H

#include "Database.h"

#endif

#include <iostream>
#include <iomanip>
using namespace std;

//constructors
Cart::Cart() {
	return;
}

//getters and setters
int Cart::getId() {
	return id;
}
void Cart::setId(int newId) {
	id = newId;
}

Item* Cart::getItems() {
	return items;
}
void Cart::setItems(Item* newItems) {
	memcpy(items, newItems, sizeof(items));
}

float* Cart::getPrices() {
	return prices;
}
void Cart::setPrices(float* newPrices) {
	memcpy(prices, newPrices, sizeof(prices));
}

int* Cart::getQuantities() {
	return quantities;
}
void Cart::setQuantities(int* newQuantities) {
	memcpy(quantities, newQuantities, sizeof(prices));
}

float Cart::getTotal() {
	return total;
}
void Cart::setTotal(float newTotal) {
	total += newTotal;
}

void Cart::printContents() {
	int count = 0;
	cout << "Cart:" << endl;
	while (true) {
		if (getItems()[count].getItemId() == 0) {
			break;
		}
		cout << "Id: " << items[count].getItemId() << endl;
		cout << "Name: " << items[count].getName() << endl;
		cout << fixed << setprecision(2) << "Price: $" << prices[count] << endl;
		cout << "Quantity: " << quantities[count] << endl;
		cout << endl;
		count++;
	}

	cout << fixed << setprecision(2) << "Total: $" << getTotal() << endl << endl;
}

