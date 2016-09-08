#include "Book.h"

//constructors
Book::Book(char* name, float price, int quantity, int itemId, char* genre, bool fiction, char* author, char* publisher) {
	setName(name);
	setPrice(price);
	setQuantity(quantity);
	setItemId(itemId);
	setGenre(genre);
	setFiction(fiction);
	setAuthor(author);
	setPublisher(publisher);
	return;
}

//getters and setters
char* Book::getGenre() {
	return genre;
}
void Book::setGenre(char* newGenre) {
	genre = newGenre;
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
	author = newAuthor;
}

char* Book::getPublisher() {
	return publisher;
}
void Book::setPublisher(char* newPublisher) {
	publisher = newPublisher;
}

//operations