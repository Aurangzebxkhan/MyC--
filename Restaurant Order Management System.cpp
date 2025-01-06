#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

// Structure to store menu items
struct MenuItem {
    int itemCode;
    char name[50];
    float price;
    int quantityAvailable;
};

// Function Prototypes
void loadMenu(MenuItem menu[], int &itemCount);
void saveMenu(MenuItem menu[], int itemCount);
void displayMenu(const MenuItem menu[], int itemCount);
int placeOrder(MenuItem menu[], int itemCount);
void updateQuantity(MenuItem &item, int quantityOrdered);
void displayMainMenu();

const int MAX_ITEMS = 100; // Maximum number of menu items

int main() {
    MenuItem menu[MAX_ITEMS];
    int itemCount = 0;

    // Load menu data from file
    loadMenu(menu, itemCount);

    int choice;
    do {
        displayMainMenu(); // Call the renamed function
        cin >> choice;

        switch (choice) {
        case 1:
            displayMenu(menu, itemCount);
            break;
        case 2:
            placeOrder(menu, itemCount);
            break;
        case 3:
            cout << "Exiting...\n";
            saveMenu(menu, itemCount);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

// Load menu data from file
void loadMenu(MenuItem menu[], int &itemCount) {
    ifstream file("menu.txt");
    if (!file) {
        cout << "Menu file not found. Starting with an empty menu.\n";
        return;
    }

    itemCount = 0;
    while (file >> menu[itemCount].itemCode) {
        file.ignore();
        file.getline(menu[itemCount].name, 50, ',');
        file >> menu[itemCount].price >> menu[itemCount].quantityAvailable;
        itemCount++;
    }

    file.close();
}

// Save menu data to file
void saveMenu(MenuItem menu[], int itemCount) {
    ofstream file("menu.txt");
    for (int i = 0; i < itemCount; i++) {
        file << menu[i].itemCode << "," << menu[i].name << ",";
        file << menu[i].price << " " << menu[i].quantityAvailable << "\n";
    }
    file.close();
}

// Display menu items
void displayMenu(const MenuItem menu[], int itemCount) {
    cout << "\nMenu:\n";
    cout << left << setw(10) << "Code" << setw(20) << "Name" << setw(10) << "Price" << "Available\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(10) << menu[i].itemCode << setw(20) << menu[i].name;
        cout << setw(10) << menu[i].price << menu[i].quantityAvailable << "\n";
    }
}

// Place an order
int placeOrder(MenuItem menu[], int itemCount) {
    int code, quantity;
    cout << "\nEnter Item Code: ";
    cin >> code;
    cout << "Enter Quantity: ";
    cin >> quantity;

    for (int i = 0; i < itemCount; i++) {
        if (menu[i].itemCode == code) {
            if (menu[i].quantityAvailable >= quantity) {
                float totalCost = menu[i].price * quantity;
                updateQuantity(menu[i], quantity);
                cout << "Order placed successfully!\n";
                cout << "Total Bill: " << totalCost << "\n";
                return 1;
            } else {
                cout << "Sorry, not enough stock available.\n";
                return 0;
            }
        }
    }

    cout << "Item not found.\n";
    return 0;
}

// Update the quantity of an item
void updateQuantity(MenuItem &item, int quantityOrdered) {
    item.quantityAvailable -= quantityOrdered;
}

// Display main menu
void displayMainMenu() {
    cout << "\nRestaurant Order Management System\n";
    cout << "1. View Menu\n";
    cout << "2. Place Order\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}
