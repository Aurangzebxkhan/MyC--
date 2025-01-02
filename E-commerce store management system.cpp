#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Product {
    int productID;
    string name;
    string category;
    float price;
    int stockQuantity;
};

struct CartItem {
    int productID;
    string name;
    int quantity;
    float price;
};

vector<Product> loadProducts();
void saveProducts(const vector<Product>& products);
void displayProducts(const vector<Product>& products);
void searchProduct(const vector<Product>& products);
void userMenu(vector<Product>& products);
void adminMenu(vector<Product>& products);
void addToCart(vector<Product>& products, vector<CartItem>& cart);
void checkout(vector<Product>& products, vector<CartItem>& cart);
void addProduct(vector<Product>& products);
void updateProduct(vector<Product>& products);
void deleteProduct(vector<Product>& products);
void viewSalesReport();

int main() {
    vector<Product> products = loadProducts();

    int choice;
    do {
        cout << "\n=== E-Commerce Store Management System ===" << endl;
        cout << "1. User Menu" << endl;
        cout << "2. Admin Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userMenu(products);
                break;
            case 2:
                adminMenu(products);
                break;
            case 3:
                saveProducts(products);
                cout << "Exiting... Data saved successfully." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

vector<Product> loadProducts() {
    vector<Product> products;
    ifstream inFile("products.txt");

    if (!inFile) {
        cerr << "Error loading product data. Starting with an empty product list." << endl;
        return products;
    }

    Product product;
    while (inFile >> product.productID >> product.name >> product.category >> product.price >> product.stockQuantity) {
        products.push_back(product);
    }

    inFile.close();
    return products;
}

void saveProducts(const vector<Product>& products) {
    ofstream outFile("products.txt");
    for (const auto& product : products) {
        outFile << product.productID << " "
                << product.name << " "
                << product.category << " "
                << product.price << " "
                << product.stockQuantity << endl;
    }
    outFile.close();
}

void displayProducts(const vector<Product>& products) {
    cout << "\n=== Product List ===" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Category" << setw(10) << "Price" << "Stock" << endl;
    cout << string(60, '-') << endl;
    for (const auto& product : products) {
        cout << left << setw(10) << product.productID
             << setw(20) << product.name
             << setw(15) << product.category
             << setw(10) << product.price
             << product.stockQuantity << endl;
    }
}

void searchProduct(const vector<Product>& products) {
    int choice;
    cout << "\nSearch by: 1. ID 2. Category" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;
        for (const auto& product : products) {
            if (product.productID == id) {
                cout << "Product Found: " << product.name << " - " << product.category << " - $" << product.price << endl;
                return;
            }
        }
        cout << "Product not found." << endl;
    } else if (choice == 2) {
        string category;
        cout << "Enter Category: ";
        cin >> category;
        bool found = false;
        for (const auto& product : products) {
            if (product.category == category) {
                cout << "Product Found: " << product.name << " - $" << product.price << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No products found in this category." << endl;
        }
    } else {
        cout << "Invalid choice." << endl;
    }
}

void userMenu(vector<Product>& products) {
    vector<CartItem> cart;
    int choice;
    do {
        cout << "\n=== User Menu ===" << endl;
        cout << "1. View Products" << endl;
        cout << "2. Search Products" << endl;
        cout << "3. Add to Cart" << endl;
        cout << "4. Checkout" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts(products);
                break;
            case 2:
                searchProduct(products);
                break;
            case 3:
                addToCart(products, cart);
                break;
            case 4:
                checkout(products, cart);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}

void adminMenu(vector<Product>& products) {
    int choice;
    do {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. View Sales Report" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(products);
                break;
            case 2:
                updateProduct(products);
                break;
            case 3:
                deleteProduct(products);
                break;
            case 4:
                viewSalesReport();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}

void addToCart(vector<Product>& products, vector<CartItem>& cart) {
    int id, quantity;
    cout << "Enter Product ID to add to cart: ";
    cin >> id;
    cout << "Enter quantity: ";
    cin >> quantity;

    for (auto& product : products) {
        if (product.productID == id) {
            if (product.stockQuantity >= quantity) {
                cart.push_back({id, product.name, quantity, product.price * quantity});
                product.stockQuantity -= quantity;
                cout << "Added to cart: " << product.name << " x " << quantity << endl;
                return;
            } else {
                cout << "Insufficient stock." << endl;
                return;
            }
        }
    }
    cout << "Product not found." << endl;
}

void checkout(vector<Product>& products, vector<CartItem>& cart) {
    float total = 0;
    cout << "\n=== Checkout ===" << endl;
    for (const auto& item : cart) {
        cout << item.name << " x " << item.quantity << " - $" << item.price << endl;
        total += item.price;
    }
    cout << "Total Bill: $" << fixed << setprecision(2) << total << endl;
    cart.clear();
}

void addProduct(vector<Product>& products) {
    Product product;
    cout << "Enter Product ID: ";
    cin >> product.productID;
    cout << "Enter Name: ";
    cin >> product.name;
    cout << "Enter Category: ";
    cin >> product.category;
    cout << "Enter Price: ";
    cin >> product.price;
    cout << "Enter Stock Quantity: ";
    cin >> product.stockQuantity;
    products.push_back(product);
    cout << "Product added successfully." << endl;
}

void updateProduct(vector<Product>& products) {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;
    for (auto& product : products) {
        if (product.productID == id) {
            cout << "Enter new details:" << endl;
            cout << "Enter Name: ";
            cin >> product.name;
            cout << "Enter Category: ";
            cin >> product.category;
            cout << "Enter Price: ";
            cin >> product.price;
            cout << "Enter Stock Quantity: ";
            cin >> product.stockQuantity;
            cout << "Product updated successfully." << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void deleteProduct(vector<Product>& products) {
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->productID == id) {
            products.erase(it);
            cout << "Product deleted successfully." << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void viewSalesReport() {
    cout << "\n=== Sales Report ===" << endl;
    ifstream salesFile("sales.txt");
    if (!salesFile) {
        cerr << "No sales data available." << endl;
        return;
    }

    string line;
    while (getline(salesFile, line)) {
        cout << line << endl;
    }
    salesFile.close();
}
