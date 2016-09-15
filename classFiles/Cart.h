#ifndef Item_H
#define Item_H

#include "Item.h"

#endif

//cart class that demostrates how object-oriented classes are used
class Cart{
private:
	int id;
	Item items[20];
	float prices[20];
	int quantities[20];
	float total = 0;

public:
	//constructors
	Cart(); 


	//functions like these shows modularity since it shows how single functions do single pieces of functionality and can be reused for cleaner code
	//getters and setters
	int getId();
	void setId(int id);

	Item* getItems();
	void setItems(Item* items);

	float* getPrices();
	void setPrices(float* prices);

	int* getQuantities();
	void setQuantities(int* quanitities);

	float getTotal();
	void setTotal(float total);

	//functions
	void printContents();
};
