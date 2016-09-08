class Item {
private:
	char* name;
	float price;
	int quantity;
	int itemId;

public:
	//constructor
	Item();
	Item(char* name, float price, int quantity, int itemId);

	//getters and setters
	char* getName();
	void setName(char* newName);

	float getPrice();
	void setPrice(float newPrice);

	int getQuantity();
	void setQuantity(int newQuantity);

	int getItemId();
	void setItemId(int newItemId);

	//operations

};