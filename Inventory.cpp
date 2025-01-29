#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdlib.h>

using std::vector, std::string, std::cout, std::cin, std::endl;

struct Product
{
    string idNum;
    string name;
    string category;
    string unit;
    double price;
    double stock;
};

const int MAX_NAME_LENGTH = 20;
const int ID_LENGTH = 4;
const int MAX_CATEGORY_LENGTH = 20;
const int MAX_UNIT_LENGTH = 5;
const double MIN_PRICE = 0.0;
const double MIN_STOCK = 0.0;

void clearScreen()
{
    for (int i = 0; i < 50; ++i)
    {
        std::cout << "\n";
    }
    system("cls");
}

// Harrys Santiago Santana
template <typename T>
void validateInput(T &input) // Validate double input
{
    while (true)
    {
        cin >> input;
        if (cin.fail())
        {
            clearScreen();
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n==============================\n";
            cout << "=====ERROR: Invalid input=====\n";
            cout << "==============================\n\n";
            cout << "Please enter a valid input: ";
        }
        else
        {
            break;
        }
    }
}

// Harrys Santiago Santana
void validateStringInput(string &input)
{
    while (true)
    {
        std::getline(cin, input);
        if (input.empty())
        {
            clearScreen();
            cout << "\n==============================\n";
            cout << "=====ERROR: Invalid input=====\n";
            cout << "==============================\n";
            cout << "Please enter a valid string: ";
        }
        else
        {
            break;
        }
    }
}

// Harrys Santiago Santana
void validateIdLength(string &id)
{
    while (id.length() != ID_LENGTH)
    {
        clearScreen();
        cout << "\n=============================================\n";
        cout << "=====ERROR: ID number must have 4 digits=====\n";
        cout << "=============================================\n";
        cout << "Enter Identification Number (----): ";
        validateStringInput(id);
    }
}

// Harrys Santiago Santana
void validateNameLength(string &name)
{
    while (name.length() > MAX_NAME_LENGTH)
    {
        clearScreen();
        cout << "=======================================================\n";
        cout << "=====ERROR: Name must have less than 20 characters=====\n";
        cout << "=======================================================\n";
        cout << "Enter Name of the Product: ";
        validateStringInput(name);
    }
}

// Harrys Santiago Santana
void validateCategoryLength(string &category)
{
    while (category.length() > MAX_CATEGORY_LENGTH)
    {
        clearScreen();
        cout << "=============================================================\n";
        cout << "=====ERROR: Category Can't have more than 20 characters======\n";
        cout << "=============================================================\n";
        cout << "Enter the category (food, drink, etc...): ";
        validateStringInput(category);
    }
}

// Harrys Santiago Santana
void validatePrice(double &price)
{
    while (price < MIN_PRICE)
    {
        clearScreen();
        cout << "\n===========================================\n";
        cout << "=====ERROR: Price Can't be Less than 0=====\n";
        cout << "===========================================\n";
        cout << "Enter the Price of the Product: ";
        validateInput(price);
    }
}

// Harrys Santiago Santana
void validateStock(double &stock)
{
    while (stock < MIN_STOCK)
    {
        clearScreen();
        cout << "\n===========================================\n";
        cout << "=====ERROR: Stock Can't be Less than 0=====\n";
        cout << "===========================================\n";
        cout << "Enter the Amount in Stock: ";
        validateInput(stock);
    }
}

// Harrys Santiago Santana
void validateUnitLength(string &unit)
{
    while (unit.length() > MAX_UNIT_LENGTH)
    {
        clearScreen();
        cout << "\n=========================================================\n";
        cout << "=====ERROR: Units Can't have more than 5 characters======\n";
        cout << "=========================================================\n";
        cout << "Enter Unit  of measurement (units, lbs, kg, etc...): ";
        validateStringInput(unit);
    }
}

// Keven Paulino Ferrer & Harrys Santiago Santana
void readFile(vector<Product> &UserProduct)
{
    std::ifstream inFile;
    inFile.open("products.txt");

    if (inFile.is_open())
    {
        Product readFile;
        inFile >> std::ws; // moves to nearest non whitespace in the file
        while (inFile >> readFile.idNum)
        {
            inFile.ignore();
            std::getline(inFile, readFile.name);
            std::getline(inFile, readFile.category);
            inFile >>
                readFile.unit >>
                readFile.price >>
                readFile.stock;
            UserProduct.push_back(readFile);
        }
        inFile.close();
    }
    else
    {
        cout << "\n==================================================\n"
             << "======ERROR: Failed to open file for reading======\n"
             << "==================================================\n";
    }
}

// Keven Paulino Ferrer
void writeFile(const vector<Product> &UserProduct)
{
    std::ofstream Outfile;
    Outfile.open("products.txt");

    if (Outfile.is_open())
    {
        for (Product Print : UserProduct)
        {
            Outfile << '\n'
                    << Print.idNum << '\n'
                    << Print.name << '\n'
                    << Print.category << '\n'
                    << Print.unit << '\n'
                    << Print.price << '\n'
                    << Print.stock << '\n';
        }
        Outfile.close();
    }
    else
    {
        cout << "\n==================================================\n";
        cout << "======ERROR: Failed to open file for writing======\n";
        cout << "==================================================\n";
    }
}

// Harrys Santiago Santana
void showFullInventory(const vector<Product> &userProducts)
{
    cout << "\n"
         << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
         << "| " << std::setw(20) << "Name"
         << "| " << std::setw(20) << "Category"
         << "| " << std::setw(15) << "Stock"
         << "| " << std::setw(15) << "Units"
         << "| " << std::setw(15) << "Price"
         << std::endl;

    cout << "===============================================================================================\n"; // Second row of inventory (Divider Line)

    for (const auto &product : userProducts) // Third row of inventory (All Products)
    {
        cout << "| " << std::setw(6) << product.idNum
             << "| " << std::setw(20) << product.name
             << "| " << std::setw(20) << product.category
             << "| " << std::setw(15) << product.stock
             << "| " << std::setw(15) << product.unit
             << "| " << std::setw(0) << "$"
             << std::setw(15) << std::fixed << std::setprecision(2) << product.price
             << std::endl;
    }
    cout << "===============================================================================================\n"; // Fourth row of inventory (End Line)
}

void showProductHeader()
{
    cout << "\n"
         << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
         << "| " << std::setw(20) << "Name"
         << "| " << std::setw(20) << "Category"
         << "| " << std::setw(15) << "Stock"
         << "| " << std::setw(15) << "Units"
         << "| " << std::setw(15) << "Price"
         << std::endl;

    cout << "===============================================================================================\n"; // Second row of inventory (Divider Line)
}

// Keven Paulino Ferrer
void addProduct(vector<Product> &userProducts)
{
    Product newProduct;
    char continuar;

    do
    {
        clearScreen();
        cout << "\n===========================================\n"
             << "========Inventory Management System========\n"
             << "=================Add Product===============\n";

        do
        {
            cout << "\nEnter Identification Number (----): ";
            std::getline(cin, newProduct.idNum);
            validateIdLength(newProduct.idNum);

            // Harrys Santiago Santana
            auto it = std::find_if(userProducts.begin(), userProducts.end(), [&newProduct](const Product &userProduct)
                                   { return userProduct.idNum == newProduct.idNum; });

            if (it != userProducts.end())
            {
                clearScreen();
                cout << "\n================================================\n"
                     << "=======ERROR: ID " << it->idNum << " Its already in Use========\n"
                     << "================================================\n";
                newProduct.idNum = "";
            }
        } while (newProduct.idNum.length() != ID_LENGTH);

        cout << "Enter Name of the Product: ";
        validateStringInput(newProduct.name);
        validateNameLength(newProduct.name);

        cout << "Enter the category (food, drink, etc...): ";
        validateStringInput(newProduct.category);
        validateCategoryLength(newProduct.category);

        cout << "Enter the Price of the Product:";
        validateInput(newProduct.price);
        validatePrice(newProduct.price);
        cin.ignore();

        cout << "Enter the Amount in Stock:";
        validateInput(newProduct.stock);
        validateStock(newProduct.stock);
        cin.ignore();

        cout << "Enter Unit  of measurement (units, lbs, kg, etc...): ";
        validateStringInput(newProduct.unit);
        validateUnitLength(newProduct.unit);

        userProducts.push_back(newProduct);
        clearScreen();

        cout << "Product [" << newProduct.idNum << "] successfully added.\n";

        showProductHeader();
        cout << "| " << std::setw(6) << newProduct.idNum
             << "| " << std::setw(20) << newProduct.name
             << "| " << std::setw(20) << newProduct.category
             << "| " << std::setw(15) << newProduct.stock
             << "| " << std::setw(15) << newProduct.unit
             << "| " << std::setw(0) << "$"
             << std::setw(15) << std::fixed << std::setprecision(2) << newProduct.price
             << "\n\n";

        cout << "Do You Wish to Continue Adding Products (Y/N): ";
        validateInput(continuar);
        continuar = toupper(continuar);
        if (continuar == 'N')
        {
            clearScreen();
            break;
        }
    } while (continuar == 'Y');
}

// Harrys Santiago Santana
void updateProduct(vector<Product> &userProducts)
{
    // Create a variable to search if 'id' is = to 'idNum' on userProducts
    string id;
    int userChoice;

    auto PrintHeader = []()
    {
        cout << "\n===========================================\n"
             << "========Inventory Management System========\n"
             << "==============Updating Product=============\n";
    };

    clearScreen();
    PrintHeader();
    cout << "\nEnter Product ID to update: ";
    validateStringInput(id);
    validateIdLength(id);

    // Search the product in vector 'userProduct' by ID
    auto it = find_if(userProducts.begin(), userProducts.end(), [&id](const Product &userProduct)
                      { return userProduct.idNum == id; });

    // If product is found, proceed to update its details
    if (it != userProducts.end())
    {
        int menuChoice;
        string newName;
        string newCategory;
        string newUnit;
        double newStock;
        double newPrice;

        do
        {
            // Show current product details
            clearScreen();
            cout << "\n===========================================\n"
                 << "========Inventory Management System========\n"
                 << "==============Updating Product=============\n"
                 << "\nCurrent Product Details: \n";
            auto showProductDetails = [](auto it)
            {
                showProductHeader();

                cout << "| " << std::setw(6) << it->idNum
                     << "| " << std::setw(20) << it->name
                     << "| " << std::setw(20) << it->category
                     << "| " << std::setw(15) << it->stock
                     << "| " << std::setw(15) << it->unit
                     << "| " << std::setw(0) << "$"
                     << std::setw(15) << std::fixed << std::setprecision(2) << it->price
                     << "\n\n";
            };

            showProductDetails(it);
            cout << "What would you like to update?\n\n"
                 << "1. Name\n"
                 << "2. Category\n"
                 << "3. Stock\n"
                 << "4. Unit\n"
                 << "5. Price\n"
                 << "6. Exit\n\n"
                 << "Enter your choice: ";
            validateInput(menuChoice);
            cin.ignore();
            clearScreen();
            if (menuChoice > 0 && menuChoice < 6)
            {
                PrintHeader();
                showProductDetails(it);
            }

            switch (menuChoice)
            {
            case 1:
                cout << "Enter new name: ";
                validateStringInput(newName);
                validateNameLength(newName);
                it->name = newName;
                break;
            case 2:
                cout << "Enter new category: ";
                validateStringInput(newCategory);
                validateCategoryLength(newCategory);
                it->category = newCategory;
                break;
            case 3:
                cout << "Enter new stock: ";
                validateInput(newStock);
                validateStock(newStock);
                cin.ignore();
                it->stock = newStock;
                break;
            case 4:
                cout << "Enter new unit: ";
                validateStringInput(newUnit);
                validateUnitLength(newUnit);
                it->unit = newUnit;
                break;
            case 5:
                cout << "Enter new price: ";
                validateInput(newPrice);
                validatePrice(newPrice);
                cin.ignore();
                it->price = newPrice;
                break;
            case 6:
                cout << "Exiting update menu...\n";
                cout << "Product [" << it->idNum << "] successfully updated.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (menuChoice != 6);
    }
    else
    {
        clearScreen();
        cout << "\n=========================================\n"
             << "=========ERROR: ID not found=============\n"
             << "=========================================\n";
    }
}

// Miguel Monsalve Valencia && Optimized_by @Harrys Santiago Santana
void deleteProduct(vector<Product> &userProducts, bool inventoryEmpty = false)
{
    int answer;
    int sizeId;
    char back, clearInv;
    bool found = false;
    Product itemId, itemName;

    do
    {
        clearScreen();
        auto printHeader = []()
        {
            cout << "\n===========================================\n"
                 << "========Inventory Management System========\n"
                 << "==============Deleting Product=============\n\n";
        };
        do
        {
            printHeader();
            cout
                << "1. Delete product\n"
                   "2. Clear Inventory\n"
                   "3. Exit \n\n"
                   "Enter Your Choice: ";

            validateInput(answer);
            cin.ignore();

            if (answer < 1 || answer > 3) // if user enter a invalid option
            {
                cout << "\n=============================================================\n"
                     << "======ERROR: Invalid choice. Please select 1, 2, or 3.======\n"
                     << "============================================================\n";
                break;
            }

        } while (answer < 1 || answer > 3);

        switch (answer)
        {
        case 1: // delete product by id
            clearScreen();
            printHeader();
            cout << "Enter the ID of the product to delete: ";

            validateStringInput(itemId.idNum);
            validateIdLength(itemId.idNum);

            for (auto i = 0; i < userProducts.size(); ++i) //  loop to access index
            {

                if (itemId.idNum == userProducts[i].idNum) // end loop if found item
                {
                    // Harrys Santiago Santana
                    found = true;

                    clearScreen();
                    printHeader();

                    cout << "Product [" << userProducts.at(i).idNum << "] will be deleted:\n";

                    showProductHeader();

                    cout << "| " << std::setw(6) << userProducts.at(i).idNum
                         << "| " << std::setw(20) << userProducts.at(i).name
                         << "| " << std::setw(20) << userProducts.at(i).category
                         << "| " << std::setw(15) << userProducts.at(i).stock
                         << "| " << std::setw(15) << userProducts.at(i).unit
                         << "| " << std::setw(0) << "$"
                         << std::setw(15) << std::fixed << std::setprecision(2) << userProducts.at(i).price
                         << "\n\n";

                    // Miguel Monsalve Valencia
                    char confirm;
                    cout << "You sure to delete it? [Y/N]: ";
                    cin >> confirm;
                    confirm = toupper(confirm);
                    cin.ignore(1000, '\n');

                    if (confirm == 'Y')
                    {
                        userProducts.erase(userProducts.begin() + i); // remove the product

                        clearScreen();
                        cout << "\n===========================================\n"
                             << "======== Product Successfully Deleted =====\n"
                             << "===========================================\n";
                    }
                    else if (confirm == 'N')
                    {
                        clearScreen();
                        cout << "\n===========================================\n"
                             << "============ Deletion Cancelled ===========\n"
                             << "===========================================\n";
                        break;
                    }
                    else
                    {
                        cout << "ERROR: Invalid input. Please try again.\n";
                        break;
                    }
                }
            }

            if (!found) //
            {
                cout << "\n=========================================\n"
                     << "===========ERROR: ID not found===========\n"
                     << "=========================================\n";
                break;
            }
            return;
        case 2: // delete all inventory
            clearScreen();
            cout << "\nWARNING: YOU ARE ABOUT TO DELETE ALL INVENTORY.\n";
            showFullInventory(userProducts);
            cout << "\nAre you sure to delete all? [Y/N]: ";
            cin >> clearInv;
            clearInv = toupper(clearInv);
            cin.ignore(1000, '\n');
            if (clearInv == 'Y')
            {
                clearScreen();
                userProducts.clear();
                cout << "\n===========================================\n"
                     << "======== Inventory Successfully Cleared ===\n"
                     << "===========================================\n";
                return;
            }
            else if (clearInv == 'N')
            {
                cout << "\n===========================================\n"
                     << "========== Clearing Cancelled =============\n"
                     << "===========================================\n";
                break;
            }
            else
            {
                clearScreen();
                cout << "ERROR: Invalid input. Please try again.\n";
                break;
            }
        case 3:
            clearScreen();
            cout << "\nExiting delete menu...\n";
            break;
        }
    } while (answer != 3); // Exit the delete menu
}

// Keven Paulino Ferrer
void searchBy_Category_Name_id(const vector<Product> &userProducts, vector<Product> &searchProduct, int searchChoice)
{

    auto printHeader = []()
    {
        cout << "==============================================\n"
             << "=========Inventory Management System==========\n"
             << "================Search Products===============\n";
    };

    if (searchChoice == 1) // if it was by Id
    {
        // Harrys Santiago Santana
        string id;
        printHeader();
        cout << "\nEnter Product ID to search: ";
        std::getline(cin, id);
        validateIdLength(id);

        // Iteration through userProducts to find products that match 'ID'
        auto it = find_if(userProducts.begin(), userProducts.end(), [&id](const Product &matchedProduct)
                          { return matchedProduct.idNum == id; });

        if (it != userProducts.end()) // If found
        {
            // Harrys Santiago Santana

            clearScreen();

            cout << "Product [" << it->idNum << "] Details:\n";

            showProductHeader();

            cout << "\n"
                 << "| " << std::setw(6) << it->idNum
                 << "| " << std::setw(20) << it->name
                 << "| " << std::setw(20) << it->category
                 << "| " << std::setw(15) << it->stock
                 << "| " << std::setw(15) << it->unit
                 << "| " << std::setw(0) << "$"
                 << std::setw(15) << std::fixed << std::setprecision(2) << it->price
                 << std::endl;

            cout << "======================================================================================================\n";
        }
        else
        {
            cout << "\n=======================================\n"
                 << "======ERROR: ID Couldn't be Found======\n"
                 << "=======================================\n";
        }
    } // Keven Paulino Ferrer
    else if (searchChoice == 2) // if search by category
    {
        string userCategory;
        printHeader();
        cout << "\nEnter the category to search: ";
        validateStringInput(userCategory);

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
            cout << "\n=============================================\n"
                 << "======ERROR: Category Couldn't be Found======\n"
                 << "=============================================\n";
        }
    }
    else if (searchChoice == 3) // if search by Name
    {
        string userName;
        printHeader();
        cout << "\nEnter the name to search: ";
        validateStringInput(userName);

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
            cout << "\n=========================================\n"
                 << "======ERROR: Name Couldn't be Found======\n"
                 << "=========================================\n";
        }
    }
    if (searchChoice == 2 || searchChoice == 3)
    {
        clearScreen();
        printHeader();
        cout << "\nSearch Results: \n";
        if (!searchProduct.empty())
        {
            showFullInventory(searchProduct);
        }
        searchProduct.clear(); // clears vector just in case
    }
}

// Keven Paulino Ferrer
void searchProduct(const vector<Product> &userProducts)
{
    vector<Product> searchProduct;
    int searchChoice;
    do
    {
        clearScreen();
        cout << "\n============================================\n"
             << "========Inventory Management System=========\n"
             << "================Search Menu=================\n"
             << "\n1. Search by ID \n"
             << "2. Search by category \n"
             << "3. Search by Name \n"
             << "4. Exit \n\n"
             << "Enter your choice: ";
        validateInput(searchChoice);
        cin.ignore();

    } while (searchChoice < 1 || searchChoice > 4);

    if (searchChoice != 4)
    {
        clearScreen();
        searchBy_Category_Name_id(userProducts, searchProduct, searchChoice);
    }
    else if (searchChoice == 4)
    {
        clearScreen();
        cout << "Exiting search menu...\n";
    }
}

int main()
{
    int menuChoice;
    bool inventoryEmpty = false;
    vector<Product> userProducts;
    std::ofstream Myfile("products.txt", std::ios::app); // to create the file ( std::ios::app  = to not overwrite)
    Myfile.close();
    readFile(userProducts);
    do
    {
        cout << "\n============================================\n"
             << "========Inventory Management System=========\n"
             << "===============Inventory Menu===============\n"
             << "1. Add a new product\n"
             << "2. Delete a product\n"
             << "3. Update a product\n"
             << "4. Search for a product\n"
             << "5. Print inventory\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        validateInput(menuChoice);
        cin.ignore();

        switch (menuChoice)
        {
        case 1:
            addProduct(userProducts);
            break;
        case 2:

            if (userProducts.empty())
            {
                inventoryEmpty = true;
                break;
            }
            else
            {
                deleteProduct(userProducts);
                inventoryEmpty = false;
                break;
            }
        case 3:
            if (!userProducts.empty())
            {
                updateProduct(userProducts);
            }
            break;
        case 4:
            if (!userProducts.empty())
            {
                searchProduct(userProducts);
            }
            break;
        case 5:
            if (!userProducts.empty())
            {
                clearScreen();
                cout << "===========================================\n"
                     << "========Inventory Management System========\n"
                     << "=================All Products==============\n";
                showFullInventory(userProducts);
            }
            break;
        case 6:
            clearScreen();
            cout << "Exiting program...\n";
            break;
        default:
            clearScreen();
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        if (menuChoice < 6 && menuChoice > 0 && menuChoice != 2)
        {
            inventoryEmpty = true;
        }
        if (userProducts.empty() && inventoryEmpty == true)
        {
            cout << "\n============================================\n"
                 << "============Error: No Products==============\n"
                 << "============================================\n";
        }
        writeFile(userProducts);
    } while (menuChoice != 6);
    return 0;
}