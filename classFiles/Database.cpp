#include "classFiles.h"
#include "../defines.h"
#include <iostream>
#include <iomanip>

using namespace std;

sqlite3* Database::getDB() {
	return db;
}

void Database::open() {
	int rc = sqlite3_open(DATABASE, &db);
	if (rc) {
		cout << "error: could not open database.";
		sqlite3_close(db);
	}
	return;
}

void Database::close() {
	int rc = sqlite3_close(db);
	if (rc) {
		cout << "Error: could not close database.";
	}
	return;
}

User Database::getUser(char* username) {
	User user = User();
	Cart cart = Cart();

	open();

	char* build1 = "Select * from User where username = '";
	char* build2 = "';";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(username));
	strcpy(stmt, build1);
	strcat(stmt, username);
	strcat(stmt, build2);

	sqlite3_stmt *selectStmt;
	sqlite3_prepare(getDB(), stmt, strlen(stmt) + 1, &selectStmt, NULL);
	int s;
	s = sqlite3_step(selectStmt);

	if (s == SQLITE_ROW) {
		user.setUsername((char*)sqlite3_column_text(selectStmt, 0));
		user.setShipAddress((char*)sqlite3_column_text(selectStmt, 1));
		user.setCreditCard((int)sqlite3_column_int(selectStmt, 2));
		user.setId((int)sqlite3_column_int(selectStmt, 4));
	}
	if (strcmp(user.getUsername(), username) == 0) {
		loggedIn = true;
		cart = getCart(user.getId());
		user.setCart(cart);
	}

	sqlite3_finalize(selectStmt);
	free(stmt);

	close();

	return user;
}

Cart Database::getCart(int userId) {
	Cart cart = Cart();
	Item items[20] = { Item() };

	char id[10];
	char* build1 = "Select * from Cart_Items where cartId = (select cartId from User where id =";
	char* build2 = ");";
	itoa(userId, id, 10);
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
	strcpy(stmt, build1);
	strcat(stmt, id);
	strcat(stmt, build2);

	sqlite3_stmt *selectStmt;
	sqlite3_prepare(getDB(), stmt, strlen(stmt) + 1, &selectStmt, NULL);

	int count = 0;
	float itemPrices[20] = { 0 };
	int itemQuantities[20] = { 0 };
	while (true) {
		int s;
		s = sqlite3_step(selectStmt);

		if (s == SQLITE_ROW) {
			cart.setId((int)sqlite3_column_int(selectStmt, 0));
			int itemId = (int)sqlite3_column_int(selectStmt, 1);
			items[count] = getItem(itemId);
			itemPrices[count] = items[count].getPrice();
			itemQuantities[count] = (int)sqlite3_column_int(selectStmt, 2);
			count++;
		}
		else if (s == SQLITE_DONE) {
			cart.setId(userId);
			break;
		}
	}
	sqlite3_finalize(selectStmt);
	free(stmt);

	cart.setItems(items);
	cart.setPrices(itemPrices);
	cart.setQuantities(itemQuantities);
	int x = 0;
	while (x < 20) {
		cart.setTotal(cart.getPrices()[x] * cart.getQuantities()[x]);
		x++;
	}

	return cart;
}

Item Database::getItem(int itemId){
	Item item = Item();
	char id[10];

	itoa(itemId, id, 10);
	char* build1 = "Select * from Item where id = ";
	char* build2 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
	strcpy(stmt, build1);
	strcat(stmt, id);
	strcat(stmt, build2);

	sqlite3_stmt *selectStmt;
	sqlite3_prepare(db, stmt, strlen(stmt) + 1, &selectStmt, NULL);
	
	int s = sqlite3_step(selectStmt);
	if (s == SQLITE_ROW) {
		item.setName((char*)sqlite3_column_text(selectStmt, 0));
		item.setPrice((float)sqlite3_column_double(selectStmt, 1));
		item.setQuantity((int)sqlite3_column_int(selectStmt, 2));
		item.setItemId((int)sqlite3_column_int(selectStmt, 3));
	}

	sqlite3_finalize(selectStmt);
	free(stmt);

	return item;
}

void Database::addToCart(int itemId, int cartId, int itemQuantity) {
	open();

	char item[10];
	char cart[10];
	char quantity[10];
	itoa(itemId, item, 10);
	itoa(cartId, cart, 10);
	itoa(itemQuantity, quantity, 10);

	char* error = "Error: item doesn't exist.";

	//insert into Cart_Items values('cartId', (Select id from Item order by name ASC limit 1 offset 'itemNum'));
	char* build1 = "Insert into Cart_Items values(";
	char* build2 = ", ";
	char* build3 = ", ";
	char* build4 = ");";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(cart) + strlen(build2) + strlen(item) + strlen(build3) + strlen(quantity) + strlen(build4));
	strcpy(stmt, build1);
	strcat(stmt, cart);
	strcat(stmt, build2);
	strcat(stmt, item);
	strcat(stmt, build3);
	strcat(stmt, quantity);
	strcat(stmt, build4);

	sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

	close();
}

void Database::removeFromCart(int cartId, int itemId) {
	open();
	
	char* error = "Error: could not remove item from cart.";
	char cart[10];
	char item[10];
	itoa(cartId, cart, 10);
	itoa(itemId, item, 10);

	char* build1 = "delete from Cart_Items where cartId = ";
	char* build2 = " and itemId = ";
	char* build3 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(build3) + strlen(cart) + strlen(item));
	strcpy(stmt, build1);
	strcat(stmt, cart);
	strcat(stmt, build2);
	strcat(stmt, item);
	strcat(stmt, build3);

	sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

	close();
}

void Database::purchaseCart(User user) {
	//purchase the items and create a purchase report(in the form of purchase object)
	Purchase purchase = Purchase();
	purchase.setItems(user.getCart().getItems());
	purchase.setPrices(user.getCart().getPrices());
	purchase.setTotal(user.getCart().getTotal());
	purchase.setCreditCard(user.getCreditCard());
	purchase.setShipAddress(user.getShipAddress());
	purchase.setUsername(user.getUsername());
	purchase.setQuantities(user.getCart().getQuantities());

	//stores the purchase item in database and stores items in purchase to item table
	addPurchase(purchase, user.getId());
	addPurchaseItems(purchase);

	//updates the inventory based on items purchased
	updateInventory(purchase);

	//empties the users cart
	emptyCart(user);

	return;
}

void Database::updateInventory(Purchase purchase) {
	open();
	char* error = "Error: could not update inventory.";

	int count = 0;
	while (true) {
		//update Item set quantity = 'purchase.getQuantity()[count]' where id = 'purchase.getItems()[count].getId();
		if (purchase.getItems()[count].getItemId() == 0) {
			break;
		}
		int newQuantity = purchase.getItems()[count].getQuantity() - purchase.getQuantities()[count];
		char id[20];
		char quantity[20];
		itoa(newQuantity, quantity, 10);
		itoa(purchase.getItems()[count].getItemId(), id, 10);

		char* build1 = "Update Item set quantity = ";
		char* build2 = " where id = ";
		char* build3 = ";";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(build3) + strlen(id) + strlen(quantity));
		strcpy(stmt, build1);
		strcat(stmt, quantity);
		strcat(stmt, build2);
		strcat(stmt, id);
		strcat(stmt, build3);

		sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

		count++;
	}

	close();
}

void Database::updateAddress(int userId, char* address) {
	//update User set address = 'address' where id = 'userId';
	open();

	char* error = "Error: could not update address.";
	char id[10];
	itoa(userId, id, 10);

	char* build1 = "Update User set address = '";
	char* build2 = "' where id = ";
	char* build3 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id) + strlen(address) + strlen(build3));
	strcpy(stmt, build1);
	strcat(stmt, address);
	strcat(stmt, build2);
	strcat(stmt, id);
	strcat(stmt, build3);

	sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

	close();
	return;
}

void Database::updateCreditCard(int userId, char* creditCard) {
	//update User set creditCard = 'creditCard' where id = 'userId';
	open();

	char* error = "Error: could not update address.";
	char id[10];
	itoa(userId, id, 10);

	char* build1 = "Update User set creditCard = '";
	char* build2 = "' where id = ";
	char* build3 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id) + strlen(creditCard) + strlen(build3));
	strcpy(stmt, build1);
	strcat(stmt, creditCard);
	strcat(stmt, build2);
	strcat(stmt, id);
	strcat(stmt, build3);

	sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

	close();
	return;
}

void Database::emptyCart(User user) {
	open();

	//empties the cart to items table for the user
	char* error = "Error: could not remove items from cart.";
	char cartId[10];
	itoa(user.getCart().getId(), cartId, 10);

	char* build1 = "delete from Cart_Items where cartId = ";
	char* build2 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(cartId));
	strcpy(stmt, build1);
	strcat(stmt, cartId);
	strcat(stmt, build2);
	sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

	close();
}

void Database::addPurchase(Purchase purchase, int userId) {
	open();

	//insert into Purchase values(NULL, 'total', 'creditCard', 'address', 'userId);
	char* error = "Error: could not add purchase to database";
	char total[20];
	char creditCard[20];
	char user[10];
	sprintf(total, "%.2f", purchase.getTotal());
	itoa(purchase.getCreditCard(), creditCard, 10);
	itoa(userId, user, 10);

	char* build1 = "insert into Purchase values(NULL, ";
	char* build2 = ", ";
	char* build3 = ", '";
	char* build4 = "', ";
	char* build5 = ");";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(build3) + strlen(build4) + strlen(build5) + strlen(total) + strlen(creditCard) + strlen(user) + strlen(purchase.getShipAddress()));
	strcpy(stmt, build1);
	strcat(stmt, total);
	strcat(stmt, build2);
	strcat(stmt, creditCard);
	strcat(stmt, build3);
	strcat(stmt, purchase.getShipAddress());
	strcat(stmt, build4);
	strcat(stmt, user);
	strcat(stmt, build5);

	sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

	close();
}

void Database::addPurchaseItems(Purchase purchase) {
	open();
	char* query = "select purchaseId from purchase order by purchaseId desc;";
	
	sqlite3_stmt* selectStmt;
	sqlite3_prepare(getDB(), query, 1 + strlen(query), &selectStmt, NULL);
	sqlite3_step(selectStmt);
	purchase.setPurchaseId((int)sqlite3_column_int(selectStmt, 0));
	sqlite3_finalize(selectStmt);


	char* error = "Error: could not add item to Purchase_Items.";

	int count = 0;
	while (true) {
		if (purchase.getItems()[count].getItemId() == 0 || purchase.getPurchaseId() == 0) {
			break;
		}

		//insert into Purchase_Items values('purchaseId', 'itemId', 'quantity');
		char purchaseId[10];
		char itemId[10];
		char quantity[10];
		itoa(purchase.getPurchaseId(), purchaseId, 10);
		itoa(purchase.getItems()[count].getItemId(), itemId, 10);
		itoa(purchase.getQuantities()[count], quantity, 10);

		char* build1 = "Insert into Purchase_Items values(";
		char* build2 = ", ";
		char* build3 = ", ";
		char* build4 = ");";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(build3) + strlen(build4) + strlen(purchaseId) + strlen(itemId) + strlen(quantity));
		strcpy(stmt, build1);
		strcat(stmt, purchaseId);
		strcat(stmt, build2);
		strcat(stmt, itemId);
		strcat(stmt, build3);
		strcat(stmt, quantity);
		strcat(stmt, build4);

		sqlite3_exec(getDB(), stmt, NULL, NULL, &error);

		count++;
	}

	close();
}

void Database::printPurchaseHistory(User user) {
	open();
	Purchase purchases[20] = { Purchase() };

	//select * from Purchase where userId = 'id';
	char id[10];
	itoa(user.getId(), id, 10);

	char* build1 = "select * from Purchase where userId = ";
	char* build2 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
	strcpy(stmt, build1);
	strcat(stmt, id);
	strcat(stmt, build2);

	sqlite3_stmt* selectStmt;
	sqlite3_prepare(getDB(), stmt, strlen(stmt) + 1, &selectStmt, NULL);

	int count = 0;
	while (true) {
		int s = sqlite3_step(selectStmt);
		if (s == SQLITE_ROW) {
			purchases[count].setPurchaseId((int)sqlite3_column_int(selectStmt, 0));
			purchases[count].setTotal((float)sqlite3_column_double(selectStmt, 1));
			purchases[count].setCreditCard((int)sqlite3_column_int(selectStmt, 2));
			purchases[count].setShipAddress((char*)sqlite3_column_text(selectStmt, 3));
			purchases[count].setUsername(user.getUsername());
			count++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
	}

	sqlite3_finalize(selectStmt);
	close();


	//select * from Purchase_Items where purchaseId = id';
	open();
	int num = 0;
	while (num < (sizeof(purchases) / sizeof(purchases[0]))) {
		if (purchases[num].getPurchaseId() == 0) {
			break;
		}
		char id[10];
		itoa(purchases[num].getPurchaseId(), id, 10);

		char* build1 = "select * from Purchase_Items where purchaseId = ";
		char* build2 = ";";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
		strcpy(stmt, build1);
		strcat(stmt, id);
		strcat(stmt, build2);

		sqlite3_stmt* selectStmt;
		sqlite3_prepare(getDB(), stmt, strlen(stmt), &selectStmt, NULL);

		int x = 0;
		Item item[20];
		float prices[20];
		int quantities[20];
		while (true) {
			int s = sqlite3_step(selectStmt);
			if (s == SQLITE_ROW) {
				item[x] = getItem(sqlite3_column_int(selectStmt, 1));
				prices[x] = item[x].getPrice();
				quantities[x] = (int)sqlite3_column_int(selectStmt,2);
				cout << quantities[x] << endl;
			}
			else if (s == SQLITE_DONE) {
				break;
			}
			x++;
		}

		sqlite3_finalize(selectStmt);
		
		purchases[num].setItems(item);
		purchases[num].setPrices(prices);
		purchases[num].setQuantities(quantities);
		num++;
	}
	close();

	int y = 0;
	while (true) {
		if (purchases[y].getPurchaseId() == 0) {
			break;
		}
		purchases[y].printContents();
		y++;
	}
}

int Database::usernameCallback(void *userPtr, int argc, char **argv, char **azColName) {
	if (argv[0]) {
		loggedIn = true;
		User* user = (User*)userPtr;
		user->setUsername(argv[0]);
	}
	return 0;
}

Item* Database::getInventory(int category) {
	open();

	char type[10];
	itoa(category, type, 10);

	Item items[20] = { Item() };
	char* build1 = "Select * from Item where type = ";
	char* build2 = ";";
	char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(type));
	strcpy(stmt, build1);
	strcat(stmt, type);
	strcat(stmt, build2);
	sqlite3_stmt* selectStmt;
	sqlite3_prepare(db, stmt, strlen(stmt) + 1, &selectStmt, NULL);

	int count = 0;
	while (true) {
		int s;
		s = sqlite3_step(selectStmt);
		if (s == SQLITE_ROW) {
			items[count].setName((char*)sqlite3_column_text(selectStmt, 0));
			items[count].setItemId((int)sqlite3_column_int(selectStmt, 3));
			items[count].setPrice((float)sqlite3_column_double(selectStmt, 1));
			items[count].setQuantity((int)sqlite3_column_int(selectStmt, 2));
			count++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
	}

	sqlite3_finalize(selectStmt);
	close();

	return items;
}

void Database::getHouseholdItems() {
	Item items[20];
	memcpy(items, getInventory(HOUSEHOLDITEMS), sizeof(items));
	HouseholdItem hhitems[20] = { HouseholdItem() };

	open();
	int count = 0;
	while (true) {
		if (items[count].getItemId() == 0) {
			break;
		}
		//select * from HouseholdItem where itemId = 'itemId';
		char id[10];
		itoa(items[count].getItemId(), id, 10);

		char* build1 = "select * from HouseholdItems where itemId = ";
		char* build2 = ";";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
		strcpy(stmt, build1);
		strcat(stmt, id);
		strcat(stmt, build2);

		sqlite3_stmt* selectStmt;
		sqlite3_prepare(db, stmt, strlen(stmt) + 1, &selectStmt, NULL);

		int s = sqlite3_step(selectStmt);
		if (s == SQLITE_ROW) {
			hhitems[count].setBrand((char*)sqlite3_column_text(selectStmt, 2));
			hhitems[count].setType((char*)sqlite3_column_text(selectStmt, 1));
			hhitems[count].setItemId(items[count].getItemId());
			hhitems[count].setName(items[count].getName());
			hhitems[count].setPrice(items[count].getPrice());
			hhitems[count].setQuantity(items[count].getQuantity());
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		
		sqlite3_finalize(selectStmt);
		count++;
	}

	int x = 0;
	while (hhitems[x].getItemId() != 0) {
		hhitems[x].printContents();
		x++;
	}

	close();
	return;
}

void Database::getElectronics() {
	Item items[20];
	memcpy(items, getInventory(ELECTRONICS), sizeof(items));
	Electronic elec[20] = { Electronic() };

	open();
	int count = 0;
	while (true) {
		if (items[count].getItemId() == 0) {
			break;
		}
		//select * from Electronics where itemId = 'itemId';
		char id[10];
		itoa(items[count].getItemId(), id, 10);

		char* build1 = "select * from Electronics where itemId = ";
		char* build2 = ";";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
		strcpy(stmt, build1);
		strcat(stmt, id);
		strcat(stmt, build2);

		sqlite3_stmt* selectStmt;
		sqlite3_prepare(db, stmt, strlen(stmt) + 1, &selectStmt, NULL);

		int s = sqlite3_step(selectStmt);
		if (s == SQLITE_ROW) {
			elec[count].setBrand((char*)sqlite3_column_text(selectStmt, 2));
			elec[count].setType((char*)sqlite3_column_text(selectStmt, 1));
			elec[count].setItemId(items[count].getItemId());
			elec[count].setName(items[count].getName());
			elec[count].setPrice(items[count].getPrice());
			elec[count].setQuantity(items[count].getQuantity());
		}
		else if (s == SQLITE_DONE) {
			break;
		}

		sqlite3_finalize(selectStmt);
		count++;
	}

	int x = 0;
	while (elec[x].getItemId() != 0) {
		elec[x].printContents();
		x++;
	}

	close();
	return;
}

void Database::getToys() {
	Item items[20];
	memcpy(items, getInventory(TOYS), sizeof(items));
	Toy toys[20] = { Toy() };

	open();
	int count = 0;
	while (true) {
		if (items[count].getItemId() == 0) {
			break;
		}
		//select * from Toys where itemId = 'itemId';
		char id[10];
		itoa(items[count].getItemId(), id, 10);

		char* build1 = "select * from Toys where itemId = ";
		char* build2 = ";";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
		strcpy(stmt, build1);
		strcat(stmt, id);
		strcat(stmt, build2);

		sqlite3_stmt* selectStmt;
		sqlite3_prepare(db, stmt, strlen(stmt) + 1, &selectStmt, NULL);

		int s = sqlite3_step(selectStmt);
		if (s == SQLITE_ROW) {
			toys[count].setBrand((char*)sqlite3_column_text(selectStmt, 3));
			toys[count].setAges((int)sqlite3_column_int(selectStmt, 2));
			toys[count].setType((char*)sqlite3_column_text(selectStmt, 1));
			toys[count].setItemId(items[count].getItemId());
			toys[count].setName(items[count].getName());
			toys[count].setPrice(items[count].getPrice());
			toys[count].setQuantity(items[count].getQuantity());
		}
		else if (s == SQLITE_DONE) {
			break;
		}

		sqlite3_finalize(selectStmt);
		count++;
	}

	int x = 0;
	while (toys[x].getItemId() != 0) {
		toys[x].printContents();
		x++;
	}

	close();
	return;
}

void Database::getBooks() {
	Item items[20];
	memcpy(items, getInventory(BOOKS), sizeof(items));
	Book books[20] = { Book() };

	open();
	int count = 0;
	while (true) {
		if (items[count].getItemId() == 0) {
			break;
		}
		//select * from Books where itemId = 'itemId';
		char id[10];
		itoa(items[count].getItemId(), id, 10);

		char* build1 = "select * from Books where itemId = ";
		char* build2 = ";";
		char* stmt = (char*)malloc(1 + strlen(build1) + strlen(build2) + strlen(id));
		strcpy(stmt, build1);
		strcat(stmt, id);
		strcat(stmt, build2);

		sqlite3_stmt* selectStmt;
		sqlite3_prepare(db, stmt, strlen(stmt) + 1, &selectStmt, NULL);

		int s = sqlite3_step(selectStmt);
		if (s == SQLITE_ROW) {
			books[count].setGenre((char*)sqlite3_column_text(selectStmt, 1));
			books[count].setFiction((int)sqlite3_column_int(selectStmt, 2));
			books[count].setAuthor((char*)sqlite3_column_text(selectStmt, 3));
			books[count].setPublisher((char*)sqlite3_column_text(selectStmt, 4));
			books[count].setItemId(items[count].getItemId());
			books[count].setName(items[count].getName());
			books[count].setPrice(items[count].getPrice());
			books[count].setQuantity(items[count].getQuantity());
		}
		else if (s == SQLITE_DONE) {
			break;
		}

		sqlite3_finalize(selectStmt);
		count++;
	}

	int x = 0;
	while (books[x].getItemId() != 0) {
		books[x].printContents();
		x++;
	}

	close();
	return;
}