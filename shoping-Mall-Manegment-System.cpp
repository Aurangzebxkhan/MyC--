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
// parking Program 
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
// Personal Care Products Management
struct Product {
    string productName;
    int price;
    int quantity;

    Product(string name, int p, int q) : productName(name), price(p), quantity(q) {}
};

// Function to display the main menu
void displayMainMenuu() {
    cout << "\n********** PERSONAL CARE MENU **********\n";
    cout << "1. Skin Care\n";
    cout << "2. Hair Care\n";
    cout << "3. Bath & Body\n";
    cout << "4. Fragrances\n";
    cout << "5. View and Adjust Cart\n";
    cout << "6. Finalize Purchase\n";
    cout << "***************************************\n";
}

// Function to add products to the cart
void addProductToCart(vector<Product>& cart, const string& category, const vector<pair<string, int>>& products) {
    int productChoice, quantity;
    cout << "\nYou selected " << category << ".\n";
    for (size_t i = 0; i < products.size(); i++) {
        cout << i + 1 << ". " << products[i].first << " - Rs. " << products[i].second << endl;
    }
    cout << "Enter the number of the product you want to add to the cart: ";
    cin >> productChoice;
    if (productChoice < 1 || productChoice > products.size()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }
    cout << "Enter the quantity: ";
    cin >> quantity;
    cart.push_back(Product(products[productChoice - 1].first, products[productChoice - 1].second, quantity));
    cout << "Added " << quantity << " x " << products[productChoice - 1].first << " to your cart.\n"; 
}

// Function to display skin care products
void displaySkinCareMenu(vector<Product>& cart) {
    vector<pair<string, int>> skinCare = {
        {"Moisturizer", 500},
        {"Sunscreen", 700},
        {"Face Wash", 300},
        {"Serum", 1200}
    };
    addProductToCart(cart, "Skin Care", skinCare);
}

// Function to display hair care products
void displayHairCareMenu(vector<Product>& cart) {
    vector<pair<string, int>> hairCare = {
        {"Shampoo", 400},
        {"Conditioner", 350},
        {"Hair Oil", 250},
        {"Hair Mask", 800}
    };
    addProductToCart(cart, "Hair Care", hairCare);
}

// Function to display bath & body products
void displayBathBodyMenu(vector<Product>& cart) {
    vector<pair<string, int>> bathBody = {
        {"Body Wash", 450},
        {"Scrub", 550},
        {"Lotion", 600},
        {"Soap", 200}
    };
    addProductToCart(cart, "Bath & Body", bathBody);
}

// Function to display fragrances
void displayFragrancesMenu(vector<Product>& cart) {
    vector<pair<string, int>> fragrances = {
        {"Perfume", 1500},
        {"Body Mist", 800},
        {"Roll-On", 300},
        {"Room Spray", 700}
    };
    addProductToCart(cart, "Fragrances", fragrances);
}

// Function to view and adjust cart
void viewAndAdjustCart(vector<Product>& cart) {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "Your current cart:\n";
    int total = 0;
    for (size_t i = 0; i < cart.size(); i++) {
        cout << i + 1 << ". " << cart[i].productName << " - Rs. " << cart[i].price << " x " << cart[i].quantity << endl;
        total += cart[i].price * cart[i].quantity;
    }

    cout << "\nTotal: Rs. " << total << endl;
    char action;
    cout << "\nWould you like to (R)emove an item, (A)dd a new item, or (C)ontinue to finalize the purchase? ";
    cin >> action;
    if (action == 'R' || action == 'r') {
        int itemIndex;
        cout << "Enter the number of the item you want to remove (1-" << cart.size() << "): ";
        cin >> itemIndex;
        if (itemIndex >= 1 && itemIndex <= cart.size()) {
            cart.erase(cart.begin() + itemIndex - 1);
            cout << "Item removed from the cart.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to handle shopping
void handleShopping() {
    vector<Product> cart;
    int choice;
    do {
        displayMainMenuu();
        cout << "Enter the number of the category you want (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: displaySkinCareMenu(cart); break;
            case 2: displayHairCareMenu(cart); break;
            case 3: displayBathBodyMenu(cart); break;
            case 4: displayFragrancesMenu(cart); break;
            case 5: viewAndAdjustCart(cart); break;
            case 6:
                if (cart.empty()) {
                    cout << "Your cart is empty. Please add products to your cart.\n";
                } else {
                    cout << "Finalizing your purchase...\n";
                    int total = 0;
                    cout << "Your final cart:\n";
                    for (const auto& item : cart) {
                        cout << "- " << item.productName << " - Rs. " << item.price << " x " << item.quantity << " = Rs. " << item.price * item.quantity << endl;
                        total += item.price * item.quantity;
                    }
                    cout << "\nTotal Bill: Rs. " << total << endl;
                    cout << "Thank you for shopping with us!\n";
                }
                break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

void personalCareMenu() {
    vector<Product> cart;
    int choice;
    do {
        cout << "\nWelcome to the Personal Care Store\n";
        cout << "1. Start Shopping\n";
        cout << "2. View Main Menu\n";
        cout << "3. Exit Store\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: handleShopping(); break;
            case 2: displayMainMenuu(); break;
            case 3: cout << "Thank you for visiting our store.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
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
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "Your cart:\n";
    int total = 0;
    for (int i = 0; i < order.size(); i++) {
        cout << i + 1 << ". " << order[i].itemName << " - Rs. " << order[i].price << " x " << order[i].quantity << endl;
        total += order[i].price * order[i].quantity;
    }

    cout << "\nTotal: Rs. " << total << endl;
    char action;
    cout << "\nWould you like to (R)emove an item, (A)dd a new item or (C)ontinue to checkout? ";
    cin >> action;
    if (action == 'R' || action == 'r') {
        int itemIndex;
        cout << "Enter the number of the item you want to remove (1-" << order.size() << "): ";
        cin >> itemIndex;
        if (itemIndex >= 1 && itemIndex <= order.size()) {
            order.erase(order.begin() + itemIndex - 1);
            cout << "Item removed from the cart.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
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
// Jewelry Shop Interactive Menu
struct JewelryItem {
    string category;
    string name;
    int price;
    int discount;

    JewelryItem(string c, string n, int p, int d) : category(c), name(n), price(p), discount(d) {}
};

void displayJewelryCategories() {
    cout << "\n********** Jewelry Shop Categories **********\n";
    cout << "1. Hair Ornaments\n";
    cout << "2. Arms\n";
    cout << "3. Hands\n";
    cout << "4. Body\n";
    cout << "5. Feet\n";
    cout << "6. Special Functions\n";
    cout << "7. Gemstone Jewelry\n";
    cout << "8. Components\n";
    cout << "9. Exit Jewelry Shop\n";
    cout << "*********************************************\n";
}

void addJewelryItem(vector<JewelryItem>& cart, const string& category, const vector<JewelryItem>& items) {
    int itemChoice, quantity;
    cout << "\nCategory: " << category << "\n";
    for (size_t i = 0; i < items.size(); i++) {
        cout << i + 1 << ". " << items[i].name << " - Rs. " << items[i].price << " (" << items[i].discount << "% discount)\n";
    }
    cout << "Enter the number of the item you want to add to the cart: ";
    cin >> itemChoice;

    if (itemChoice < 1 || itemChoice > items.size()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }

    cart.push_back(items[itemChoice - 1]);
    cout << "Added " << items[itemChoice - 1].name << " to your cart.\n";
}

void viewCart(const vector<JewelryItem>& cart) {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    int total = 0;
    cout << "\nYour Cart:\n";
    for (size_t i = 0; i < cart.size(); i++) {
        int discountedPrice = cart[i].price * (100 - cart[i].discount) / 100;
        cout << i + 1 << ". " << cart[i].name << " - Rs. " << discountedPrice << " (Original: Rs. " << cart[i].price << ")\n";
        total += discountedPrice;
    }
    cout << "\nTotal: Rs. " << total << "\n";
}

void handleJewelryShop() {
    vector<JewelryItem> cart;
    int choice;

    vector<JewelryItem> hairOrnaments = {
        {"Hair Ornaments", "Crowns", 5000, 10},
        {"Hair Ornaments", "Headband", 1500, 5},
        {"Hair Ornaments", "Scrunchie", 500, 0},
        {"Hair Ornaments", "Hairclip", 1000, 5}
    };

    vector<JewelryItem> arms = {
        {"Arms", "Armlet (upper arm bracelets)", 3000, 10},
        {"Arms", "Bangle", 2500, 5},
        {"Arms", "Bracelet", 2000, 10},
        {"Arms", "Charm bracelet", 1800, 5},
        {"Arms", "Italian charm bracelet", 2200, 10},
        {"Arms", "Friendship bracelet", 1500, 0},
        {"Arms", "Gospel bracelet", 1700, 5},
        {"Arms", "Cuff links", 3000, 15}
    };

    vector<JewelryItem> hands = {
        {"Hands", "Ring", 5000, 10},
        {"Hands", "Championship ring", 7000, 15},
        {"Hands", "Class ring", 4000, 5},
        {"Hands", "Engagement ring", 20000, 20},
        {"Hands", "Wedding ring", 25000, 25},
        {"Hands", "Promise ring", 8000, 10},
        {"Hands", "Pre-engagement ring", 10000, 15},
        {"Hands", "Hand Chain Ring-bracelet", 12000, 10}
    };

    vector<JewelryItem> body = {
        {"Body", "Belly chain", 7000, 10},
        {"Body", "Body piercing jewelry", 2000, 5},
        {"Body", "Brooch", 3500, 10},
        {"Body", "Earring", 4000, 10},
        {"Body", "Chatelaine", 6000, 15},
        {"Body", "Necklace", 8000, 10},
        {"Body", "Mala set", 10000, 20}
    };

    vector<JewelryItem> feet = {
        {"Feet", "Anklet (ankle bracelets)", 3000, 10},
        {"Feet", "Toe ring", 2000, 5}
    };

    vector<JewelryItem> specialFunctions = {
        {"Special Functions", "Amulet", 4000, 10},
        {"Special Functions", "Medical alert jewelry", 5000, 15},
        {"Special Functions", "Prayer beads", 3000, 5}
    };

    vector<JewelryItem> gemstoneJewelry = {
        {"Gemstone Jewelry", "Gemstone Pendant", 15000, 20}
    };

    vector<JewelryItem> components = {
        {"Components", "Locket", 2000, 5},
        {"Components", "Medallion", 3000, 10},
        {"Components", "Pendant", 5000, 15}
    };

    do {
        displayJewelryCategories();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addJewelryItem(cart, "Hair Ornaments", hairOrnaments); break;
            case 2: addJewelryItem(cart, "Arms", arms); break;
            case 3: addJewelryItem(cart, "Hands", hands); break;
            case 4: addJewelryItem(cart, "Body", body); break;
            case 5: addJewelryItem(cart, "Feet", feet); break;
            case 6: addJewelryItem(cart, "Special Functions", specialFunctions); break;
            case 7: addJewelryItem(cart, "Gemstone Jewelry", gemstoneJewelry); break;
            case 8: addJewelryItem(cart, "Components", components); break;
            case 9: cout << "Exiting Jewelry Shop...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

        if (choice != 9) {
            char viewCartChoice;
            cout << "\nWould you like to view your cart? (Y/N): ";
            cin >> viewCartChoice;
            if (viewCartChoice == 'Y' || viewCartChoice == 'y') {
                viewCart(cart);
            }
        }
    } while (choice != 9);
}

// Bookstore
// program for bookstore
struct Book {
    string name;
    int price;
    int discount;

    Book(string n, int p, int d) : name(n), price(p), discount(d) {}
};

struct Order {
    string bookName;
    int price;
    int discount;
    int quantity;

    Order(string name, int p, int d, int q) : bookName(name), price(p), discount(d), quantity(q) {}
};

void displayMainMenu() {
    cout << "\n********** Welcome to the Bookstore **********\n";
    cout << "1. Programming Books\n";
    cout << "2. Data Science & AI Books\n";
    cout << "3. Fiction Books\n";
    cout << "4. Non-Fiction Books\n";
    cout << "5. View and Adjust Cart\n";
    cout << "6. Checkout\n";
    cout << "**********************************************\n";
}

void addBookToCart(vector<Order>& cart, const string& category, const vector<Book>& books) {
    int choice, quantity;
    cout << "\nYou selected " << category << ".\n";
    for (size_t i = 0; i < books.size(); i++) {
        cout << i + 1 << ". " << books[i].name << " - Rs. " << books[i].price 
             << " (" << books[i].discount << "% discount)\n";
    }
    cout << "Enter the number of the book you want to add to the cart: ";
    cin >> choice;
    if (choice < 1 || choice > books.size()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }
    cout << "Enter the quantity: ";
    cin >> quantity;
    cart.push_back(Order(books[choice - 1].name, books[choice - 1].price, books[choice - 1].discount, quantity));
    cout << "Added " << quantity << " x " << books[choice - 1].name << " to your cart.\n";
}

void programmingBooksMenu(vector<Order>& cart) {
    vector<Book> programmingBooks = {
        {"C++ Programming", 1000, 10},
        {"Python Basics", 1200, 15},
        {"Java Fundamentals", 1100, 12},
        {"Web Development with JavaScript", 1300, 18}
    };
    addBookToCart(cart, "Programming Books", programmingBooks);
}

void dataScienceBooksMenu(vector<Order>& cart) {
    vector<Book> dataScienceBooks = {
        {"Data Science Fundamentals", 1500, 20},
        {"Machine Learning Basics", 1600, 18},
        {"Deep Learning with Python", 1700, 25},
        {"Artificial Intelligence Essentials", 1800, 22}
    };
    addBookToCart(cart, "Data Science & AI Books", dataScienceBooks);
}

void fictionBooksMenu(vector<Order>& cart) {
    vector<Book> fictionBooks = {
        {"The Great Gatsby", 500, 5},
        {"To Kill a Mockingbird", 600, 7},
        {"1984 by George Orwell", 700, 10},
        {"Pride and Prejudice", 550, 6}
    };
    addBookToCart(cart, "Fiction Books", fictionBooks);
}

void nonFictionBooksMenu(vector<Order>& cart) {
    vector<Book> nonFictionBooks = {
        {"Sapiens: A Brief History of Humankind", 800, 12},
        {"Atomic Habits", 850, 10},
        {"Educated: A Memoir", 900, 15},
        {"The Subtle Art of Not Giving a F*ck", 750, 8}
    };
    addBookToCart(cart, "Non-Fiction Books", nonFictionBooks);
}

void viewAndAdjustCart(vector<Order>& cart) {
    if (cart.empty()) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "Your current cart:\n";
    int total = 0;
    for (size_t i = 0; i < cart.size(); i++) {
        int discountedPrice = cart[i].price - (cart[i].price * cart[i].discount / 100);
        cout << i + 1 << ". " << cart[i].bookName << " - Rs. " << cart[i].price 
             << " (" << cart[i].discount << "% off) x " << cart[i].quantity 
             << " = Rs. " << discountedPrice * cart[i].quantity << "\n";
        total += discountedPrice * cart[i].quantity;
    }

    cout << "\nTotal: Rs. " << total << "\n";
    char action;
    cout << "\nWould you like to (R)emove a book, (A)dd a new book, or (C)ontinue? ";
    cin >> action;
    if (action == 'R' || action == 'r') {
        int bookIndex;
        cout << "Enter the number of the book you want to remove (1-" << cart.size() << "): ";
        cin >> bookIndex;
        if (bookIndex >= 1 && bookIndex <= cart.size()) {
            cart.erase(cart.begin() + bookIndex - 1);
            cout << "Book removed from the cart.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void checkout(const vector<Order>& cart) {
    if (cart.empty()) {
        cout << "Your cart is empty. Add some books first!\n";
        return;
    }

    int total = 0;
    cout << "Your final order:\n";
    for (const auto& order : cart) {
        int discountedPrice = order.price - (order.price * order.discount / 100);
        cout << "- " << order.bookName << " - Rs. " << discountedPrice 
             << " x " << order.quantity 
             << " = Rs. " << discountedPrice * order.quantity << "\n";
        total += discountedPrice * order.quantity;
    }
    cout << "\nTotal Bill: Rs. " << total << "\n";
    cout << "Thank you for shopping at the Bookstore!\n";
}

void bookstore() {
    vector<Order> cart;
    int choice;

    do {
        displayMainMenu();
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: programmingBooksMenu(cart); break;
            case 2: dataScienceBooksMenu(cart); break;
            case 3: fictionBooksMenu(cart); break;
            case 4: nonFictionBooksMenu(cart); break;
            case 5: viewAndAdjustCart(cart); break;
            case 6: checkout(cart); break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
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

// Jewelry Shop
void jewelryShop() {
    handleJewelryShop();
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

// Function to handle cosmetics shop
void cosmeticsShop() {
    personalCareMenu();
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
