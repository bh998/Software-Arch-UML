//this file is the cpp file that controls all the methods of the book class
//this demostrates modularity in that it controls the book class completely and all of its attributes
//it also shows inheritance since it inherits from items

#include "Book.h"
#include <iostream>
#include <iomanip>
using namespace std;

//constructors

//getters and setters
char* Book::getGenre() {
	return genre;
}
void Book::setGenre(char* newGenre) {
	strcpy(genre, newGenre);
}

bool Book::getFiction() {
	return fiction;
}
void Book::setFiction(bool newFiction) {
	fiction = newFiction;
}

char* Book::getAuthor() {
	return author;
}
void Book::setAuthor(char* newAuthor) {
	strcpy(author, newAuthor);
}

char* Book::getPublisher() {
	return publisher;
}
void Book::setPublisher(char* newPublisher) {
	strcpy(publisher, newPublisher);
}

//operations
void Book::printContents() {
	cout << "Item Id: " << getItemId() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Genre: " << getGenre() << endl;
	char* fict = (getFiction() == 1) ? "Fiction" : "Not Fiction";
	cout << "Category: " << fict << endl;
	cout << "Author: " << getAuthor() << endl; 
	cout << "Publisher: " << getPublisher() << endl;
	cout << fixed << setprecision(2) << "Price: " << getPrice() << endl;
	cout << "Quantity: " << getQuantity() << endl << endl;
}