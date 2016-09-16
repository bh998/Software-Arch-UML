//this class shows modularity since this one class controls everything related to the user except for accessing the database
//it contains all the functions and attributes that are needed to work with a user object

#include "User.h"
#include <string.h>
#include <iostream>

using namespace std;

//constructors
User::User(){
	return;
}

//getters and setters
char* User::getUsername() {
	return username;
}
void User::setUsername(char* newUsername) {
	strcpy(username, newUsername);
}

char* User::getShipAddress() {
	return shipAddress;
}
void User::setShipAddress(char* address) {
	strcpy(shipAddress,address);
}

int User::getCreditCard() {
	return creditCard;
}
void User::setCreditCard(int cardNum) {
	creditCard = cardNum;
}

Cart User::getCart() {
	return shopCart;
}
void User::setCart(Cart cart){
	shopCart = cart;
}

int User::getId() {
	return id;
}
void User::setId(int newId) {
	id = newId;
}

//functions




