//this file uses the classes and calls upon many objects in order to run the entire system

#include "classFiles\classFiles.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "defines.h"

using namespace std;

bool loggedIn; //defined from extern in defines.h
char* username;
Database db = Database();

//a system function was used here to make sure the screen was clean and would keep the console from piling up with text, we do realize it isnt good practice to use system calls but for the triviality of this system we figured it to be acceptable
void clearScreen() {
	system("CLS"); //should probably be implemented in another way
}

//prints the main screen options
void printOptions() {
	cout << "Input option number:" << endl;
	cout << "1. Look through inventory" << endl;
	cout << "2. Look at cart" << endl;
	cout << "3. Look at purchase history" << endl;
	cout << "4. Log out" << endl;
	cout << "5. Quit" << endl;
}

//gets the choice from the user
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

//logs the user in and error checks to make sure that the username is accurate
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

//adds an item to the users cart by grabbing the selected items id and then adding the selected quantity to the users cart
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

//gets the users address for an order
User getAddress(User user) {
	char newAddress[30];
	cout << "Enter address: ";
	cin.ignore();
	cin.get(newAddress, sizeof(newAddress));
	db.updateAddress(user.getId(), newAddress);
	user = db.getUser(user.getUsername());
	return user;
}

//gets the users credit card for an order
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

//displays the inventory to the user based on their choice of categories
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

		//skip is used to keep the user looking at the current menu when an action is completed, if skip is not true then it will return the user to the main menu
		if (skip == false) {
			choice = getOptions();
		}
		else if (skip == true) {
			skip = false;
		}

		//choice for seeing the inventory
		if (choice == 1) {
			clearScreen();
			user = getInventory(user);
			continue;
		}

		//choice for seeing the users cart and modifying it
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

		//choice to see the users purchase history
		else if (choice == 3) {
			clearScreen();
			cout << "Purchase history for " << user.getUsername() << ":" << endl << endl;
			db.printPurchaseHistory(user);
			continue;
		}

		//choice to log the user out of the system
		else if (choice == 4) {
			loggedIn = false;
			db.emptyCart(user);
			clearScreen();
			user = login();
			continue;
		}

		//choice that shuts down the system
		else if (choice == 5) {
			db.emptyCart(user);
			quit = false;
		}
		clearScreen();
	}
	return 1;
}