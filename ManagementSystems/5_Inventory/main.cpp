#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

void clearScreen()
{
    system("cls");
}

void pauseScreen()
{
    system("pause");
}

bool isValidInt(int &input, int min, int max)
{
    cin >> input;
    if (cin.fail() || input < min || input > max)
    {
        cin.clear();           // Clears the error flag
        cin.ignore(100, '\n'); // Ignores invalid input (up to 100 characters)
        return false;
    }
    return true;
}

bool isValidDouble(double &input, double min, double max)
{
    cin >> input;
    if (cin.fail() || input < min || input > max)
    {
        cin.clear();           // Clears the error flag
        cin.ignore(100, '\n'); // Ignores invalid input (up to 100 characters)
        return false;
    }
    return true;
}

class Product
{
    int ID;
    string name;
    int stock;
    double price;

public:
    Product(int id = 0, string n = "", int s = 0, double p = 0.0) : ID(id), name(n), stock(s), price(p) {}

    // Setters
    void setID(int id) { ID = id; }
    void setName(string n) { name = n; }
    void setStock(int s) { stock = s; }
    void setPrice(double p) { price = p; }

    // Getters
    int getID() const { return ID; }
    string getName() const { return name; }
    int getStock() const { return stock; }
    double getPrice() const { return price; }

    // Method to update stock
    void increaseStock(int amount)
    {
        stock += amount;
    }

    void sellStock(int amount)
    {
        if (stock >= amount)
        {
            stock -= amount;
        }
        else
        {
            cout << "Not enough stock to sell!" << endl;
        }
    }

    // Display product details
    void display() const
    {
        cout << "-----------------------------------------------" << endl;
        cout << left << setw(10) << "ID: " << setw(10) << ID << endl;
        cout << left << setw(10) << "Name: " << setw(30) << name << endl;
        cout << left << setw(10) << "Stock: " << setw(10) << stock << endl;
        cout << left << setw(10) << "Price:    $ " << price << endl;
        cout << "-----------------------------------------------" << endl;
    }

    // Write the product data to a file
    void writeToFile(ofstream &outFile) const
    {
        outFile << ID << endl
                << name << endl
                << stock << endl
                << fixed << setprecision(2) << price << endl;
    }
};

class Store
{
    string name;
    Product *products; // Pointer to dynamically allocated array of products
    int numProducts;   // Keep track of how many products are in the store

public:
    Store(string storeName) : name(storeName), numProducts(0), products(nullptr) {}

    ~Store()
    {
        delete[] products; // Free the allocated memory when done
    }

    // Method to read products from a file
    void loadProductsFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Failed to open file!" << endl;
            return;
        }

        file >> numProducts;
        file.ignore();

        // Directly allocate memory based on the number of products
        products = new Product[numProducts];

        for (int i = 0; i < numProducts; ++i)
        {
            int id, stock;
            string name;
            double price;

            file >> id;
            file.ignore(); // To ignore the newline character after reading the ID
            getline(file, name);
            file >> stock >> price;
            file.ignore(); // To ignore the newline character after reading the price

            products[i] = Product(id, name, stock, price);
        }

        file.close();
    }

    // Method to write the products back to a file after changes
    void writeProductsToFile(const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Failed to open file!" << endl;
            return;
        }

        file << numProducts << endl;

        for (int i = 0; i < numProducts; ++i)
        {
            products[i].writeToFile(file);
        }

        file.close();
    }

    // Method to add a new product
    void addProduct(int id, string name, int stock, double price)
    {
        Product *tempProducts = new Product[numProducts + 1]; // Temporary array for new product

        for (int i = 0; i < numProducts; ++i)
        {
            tempProducts[i] = products[i]; // Copy old products
        }

        tempProducts[numProducts] = Product(id, name, stock, price); // Add new product
        delete[] products;                                           // Free the old array
        products = tempProducts;                                     // Point to the new array
        numProducts++;                                               // Update product count

        cout << "Product added!" << endl;
    }

    // Method to remove a product by ID
    void removeProduct(int productID)
    {
        bool found = false;
        for (int i = 0; i < numProducts; ++i)
        {
            if (products[i].getID() == productID)
            {
                Product *tempProducts = new Product[numProducts - 1]; // Temporary array for remaining products
                for (int j = 0, k = 0; j < numProducts; ++j)
                {
                    if (j != i)
                    {
                        tempProducts[k++] = products[j]; // Copy all except the removed product
                    }
                }
                delete[] products;       // Free the old array
                products = tempProducts; // Point to the new array
                numProducts--;           // Update product count
                found = true;
                cout << "Product removed!" << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Product not found!" << endl;
        }
    }

    // Method to increase stock of a product
    void increaseStock(int productID, int amount)
    {
        bool found = false;
        for (int i = 0; i < numProducts; ++i)
        {
            if (products[i].getID() == productID)
            {
                products[i].increaseStock(amount);
                cout << "Stock increased!" << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Product not found!" << endl;
        }
    }

    // Method to sell stock of a product
    void sellStock(int productID, int amount)
    {
        bool found = false;
        for (int i = 0; i < numProducts; ++i)
        {
            if (products[i].getID() == productID)
            {
                products[i].sellStock(amount);
                cout << "Stock sold!" << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Product not found!" << endl;
        }
    }

    // Method to generate a report of the remaining stock
    void generateReport()
    {
        cout << "Inventory Report:" << endl;
        for (int i = 0; i < numProducts; ++i)
        {
            products[i].display();
        }
    }
    // Method to check if the ID is unique
    bool isUniqueID(int id) const
    {
        for (int i = 0; i < numProducts; ++i)
        {
            if (products[i].getID() == id)
            {
                return false; // ID is not unique
            }
        }
        return true; // ID is unique
    }
};

int main()
{
    Store myStore("My Store");

    // Load products from file
    myStore.loadProductsFromFile("products.txt");

    int choice;
    while (true)
    {
        cout << "------ Inventory Management System ------" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Remove Product" << endl;
        cout << "3. Increase Stock" << endl;
        cout << "4. Sell Stock" << endl;
        cout << "5. Generate Report" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        while (!isValidInt(choice, 1, 6))
        {
            cout << "Invalid input. Please enter a number between 1 and 6: ";
        }

        int id, stock, amount;
        string name;
        double price;

        switch (choice)
        {
        case 1:
            cout << "Enter product ID: ";
            while (!isValidInt(id, 100, 999) || !myStore.isUniqueID(id))
            {
                if (!myStore.isUniqueID(id))
                {
                    cout << "Invalid ID. The ID " << id << " is already taken. Please enter a unique ID between 100 and 999: ";
                }
                else
                {
                    cout << "Invalid ID. Enter a valid ID between 100 and 999: ";
                }
            }

            cout << "Enter product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter stock: ";
            while (!isValidInt(stock, 0, 1000))
            {
                cout << "Invalid stock. Enter a valid stock quantity between 0 and 1000: ";
            }
            cout << "Enter price: ";
            while (!isValidDouble(price, 0.01, 10000))
            {
                cout << "Invalid price. Enter a valid price between 0.01 and 10000: ";
            }
            
            myStore.addProduct(id, name, stock, price);
            myStore.writeProductsToFile("products.txt");

            break;
        case 2:
            cout << "Enter product ID to remove: ";
            while (!isValidInt(id, 100, 999))
            {
                cout << "Invalid ID. Enter a valid ID between 100 and 999: ";
            }
            myStore.removeProduct(id);
            myStore.writeProductsToFile("products.txt");
            break;
        case 3:
            cout << "Enter product ID to increase stock: ";
            while (!isValidInt(id, 100, 999))
            {
                cout << "Invalid ID. Enter a valid ID between 100 and 999: ";
            }
            cout << "Enter amount to increase: ";
            while (!isValidInt(amount, 0, 1000))
            {
                cout << "Invalid amount. Enter a valid amount between 0 and 1000: ";
            }
            myStore.increaseStock(id, amount);
            myStore.writeProductsToFile("products.txt");
            break;
        case 4:
            cout << "Enter product ID to sell stock: ";
            while (!isValidInt(id, 100, 999))
            {
                cout << "Invalid ID. Enter a valid ID between 100 and 999: ";
            }
            cout << "Enter amount to sell: ";
            while (!isValidInt(amount, 0, 1000))
            {
                cout << "Invalid amount. Enter a valid amount between 0 and 1000: ";
            }
            myStore.sellStock(id, amount);
            myStore.writeProductsToFile("products.txt");
            break;
        case 5:
            myStore.generateReport();
            break;
        case 6:
            myStore.writeProductsToFile("products.txt");
            cout << "Exiting and saving changes to file." << endl;
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }

        cout << "Would you like to perform another operation? (1 = Yes, 0 = No): ";
        int continueChoice;
        while (!isValidInt(continueChoice, 0, 1))
        {
            cout << "Invalid input. Enter 1 for Yes or 0 for No: ";
        }
        if (continueChoice == 0)
            break;
    }

    return 0;
}
