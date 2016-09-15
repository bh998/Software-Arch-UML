#ifndef Cart_H
#define Cart_H

#include "Cart.h"

#endif

//example of objects and modularity in systems since a user is managed only by this class
//also it shows how composition is used since the user contains a cart and that cart belongs to the user class, since it is deleted when the user is deleted
class User {
private: 
	char username[20];
	char shipAddress[30];
	int creditCard;
	Cart shopCart;
	int id;

public:
	//constructors
	User();
	
	//getters and setters
	char* getUsername();
	void setUsername(char* username);

	char* getShipAddress();
	void setShipAddress(char* address);

	int getCreditCard();
	void setCreditCard(int creditCard);

	Cart getCart();
	void setCart(Cart cart);

	int getId();
	void setId(int id);
};