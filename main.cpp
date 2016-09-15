#include "classFiles\classFiles.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "defines.h"

using namespace std;

bool loggedIn; //defined from extern in defines.h
char* username;
Database db = Database();

void clearScreen() {
	system("CLS"); //should implement this in another way
}

void printOptions() {
	cout << "Input option number:" << endl;
	cout << "1. Look through inventory" << endl;
	cout << "2. Look at cart" << endl;
	cout << "3. Look at purchase history" << endl;
	cout << "4. Log out" << endl;
	cout << "5. Quit" << endl;
}

int getOptions() {
	int choice = 0;
	printOptions();
	cin >> choice;
	return choice;
}

void printCartOptions() {
	cout << "Cart Options:" << endl;
	cout << "1. Remove select item from cart." << endl;
	cout << "2. Purchase cart." << endl;
	cout << "3. Exit cart menu." << endl;
	cout << "Enter choice: ";
}

int getCartOptions() {
	int choice = 0;
	printCartOptions();
	cin >> choice;
	return choice;
}

User login() {
	username = new char[20];
	User user;

	while (loggedIn == false) {
		if (loggedIn == false) {
			cout << "Login: ";
			cin >> username;
			user = db.getUser(username);
		}
		if (loggedIn == false) {
			cout << "Error: incorrect username. Try again." << endl;
		}
	}

	cout << "Login successful! Welcome " << user.getUsername() << "." << endl << endl;
	return user;
}

User addItem(User user) {
	Item item = Item();
	int itemNum;
	int quantity;
	int cartId = user.getCart().getId(); //needs to get this from user object
	cout << "Enter item id to add to cart or enter 0 to exit inventory list: ";
	cin >> itemNum;
	if (itemNum == 0) {
		clearScreen();
		return user;
	}
	cout << "Enter quantity to purchase: ";
	cin >> quantity;

	//check to see how many items are in inventory and dont let the user grab more than is left
	clearScreen();
	db.open();
	item = db.getItem(itemNum);
	db.close();
	if (quantity > item.getQuantity()) {
		quantity = item.getQuantity();
		cout << "Could only add " << quantity << "." << endl;
	}

	db.addToCart(itemNum, user.getCart().getId(), quantity);
	User updatedUser = db.getUser(user.getUsername());
	cout << "Succesfully added item to cart!" << endl << endl;

	return updatedUser;
}

User getAddress(User user) {
	char newAddress[30];
	cout << "Enter address: ";
	cin.ignore();
	cin.get(newAddress, sizeof(newAddress));
	db.updateAddress(user.getId(), newAddress);
	user = db.getUser(user.getUsername());
	return user;
}

User getCreditCard(User user) {
	char choice = ' ';
	char newCreditCard[20];
	cout << "Enter credit card: ";
	cin.ignore();
	cin.get(newCreditCard, sizeof(newCreditCard));
	db.updateCreditCard(user.getId(), newCreditCard);
	user = db.getUser(user.getUsername());
	return user;
}

User getInventory(User user) {
	int choice = 0;
	cout << "Choose category:" << endl;
	cout << "1. Household Items" << endl;
	cout << "2. Books" << endl;
	cout << "3. Toys" << endl;
	cout << "4. Small Electronics" << endl;
	cin >> choice;

	clearScreen();
	cout << "Inventory:" << endl;
	switch (choice) {
	case 1:
		db.getHouseholdItems();
		break;
	case 2:
		db.getBooks();
		break;
	case 3:
		db.getToys();
		break;
	case 4:
		db.getElectronics();
		break;
	default:
		break;
	}
	user = addItem(user);
	return user;
}

int main() {
	bool quit = true;
	bool skip = false; //used when the loop should stay in the current menu
	int choice = 0;

	User user = login();

	while (quit) {

		if (skip == false) {
			choice = getOptions();
		}
		else if (skip == true) {
			skip = false;
		}

		if (choice == 1) {
			clearScreen();
			user = getInventory(user);
			continue;
		}
		else if (choice == 2) {
			clearScreen();
			int cartChoice;
			user.getCart().printContents();
			cartChoice = getCartOptions();
			if (cartChoice == 1) {
				int itemId;
				cout << "Enter item id to be removed: ";
				cin >> itemId;
				db.removeFromCart(user.getCart().getId(), itemId);
				user = db.getUser(user.getUsername());
				skip = true;
			}
			else if (cartChoice == 2) {
				user = getAddress(user);
				user = getCreditCard(user);
				db.purchaseCart(user);
				user = db.getUser(user.getUsername());
			}
			else if (cartChoice == 3) {
				//return to normal loop
				//does nothing
			}
		}
		else if (choice == 3) {
			clearScreen();
			cout << "Purchase history for " << user.getUsername() << ":" << endl << endl;
			db.printPurchaseHistory(user);
			continue;
		}
		else if (choice == 4) {
			loggedIn = false;
			db.emptyCart(user);
			clearScreen();
			user = login();
			continue;
		}
		else if (choice == 5) {
			db.emptyCart(user);
			quit = false;
		}
		clearScreen();
	}
	return 1;
}