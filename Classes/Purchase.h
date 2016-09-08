#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

class Purchase {
private:
	Item* items;
	float* prices;
	float total;
	int creditCard;
	char* shipAddress;
	int username;
	int purchaseId;
	int* quantities;

public:
	//constructors
	Purchase(Item* itemList, float* priceList, float totalPrice, int creditCardNum, char* address, int user, int id, int* quantityNum);
	
	//getters and setters
	Item* getItems();
	void setItems(Item* itemList);

	float* getPrices();
	void setPrices(float* priceList);

	float getTotal();
	void setTotal(float totalPrice);

	int getCreditCard();
	void setCreditCard(int creditCardNum);

	char* getShipAddress();
	void setShipAddress(char* address);

	int getUsername();
	void setUsername(int user);

	int getPurchaseId();
	void setPurchaseId(int id);

	int* getQuantities();
	void setQuantities(int* quantityNum);

	//operations
	void confirmPurchase();
};