//this class shows how modularity is used, in this case it is used to single out an object for communication with the database, so every call to the database is managed by this class

#include "../sqlite3.h"
#include "classFiles.h"

class Database {
private:
	sqlite3* db;

public:
	sqlite3* getDB();
	void open();
	void close();
	User getUser(char* username);
	Cart getCart(int userId);
	Item getItem(int itemId);
	Item* getInventory(int category);
	void addToCart(int itemId, int cartId, int quantity);
	void removeFromCart(int cartId, int itemId);
	void purchaseCart(User user);
	void updateAddress(int userId, char* address);
	void updateCreditCard(int userId, char* creditCard);
	void updateInventory(Purchase purchase);
	void emptyCart(User user);
	void addPurchase(Purchase purchase, int userId);
	void addPurchaseItems(Purchase purchase);
	void printPurchaseHistory(User user);
	static int usernameCallback(void *NotUsed, int argc, char **argv, char **azColName);
	void getHouseholdItems();
	void getElectronics();
	void getToys();
	void getBooks();
};
