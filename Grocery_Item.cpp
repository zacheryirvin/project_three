#include "Grocery_Item.h"

// Constructor with only name parameter
Grocery_Item::Grocery_Item(std::string name) {
	this->name = name;
	this->quantity = 0;
}

// Constructor with name and quantity parameters
Grocery_Item::Grocery_Item(std::string name, int quantity) {
	this->name = name;
	this->quantity = quantity;
}

// Copy constructor
Grocery_Item::Grocery_Item(const Grocery_Item& other) {
	this->name = other.name;
	this->quantity = other.quantity;
}

// Getter for the name of the grocery item
std::string Grocery_Item::getName() const {
	return this->name;
}

// Getter for the quantity of the grocery item
int Grocery_Item::getQuantity() const {
	return this->quantity;
}

// Increment the quantity of the grocery item by 1
void Grocery_Item::addItem() {
	this->quantity += 1;
}

// Decrement the quantity of the grocery item by 1 (if quantity is greater than 0)
void Grocery_Item::removeItem() {
	if (this->quantity > 0) {
		this->quantity -= 1;
	}
}

// Overloaded less than operator for comparison based on the item names
bool Grocery_Item::operator<(const Grocery_Item& other) const {
	return name.compare(other.getName()) < 0;
}

