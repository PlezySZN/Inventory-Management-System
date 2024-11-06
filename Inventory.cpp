#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

using std::vector, std::string, std::cout, std::cin, std::endl;

struct Product
{
    string idNum;
    string name;
    string category;
    double price;
    double stock;
};

// Keven Paulino Ferrer
void addProduct(vector<Product> &userProducts)
{
    Product newProduct;
    char continuar;
    do
    {
        cout << "\n===========================================\n";
        cout << "========Inventory Management System========\n";
        cout << "=============Adding New Product============\n";

        do
        {

            cout << "Enter Identification Number (----): ";
            std::getline(cin, newProduct.idNum);

            for (int i = 0; i < userProducts.size(); i++) // look for user input in the vector userProducts
            {
                if (newProduct.idNum == userProducts.at(i).idNum) // if found
                {
                    cout << "\n=======================================\n";
                    cout << "=======ERROR: ID Already in Use=======\n";
                    cout << "=======================================\n";
                    newProduct.idNum = "!@#";
                    break;
                }
            }

            if (newProduct.idNum == "!@#")
            {
                continue;
            }
            if (newProduct.idNum.length() != 4)
            {
                cout << "\n===========================================================\n";
                cout << "=====ERROR: ID Can't be more or less than 4 characters=====\n";
                cout << "===========================================================\n";
                continue;
            }

        } while (newProduct.idNum.length() != 4);

        cout << "Enter Name of the Product: ";
        std::getline(cin, newProduct.name);

        cout << "Enter the category (food, drink, etc...): ";
        std::getline(cin, newProduct.category);

        do
        {
            cout << "Enter the Price of the Product:";
            cin >> newProduct.price;

            if ((!cin))
            {
                cout << "\n=======================================================\n";
                cout << "=====ERROR: Invalid input. Please Enter a number ======\n";
                cout << "=======================================================\n";

                cin.clear();
                cin.ignore();

                continue;
            }
            if (newProduct.price < 0)
            {
                cout << "\n===========================================\n";
                cout << "=====ERROR: Price Can't be Less than 0======\n";
                cout << "===========================================\n";
            }
        } while (newProduct.price < 0);

        do
        {
            cout << "Enter the Amount in Stock:";
            cin >> newProduct.stock;

            if ((!cin))
            {
                cout << "\n=======================================================\n";
                cout << "=====ERROR: Invalid input. Please Enter a number ======\n";
                cout << "=======================================================\n";

                cin.clear();
                cin.ignore();

                continue;
            }

            if (newProduct.stock < 0)
            {
                cout << "\n============================================\n";
                cout << "======ERROR: Stock Can't be Less tha 0======\n";
                cout << "============================================\n";
            }

        } while (newProduct.stock < 0);

        userProducts.push_back(newProduct);

        cout << "Do You Wish to Continue Adding Products (Y/N)";
        cin >> continuar;
        cin.ignore();
        continuar = toupper(continuar);
        if (continuar == 'N')
        {
            break;
        }
    } while (continuar == 'Y');
}

void deleteProduct()
{
}

// Harrys Santiago Santana
void updateProduct(vector<Product> &userProducts)
{
    // Create a variable to search if 'id' is = to 'idNum' on userProducts
    string id;
    int userChoice;

    cout << "\n===========================================\n";
    cout << "========Inventory Management System========\n";
    cout << "==============Updating Product=============\n";
    cout << "Enter Product ID to update: ";
    cin >> id;
    cin.ignore(); // Clean Buffer

    // Search the product in vector 'userProduct' by ID
    auto it = find_if(userProducts.begin(), userProducts.end(), [&id](Product &userProduct)
                      { return userProduct.idNum == id; });

    // If product is found, proceed to update its details
    if (it != userProducts.end())
    {
        string newName;
        string newCategory;
        double newStock;
        double newPrice;

        // Show current product details
        cout << "===========================================\n";
        cout << "Current product name: " << it->name << endl;
        cout << "============================================\n";
        cout << "1. Update product \n";
        cout << "2. Don't make changes.\n\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        cin.ignore();

        if (userChoice == 1)
        {
            cout << "Enter product name to update: ";
            std::getline(cin, newName);
            it->name = newName;
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }

        cout << "===========================================\n";
        cout << "Current product category: " << it->category << endl;
        cout << "============================================\n";
        cout << "1. Update product \n";
        cout << "2. Don't make changes.\n\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        cin.ignore();

        if (userChoice == 1)
        {
            cout << "Enter product category to update: ";
            std::getline(cin, newCategory);
            it->category = newCategory;
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }

        cout << "===========================================\n";
        cout << "Current price: $" << std::fixed << std::setprecision(2) << it->price << endl;
        cout << "============================================\n\n";
        cout << "1. Update product \n";
        cout << "2. Don't make changes.\n\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        cin.ignore();

        if (userChoice == 1)
        {
            do
            {
                cout << "Enter product price to update: ";
                cin >> newPrice;  
                it->price = newPrice;
            } while (newPrice < 0);
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }

        cout << "===========================================\n";
        cout << "Current stock: " << it->stock << endl;
        cout << "============================================\n\n";
        cout << "1. Update product \n";
        cout << "2. Don't make changes.\n\n";
        cout << "Enter your choice: ";
        cin >> userChoice;
        cin.ignore();

        if (userChoice == 1)
        {
            do
            {
                cout << "Enter product stock to update: ";
                cin >> newStock;
                it->stock = newStock;
            } while (newStock < 0);
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }
    }
    else
    {
        cout << "\n=======================================\n";
        cout << "=========ERROR: ID not found=========\n";
        cout << "=========================================\n";
    }
}

// Harrys Santiago Santana
void printInventory(vector<Product> &userProducts)
{
    cout << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
         << "| " << std::setw(15) << "Name"
         << "| " << std::setw(15) << "Category"
         << "| " << std::setw(15) << "Stock"
         << "| " << std::setw(15) << "Price"
         << std::endl;

    cout << "===================================================================\n"; // Second row of inventory (Divider Line)

    for (auto &product : userProducts) // Third row of inventory (All Products)
    {

        cout << "| " << std::setw(6) << product.idNum
             << "| " << std::setw(15) << product.name
             << "| " << std::setw(15) << product.category
             << "| " << std::setw(15) << product.stock
             << "| " << std::setw(0) << "$"
             << std::setw(15) << std::fixed << std::setprecision(2) << product.price
             << std::endl;
    }
}

// Keven Paulino Ferrer
void searchBy_Category_Name_id(vector<Product> &userProducts, vector<Product> &searchProduct, int searchChoice)
{
    if (searchChoice == 1) // if it was by Id
    {
        // Harrys Santiago Santana
        string id;
        cout << "Enter Id: ";
        std::getline(cin, id);
        // Iteration through userProducts to find products that match 'ID'
        auto it = find_if(userProducts.begin(), userProducts.end(), [&id](Product &matchedProduct)
                          { return matchedProduct.idNum == id; });

        if (it != userProducts.end()) // If found
        {
            cout << std::left << "| " << std::setw(15) << "ID"
                 << "| " << std::setw(20) << "Name"
                 << "| " << std::setw(15) << "Category"
                 << "| " << std::setw(15) << "Stock"
                 << "| " << std::setw(15) << "Price"
                 << std::endl;

            cout << "====================================================================================\n";

            cout << "| " << std::setw(15) << it->idNum
                 << "| " << std::setw(20) << it->name
                 << "| " << std::setw(15) << it->category
                 << "| " << std::setw(15) << it->stock
                 << "| " << std::setw(0) << "$"
                 << std::setw(15) << std::fixed << std::setprecision(2) << it->price
                 << std::endl;
        }
        else
        {
            cout << "\n=======================================\n";
            cout << "======ERROR: ID Couldn't be Found======\n";
            cout << "=======================================\n";
        }
    } // Keven Paulino Ferrer
    else if (searchChoice == 2) // if search by category
    {
        string userCategory;
        cout << "Enter Category: ";
        std::getline(cin, userCategory);
        for (int i = 0; i < userProducts.size(); i++) // look for user input in the vector userProducts
        {
            if (userCategory != userProducts.at(i).category)
            {
                continue;
            }
            searchProduct.push_back(userProducts.at(i)); // pushes element of userProducts to searchProduct
        }
        if (searchProduct.empty()) // if searchProduct is empty
        {
            cout << "\n=============================================\n";
            cout << "======ERROR: Category Couldn't be Found======\n";
            cout << "=============================================\n";
        }
    }
    else if (searchChoice == 3) // if search by Name
    {
        string userName;
        cout << "Enter Name: ";
        std::getline(cin, userName);
        for (int i = 0; i < userProducts.size(); i++) // look for user input in the vector userProducts
        {
            if (userName != userProducts.at(i).name)
            {
                continue;
            }
            searchProduct.push_back(userProducts.at(i)); // pushes element of userProducts to searchProduct
        }
        if (searchProduct.empty()) // if searchProduct is empty
        {
            cout << "\n=========================================\n";
            cout << "======ERROR: Name Couldn't be Found======\n";
            cout << "=========================================\n";
        }
    }
}
// Keven Paulino Ferrer
void searchProduct(vector<Product> &userProducts)
{
    vector<Product> searchProduct;
    int searchChoice;
    do
    {
        cout << "\n============================================\n";
        cout << "========Inventory Management System=========\n";
        cout << "================Search Menu=================\n";
        cout << "1. Search by ID \n";
        cout << "2. Search by category \n";
        cout << "3. Search by Name \n";
        cout << "Enter your choice: ";
        cin >> searchChoice;
        cin.ignore();

    } while (searchChoice < 1 || searchChoice > 3);

    searchBy_Category_Name_id(userProducts, searchProduct, searchChoice);

    if (searchChoice == 2 || searchChoice == 3)
    {
        // Harrys Santiago Santana
        cout << std::left << "| " << std::setw(15) << "ID"
             << "| " << std::setw(20) << "Name"
             << "| " << std::setw(15) << "Category"
             << "| " << std::setw(15) << "Stock"
             << "| " << std::setw(15) << "Price"
             << std::endl;

        cout << "====================================================================================\n";
    }
    // Keven Paulino Ferrer
    for (Product Search : searchProduct)
    {
        if (searchChoice == 1) // if it was by Id
        {
            break;
        }

        // Harrys Santiago Santana
        cout << "| " << std::setw(15) << Search.idNum
             << "| " << std::setw(20) << Search.name
             << "| " << std::setw(15) << Search.category
             << "| " << std::setw(15) << Search.stock
             << "| " << std::setw(0) << "$"
             << std::setw(15) << std::fixed << std::setprecision(2) << Search.price
             << std::endl;
    }
    searchProduct.clear(); // clears vector just in case
}

int main()
{
    int menuChoice;
    vector<Product> userProducts;
    do
    {
        cout << "\n============================================\n";
        cout << "========Inventory Management System=========\n";
        cout << "===============Inventory Menu===============\n";
        cout << "1. Add a new product\n";
        cout << "2. Delete a product\n";
        cout << "3. Update a product\n";
        cout << "4. Search for a product\n";
        cout << "5. Print inventory\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> menuChoice;
        cin.ignore();

        switch (menuChoice)
        {

        case 1:
            addProduct(userProducts);
            break;
        case 2:
            deleteProduct();
            break;
        case 3:
            updateProduct(userProducts);
            break;
        case 4:
            searchProduct(userProducts);
            break;
        case 5:
            printInventory(userProducts);
            break;
        }

    } while (menuChoice != 6);
    return 0;
}