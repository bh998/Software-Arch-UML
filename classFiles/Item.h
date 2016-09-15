//this class shows how classes fit into a system and this class will also be used as a base class for other classes
class Item {
private:
	char name[20];
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