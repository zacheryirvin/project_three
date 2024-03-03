#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include "Grocery_Item.h"

// Function to read data from a file and populate a set of Grocery_Item objects
std::set<Grocery_Item> read_in_file(const std::string& filename) {
    std::set<Grocery_Item> groceryItemList;
    std::string groceryItemName;
    std::ifstream inputFile(filename);

    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        std::exit(1);
    }

    // Read each line from the file and process grocery items
    while (std::getline(inputFile, groceryItemName)) {
        // Trim leading and trailing whitespaces
        groceryItemName.erase(0, groceryItemName.find_first_not_of(" \t\r\n"));
        groceryItemName.erase(groceryItemName.find_last_not_of(" \t\r\n") + 1);

        // Check if the grocery item name is not empty
        if (!groceryItemName.empty()) {
            // Create a temporary Grocery_Item object
            Grocery_Item* temp = new Grocery_Item(groceryItemName, 1);

            // Check if the item already exists in the set
            auto existingItem = groceryItemList.find(*temp);
            if (existingItem != groceryItemList.end()) {
                // If exists, update the existing item's quantity
                temp = const_cast<Grocery_Item*>(&(*existingItem));
                temp->addItem();
            }
            else {
                // If not exists, insert the item into the set
                groceryItemList.insert(*temp);
                delete(temp); // Avoid memory leak
            }
        }
    }
    inputFile.close();
    return groceryItemList;
}

// Function to backup grocery data to a file
void backupData(const std::set<Grocery_Item> list) {
    std::ofstream outputFile("frequency.dat");

    // Check if the output file is successfully opened
    if (outputFile.is_open()) {
        // Write each item's name and quantity to the file
        for (const auto& item : list) {
            outputFile << item.getName() << item.getQuantity() << '\n';
        }
        outputFile.close();
    }
    else {
        std::cerr << "Error opening frequency.dat.";
    }
}

// Function to delete dynamically allocated Grocery_Item objects in a set
void deleteGroceryItemList(std::set<Grocery_Item*>& groceryItems) {
    for (auto item : groceryItems) {
        delete item;
    }
}

// Function to search for a specific item in the set and print its quantity
void searchForItem(const std::string& item, const std::set<Grocery_Item> list) {
    auto temp = list.find(item);
    if (temp != list.end()) {
        std::cout << item << ": " << temp->getQuantity() << "\n\n";
    }
    else {
        std::cout << "Item not found.\n";
    }
}

// Function to print the list of grocery items and their quantities
void printList(const std::set<Grocery_Item> list) {
    for (const auto& item : list) {
        std::cout << item.getName() << ": " << item.getQuantity() << '\n';
    }
    std::cout << '\n';
}

// Function to print a histogram of occurrences for each grocery item
void printHistogram(const std::set<Grocery_Item> list) {
    for (const auto& item : list) {
        std::cout << item.getName() << " ";
        for (int i = 0; i < item.getQuantity(); ++i) {
            std::cout << "*";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Main function
int main() {
    int userChoice;
    std::string item;

    // Read grocery items from the file "inventory.txt"
    std::set<Grocery_Item> groceryItemList = read_in_file("inventory.txt");

    // Backup the data to "frequency.dat"
    backupData(groceryItemList);

    // Main menu loop
    do {
        std::cout << "Menu Options:\n";
        std::cout << "1. Search for Item:\n";
        std::cout << "2. Print List:\n";
        std::cout << "3. Print Histogram of Occurrences:\n";
        std::cout << "4: Exit\n";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1:
            std::cout << "Enter the Item to search for: ";
            std::cin >> item;
            searchForItem(item, groceryItemList);
            break;
        case 2:
            printList(groceryItemList);
            break;
        case 3:
            printHistogram(groceryItemList);
            break;
        case 4:
            std::cout << "Goodbye.\n";
            break;
        default:
            std::cout << "Invalid Choice.\n";
        }
    } while (userChoice != 4);

    // Delete dynamically allocated Grocery_Item objects
    deleteGroceryItemList;

    return 0;
}

