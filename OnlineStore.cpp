#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Product {
    int productID;
    string name;
    string category;
};

struct Order {
    int orderID;
    int productID;
    int quantity;
    string customerID;
    time_t orderDate;
};

unordered_map<string, string> adminData = {{"admin", "admin123"}};
unordered_map<string, string> customerData;

vector<Product> products = {
    {101, "Smartphone", "Electronics"},
    {102, "Wall hanging", "Home"},
    {103, "Curtains", "Home"},
    {104, "Flour", "Grocery"},
    {105, "TV", "Electronics"}
};

map<int, int> productStock = {
    {101, 20},
    {102, 50},
    {103, 10},
    {104, 30},
    {105, 25}
};

list<Order> orderHistory;

void adminMenu();
void customerMenu(const string& customerID);
void registerUser();
bool loginUser(string& userID, bool isAdmin);

void viewProducts() {
    cout << "Available Products:\n";
    for (const auto& product : products) {
        cout << "ID: " << product.productID << " | Name: " << product.name 
             << " | Category: " << product.category 
             << " | Stock: " << productStock[product.productID] << endl;
    }
}

void viewOrderHistory() {
    cout << "Order History:\n";
    for (const auto& order : orderHistory) {
        cout << "Order ID: " << order.orderID << " | Product ID: " << order.productID 
             << " | Quantity: " << order.quantity 
             << " | Customer ID: " << order.customerID << endl;
    }
}

void addProduct() {
    int id, stock;
    string name, category;
    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Product Name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Enter Product Category: ";
    getline(cin, category);
    cout << "Enter Stock Quantity: ";
    cin >> stock;

    products.push_back({id, name, category});
    productStock[id] = stock;
    cout << "Product added successfully.\n";
}

void placeOrder(const string& customerID) {
    int productID, quantity;
    cout << "Enter Product ID to order: ";
    cin >> productID;
    cout << "Enter Quantity: ";
    cin >> quantity;

    if (productStock[productID] >= quantity) {
        int orderID = orderHistory.size() + 1;
        orderHistory.push_back({orderID, productID, quantity, customerID, time(0)});
        productStock[productID] -= quantity;
        cout << "Order placed successfully.\n";
    } else {
        cout << "Insufficient stock.\n";
    }
}

void adminMenu() {
    int choice;
    do {
        cout << "\nAdmin Menu:\n1. View Products\n2. View Order History\n3. Add Product\n4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                viewOrderHistory();
                break;
            case 3:
                addProduct();
                break;
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

void customerMenu(const string& customerID) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n1. View Products\n2. Place Order\n3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                placeOrder(customerID);
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void registerUser() {
    string userID, password;
    cout << "Enter new username: ";
    cin >> userID;
    if (customerData.find(userID) != customerData.end()) {
        cout << "Username already exists.\n";
        return;
    }
    cout << "Enter password: ";
    cin >> password;
    customerData[userID] = password;
    cout << "Registration successful.\n";
}

bool loginUser(string& userID, bool isAdmin) {
    string password;
    cout << "Enter username: ";
    cin >> userID;
    cout << "Enter password: ";
    cin >> password;

    if (isAdmin) {
        return adminData.find(userID) != adminData.end() && adminData[userID] == password;
    } else {
        return customerData.find(userID) != customerData.end() && customerData[userID] == password;
    }
}

int main() {
    int choice;
    string userID;
    while (true) {
        cout << "\nWelcome to the Online Product Store:\n1. Admin Login\n2. Customer Login\n3. Customer Registration\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (loginUser(userID, true)) {
                    cout << "Admin logged in successfully.\n";
                    adminMenu();
                } else {
                    cout << "Invalid Admin credentials.\n";
                }
                break;
            case 2:
                if (loginUser(userID, false)) {
                    cout << "Customer logged in successfully.\n";
                    customerMenu(userID);
                } else {
                    cout << "Invalid Customer credentials.\n";
                }
                break;
            case 3:
                registerUser();
                break;
            case 4:
                cout << "Exiting the program...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
