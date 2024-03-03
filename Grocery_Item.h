#pragma once
#include <string>


class Grocery_Item
{
public:
	Grocery_Item(std::string name);
	Grocery_Item(std::string name, int quantity);
	Grocery_Item(const Grocery_Item& other);

	std::string getName() const;
	int getQuantity() const;

	void addItem();
	void removeItem();

	bool operator<(const Grocery_Item& other) const;

private:
	std::string name;
	int quantity;
};

