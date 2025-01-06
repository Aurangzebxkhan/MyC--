#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Forward declarations
void firstFloor();
void secondFloor();
void thirdFloor();

// Base structure for items
struct Item {
    string name;
    float price;
    float discount;
};

// Structure to represent a parked vehicle
struct Vehicle {
    string plateNumber;
    string type; // Car, Motorcycle, or Truck
    int parkingSlot;
    time_t entryTime; // Entry time for calculating charges
};

// Function to calculate parking charges based on time duration
int calculateCharges(time_t entryTime) {
    time_t currentTime = time(nullptr); // Current time
    double duration = difftime(currentTime, entryTime) / 60.0; // Duration in minutes

    if (duration <= 10) {
        return 0;
    } else if (duration <= 20) {
        return 50;
    } else if (duration <= 30) {
        return 80;
    } else if (duration <= 40) {
        return 120;
    } else if (duration <= 60) {
        return 150;
    } else if (duration <= 120) {
        return 300;
    } else {
        return 1500; // Charges for a whole day or more
    }
}

// Function to display the parking lot status
void displayParkingLot(const vector<Vehicle>& parkingLot, int totalSlots) {
    cout << "\n********** Parking Lot Status **********\n";
    for (int i = 1; i <= totalSlots; i++) {
        bool slotOccupied = false;
        for (const auto& vehicle : parkingLot) {
            if (vehicle.parkingSlot == i) {
                cout << "Slot " << i << ": " << vehicle.type << " (Plate: " << vehicle.plateNumber << ")\n";
                slotOccupied = true;
                break;
            }
        }
        if (!slotOccupied) {
            cout << "Slot " << i << ": Empty\n";
        }
    }
    cout << "****************************************\n";
}

// Function to park a vehicle
void parkVehicle(vector<Vehicle>& parkingLot, int totalSlots) {
    if (parkingLot.size() >= totalSlots) {
        cout << "Parking lot is full. No available slots.\n";
        return;
    }

    string plateNumber, type;
    cout << "Enter vehicle plate number: ";
    cin >> plateNumber;
    cout << "Enter vehicle type (Car/Motorcycle/Truck): ";
    cin >> type;

    int slotNumber = -1;
    for (int i = 1; i <= totalSlots; i++) {
        bool slotOccupied = false;
        for (const auto& vehicle : parkingLot) {
            if (vehicle.parkingSlot == i) {
                slotOccupied = true;
                break;
            }
        }
        if (!slotOccupied) {
            slotNumber = i;
            break;
        }
    }

    if (slotNumber != -1) {
        parkingLot.push_back({plateNumber, type, slotNumber, time(nullptr)});
        cout << "Vehicle parked successfully in slot " << slotNumber << ".\n";
    } else {
        cout << "No available slots found. Parking failed.\n";
    }
}

// Function to remove a vehicle from the parking lot
void removeVehicle(vector<Vehicle>& parkingLot) {
    if (parkingLot.empty()) {
        cout << "Parking lot is empty. No vehicles to remove.\n";
        return;
    }

    string plateNumber;
    cout << "Enter the plate number of the vehicle to remove: ";
    cin >> plateNumber;

    auto it = parkingLot.begin();
    while (it != parkingLot.end()) {
        if (it->plateNumber == plateNumber) {
            int charges = calculateCharges(it->entryTime);
            cout << "Vehicle with plate " << plateNumber << " removed from slot " << it->parkingSlot << ".\n";
            cout << "Parking charges: Rs. " << charges << ".\n";
            parkingLot.erase(it);
            return;
        }
        ++it;
    }

    cout << "Vehicle with plate " << plateNumber << " not found in the parking lot.\n";
}

int main() {
    vector<Vehicle> parkingLot;
    const int totalSlots = 10; // Total parking slots available
    int choice;

    do {
        cout << "\n*********Welcome to the Shopping Mall*********\n";
        cout << "1. Ground Floor (Parking)\n";
        cout << "2. First Floor (Shops)\n";
        cout << "3. Second Floor (Bookstore)\n";
        cout << "4. Third Floor (Restaurant)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                int parkingChoice;
                do {
                    cout << "\n********** Parking Management System **********\n";
                    cout << "1. Park a Vehicle\n";
                    cout << "2. Remove a Vehicle\n";
                    cout << "3. View Parking Lot Status\n";
                    cout << "4. Exit\n";
                    cout << "**********************************************\n";
                    cout << "Enter your choice: ";
                    cin >> parkingChoice;

                    switch (parkingChoice) {
                        case 1: parkVehicle(parkingLot, totalSlots); break;
                        case 2: removeVehicle(parkingLot); break;
                        case 3: displayParkingLot(parkingLot, totalSlots); break;
                        case 4: cout << "Exiting the system. Thank you!\n"; break;
                        default: cout << "Invalid choice. Please try again.\n";
                    }
                } while (parkingChoice != 4);
                break;
            case 2: firstFloor(); break;
            case 3: secondFloor(); break;
            case 4: thirdFloor(); break;
            case 5: cout << "Thank you for visiting!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}


// Cosmetics Shop
void cosmeticsShop() {
    vector<Item> cosmetics = {{"Lipstick", 500, 10}, {"Foundation", 1000, 15}, {"Perfume", 1500, 20}};
    cout << "\nWelcome to the Cosmetics Shop\n";
    cout << "Items Available:\n";
    for (const auto& item : cosmetics) {
        cout << item.name << " - Rs. " << item.price << " (" << item.discount << "% discount)\n";
    }
}
// Clothing Shop
// Structure for clothing items
struct ClothingItem {
    string itemName;
    int price;
    int quantity;

    ClothingItem(string name,int p, int q) : itemName(name),  price(p),quantity(q) {}
};

// Function to display the main menu of the clothing shop
void displayClothingMainMenu()
 {
    cout << "\n********** Welcome to Khan G Clothing Shop **********\n";
    cout << "1. Men's Collection\n";
    cout << "2. Women's Collection\n";
    cout << "3. Kid's Collection\n";
    cout << "4. View and Finalize Order\n";
    cout << "5. Exit\n";
    cout << "***********************************************\n";
}

// Function to display items from a specific category and allow adding them to the order
void addClothingItem(vector<ClothingItem>& order, const string& category, const vector<pair<string,int>>& items) {
    int itemChoice, quantity;
    cout << "\nYou selected " << category << ".\n";
    for (size_t i = 0; i < items.size(); i++) {
        cout << i + 1 << ". " << items[i].first<< " -Rs." << items[i]. second << endl;
    }
    cout << "Enter the number of the item you want to add to your cart: ";
    cin >> itemChoice;

    if (itemChoice < 1 || itemChoice > items.size()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }

    cout << "Enter the quantity: ";
    cin >> quantity;
    order.push_back(ClothingItem(items[itemChoice - 1].first, items[itemChoice - 1].second, quantity));
    cout << "Added " << quantity << " x " << items[itemChoice - 1].first << " to your cart.\n"; 
}

// Function to display men's collection
void displayMensCollection(vector<ClothingItem>& order)
{
    vector<pair<string,int>> mensItems = {
        {"T-Shirt", 800},
        {"Shirt", 1200},
        {"Jeans", 2000},
        {"Blazer", 5000}
    };
    addClothingItem(order,"Men's Collection",mensItems);
}

// Function to display women's collection
void displayWomensCollection(vector<ClothingItem>& order)
 {
    vector<pair<string,int>>womenItems = {
        {"Blouse", 1000},
        {"Silk", 1500},
        {"Evening Gown", 2500},
        { "Satin", 5000},
        {"Skirt",800},
        {"Cotton", 1200},
        {"Jacket", 2100},
        {"Leather", 3000}
    };
    addClothingItem(order, "Women's Collection", womenItems);
}

// Function to display kid's collection
void displayKidsCollection(vector<ClothingItem>& order)
 {
    vector<pair<string,int>>kidsItems=  {
        {"T-Shirt",  500},
        {"Sweater",  1000},
        {"Shorts",  700},
        {"Raincoat",  1200}
    };
    addClothingItem(order, "Kid's Collection", kidsItems);
}

// Function to view and finalize the order
void viewAndFinalizeOrder(vector<ClothingItem>& order) {
    if (order.empty()) {
        cout << "Your cart is empty. .\n";
        return;
    }

    cout << "\nYour current order:\n";
    int total = 0;
    for (size_t i = 0; i < order.size(); i++) {
        cout << i + 1 << ". " << order[i].itemName << " - Rs. " << order[i].price << " x " << order[i].quantity << endl;
        total += order[i].price * order[i].quantity;
    }

    cout << "\nTotal: Rs. " << total << endl;
    char finalize;
    cout << "Would you like to finalize your order? (Y/N): ";
    cin >> finalize;
    if (finalize == 'Y' || finalize == 'y') {
        int itemIndex;
        cout << " Enter the number of item you want to remove (1-" << order.size() << "): ";
        if( itemIndex>=1&& itemIndex<=order.size())
        {
            order.erase(order.begin()+itemIndex-1);
            cout<<"Item removed from the order.\n";
        }
        else
        {
            cout<<"Invalid choice. Please try again.\n";
        }
    }    
}

// Function to handle clothing shop
void clothingShop() {
    vector<ClothingItem> order;
    int choice;
    do {
        displayClothingMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayMensCollection(order); break;
            case 2: displayWomensCollection(order); break;
            case 3: displayKidsCollection(order); break;
            case 4: viewAndFinalizeOrder(order); break;
            case 5: cout << "Returning to First Floor Menu...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}


// Jewelry Shop
void jewelryShop() {
    vector<Item> jewelry = {{"Gold Necklace", 50000, 5}, {"Gold Ring", 20000, 8}, {"Gold Bracelet", 30000, 10}};
    cout << "\nWelcome to the Jewelry Shop\n";
    cout << "Items Available:\n";
    for (const auto& item : jewelry) {
        cout << item.name << " - Rs. " << item.price << " (" << item.discount << "% discount)\n";
    }
}

// Bookstore
void bookstore() {
    vector<Item> books = {{"C++ Programming", 1000, 10}, {"Python Basics", 1200, 15}, {"Data Science", 1500, 20}};
    cout << "\nWelcome to the Bookstore\n";
    cout << "Books Available:\n";
    for (const auto& book : books) {
        cout << book.name << " - Rs. " << book.price << " (" << book.discount << "% discount)\n";
    }
}

// Restaurant
struct OrderItem {
    string itemName;
    int price;
    int quantity;
    
    OrderItem(string name, int p, int q) : itemName(name), price(p), quantity(q) {}
};

// Function to display the main menu of the restaurant
void displayRestaurantMainMenu() {
    cout << "\n********** KHAN G RESTAURANT **********\n";
    cout << "********** DELICIOUS MENU **********\n";
    cout << "1. Delicious Pizza\n";
    cout << "2. Value Meals\n";
    cout << "3. Signature Burgers\n";
    cout << "4. Crunch Boost\n";
    cout << "5. Lahore Broast\n";
    cout << "6. Broasted Biryani\n";
    cout << "7. Curries\n";
    cout << "8. View and Adjust Order\n";
    cout << "9. Finalize Order\n";
    cout << "************************************\n";
}

// Function to add items from a specific category to the order list
void addMenuItem(vector<OrderItem>& order, const string& category, const vector<pair<string, int>>& items) {
    int itemChoice, quantity;
    cout << "\nYou selected " << category << ".\n";
    for (size_t i = 0; i < items.size(); i++) {
        cout << i + 1 << ". " << items[i].first << " - Rs. " << items[i].second << endl;
    }
    cout << "Enter the number of the item you want to add to the order: ";
    cin >> itemChoice;
    if (itemChoice < 1 || itemChoice > items.size()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }
    cout << "Enter the quantity: ";
    cin >> quantity;
    order.push_back(OrderItem(items[itemChoice - 1].first, items[itemChoice - 1].second, quantity));
    cout << "Added " << quantity << " x " << items[itemChoice - 1].first << " to your order.\n"; 
}

// Function to display the value meals menu
void displayValueMealsMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> valueMeals = {
        {"Chicken Value Meals", 650},
        {"Beef Value Meals", 750},
        {"Fish Value Meals", 800},
        {"Family Platter", 2000}
    };
    addMenuItem(order, "Value Meals", valueMeals);
}

// Function to display the pizza menu
void displayPizzaMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> pizza = {
        {"Fajita Delight (Small)", 600},
        {"Fajita Delight (Medium)", 950},
        {"Fajita Delight (Large)", 1500},
        {"Chicken Tikka (Small)", 600},
        {"Chicken Tikka (Medium)", 950},
        {"Chicken Tikka (Large)", 1500},
    };
    addMenuItem(order, "Delicious Pizza", pizza);
}

// Function to display burgers menu
void displayBurgersMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> burgers = {
        {"Zinger Burger", 600},
        {"Beef Burger", 500},
        {"Chicken Burger", 450},
        {"Fish Burger", 700}
    };
    addMenuItem(order, "Signature Burgers", burgers);
}

// Function to display the crunch boost menu
void displayCrunchBoostMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> crunchBoost = {
        {"Crispy Chicken Strips", 550},
        {"Crispy Fries", 350},
        {"Crispy Fish", 400},
        {"Crispy Nuggets", 500}
    };
    addMenuItem(order, "Crunch Boost", crunchBoost);
}

// Function to display the Lahore broast menu
void displayLahoreBroastMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> lahoreBroast = {
        {"Half Broast", 800},
        {"Full Broast", 1500},
    };
    addMenuItem(order, "Lahore Broast", lahoreBroast);
}

// Function to display the biryani menu
void displayBiryaniMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> biryani = {
        {"Chicken Biryani", 600},
        {"Beef Biryani", 800},
        {"Mutton Biryani", 900},
        {"Fish Biryani", 1200}
    };
    addMenuItem(order, "Broasted Biryani", biryani);
}

// Function to display the curries menu
void displayCurriesMenu(vector<OrderItem>& order) {
    vector<pair<string, int>> curries = {
        {"Chicken Karahi", 800},
        {"Beef Karahi", 1000},
        {"Mutton Karahi", 1200},
        {"Fish Karahi", 1500}
    };
    addMenuItem(order, "Curries", curries);
}

// Function to display the current order and adjust it
void viewAndAdjustOrder(vector<OrderItem>& order) {
    if (order.empty()) {
        cout << "Your order is empty.\n";
        return;
    }

    cout << "Your current order:\n";
    int total = 0;
    for (int i = 0; i < order.size(); i++) {
        cout << i + 1 << ". " << order[i].itemName << " - Rs. " << order[i].price << " x " << order[i].quantity << endl;
        total += order[i].price * order[i].quantity;
    }

    cout << "\nTotal: Rs. " << total << endl;
    char action;
    cout << "\nWould you like to (R)emove an item, (A)dd a new item or (C)ontinue to finalize the order? ";
    cin >> action;
    if (action == 'R' || action == 'r') {
        int itemIndex;
        cout << "Enter the number of the item you want to remove (1-" << order.size() << "): ";
        cin >> itemIndex;
        if (itemIndex >= 1 && itemIndex <= order.size()) {
            order.erase(order.begin() + itemIndex - 1);
            cout << "Item removed from the order.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to handle restaurant orders
void handleRestaurantOrders() {
    vector<OrderItem> order;
    int choice;
    do {
        displayRestaurantMainMenu();
        cout << "Enter the number of the category you want (1-9): ";
        cin >> choice;

        switch (choice) {
            case 1: displayPizzaMenu(order); break;
            case 2: displayValueMealsMenu(order); break;
            case 3: displayBurgersMenu(order); break;
            case 4: displayCrunchBoostMenu(order); break;
            case 5: displayLahoreBroastMenu(order); break;
            case 6: displayBiryaniMenu(order); break;
            case 7: displayCurriesMenu(order); break;
            case 8: viewAndAdjustOrder(order); break;
            case 9:
                if (order.empty()) {
                    cout << "Your order is empty. Please add items to your order.\n";
                    cout << "Thank you for visiting KHAN G RESTAURANT.\n";
                } else {
                    cout << "Finalizing your order...\n";
                    int total = 0;
                    cout << "Your final order:\n";
                    for (const auto& item : order) {
                        cout << "-" << item.itemName << " - Rs. " << item.price << " x " << item.quantity << " = Rs. " << item.price * item.quantity << endl;
                        total += item.price * item.quantity;
                    }
                    cout << "\nTotal Bill: Rs. " << total << endl;
                    cout << "Thank you for visiting KHAN G RESTAURANT.\n";
                }
                break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);
}

void restaurantMenu() {
    vector<OrderItem> order;
    int choice;
    do {
        cout << "\nWelcome to the Restaurant\n";
        cout << "1. Order Food\n";
        cout << "2. View Menu\n";
        cout << "3. Back to Third Floor Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: handleRestaurantOrders(); break;
            case 2: displayRestaurantMainMenu(); break;
            case 3: cout << "Returning to Third Floor Menu...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

// Third Floor Menu
void thirdFloor() {
    int choice;
    cout << "\nWelcome to the Third Floor\n";
    cout << "1. Restaurant\n";
    cout << "2. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: restaurantMenu(); break;
        case 2: cout << "Returning to Main Menu...\n"; break;
        default: cout << "Invalid choice. Try again.\n"; return;
    }
}

// First Floor Menu
void firstFloor() {
    int choice;
    do {
        cout << "\nWelcome to the First Floor\n";
        cout << "1. Cosmetics Shop\n";
        cout << "2. Clothing Shop\n";
        cout << "3. Jewelry Shop\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cosmeticsShop(); break;
            case 2: clothingShop(); break;
            case 3: jewelryShop(); break;
            case 4: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Second Floor Menu
void secondFloor() {
    cout << "\nWelcome to the Second Floor\n";
    bookstore();
}
