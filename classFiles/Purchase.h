#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

//example of how classes are used
//also a good example of modularity since it shows how purchases are completely handled by a single class or object instance
class Purchase {
private:
	Item items[20];
	float prices[20];
	float total;
	int creditCard;
	char shipAddress[30];
	char username[20];
	int purchaseId;
	int quantities[20];

public:
	//constructors
	Purchase();
	
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

	char* getUsername();
	void setUsername(char* user);

	int getPurchaseId();
	void setPurchaseId(int id);

	int* getQuantities();
	void setQuantities(int* quantityNum);

	//operations
	void printContents();
};