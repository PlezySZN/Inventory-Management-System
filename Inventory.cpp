#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using std::vector, std::string, std::cout, std::cin, std::endl;

struct Product
{
    string idNum;
    string name;
    string category;
    string Units;
    double price;
    double stock;
};

const int MAX_NAME_LENGTH = 20;
const int ID_LENGTH = 4;

// Harrys Santiago Santana
void validateIdLength(string &id)
{
    while (id.length() != ID_LENGTH)
    {
        cout << "\n=============================================\n";
        cout << "=====ERROR: ID number must have 4 digits=====\n";
        cout << "=============================================\n";
        cout << "Enter Identification Number (----): ";
        std::getline(cin, id);
    }
}

// Harrys Santiago Santana
void validateInput(double &input) // Validate double input
{
    while (true)
    {
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        else
        {
            break;
        }
    }
}

// Harrys Santiago Santana
void validateInput(int &input) // Validate int input
{
    while (true)
    {
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        else
        {
            break;
        }
    }
}

// Harrys Santiago Santana
int getUserChoice(int &input)
{
    cout << "1. Update product \n"
         << "2. Don't make changes.\n\n"
         << "Enter your choice: ";
    cin >> input;
    cin.ignore();
    return input;
}

// Harrys Santiago Santana
void validateStringInput(string &input)
{
    while (true)
    {
        std::getline(cin, input);
        if (input.empty())
        {
            cout << "Invalid input. Please enter a valid string: ";
        }
        else
        {
            break;
        }
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
                readFile.Units >>
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
void writeFile(vector<Product> &UserProduct)
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
                    << Print.Units << '\n'
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

// Keven Paulino Ferrer
void addProduct(vector<Product> &userProducts)
{
    Product newProduct;
    char continuar;

    do
    {
        cout << "\n===========================================\n"
             << "========Inventory Management System========\n"
             << "=================Add Product===============\n";

        do
        {
            cout << "Enter Identification Number (----): ";
            std::getline(cin, newProduct.idNum);

            // Harrys Santiago Santana
            auto it = std::find_if(userProducts.begin(), userProducts.end(), [&newProduct](Product &userProduct)
                                   { return userProduct.idNum == newProduct.idNum; });

            if (it != userProducts.end())
            {
                cout << "\n================================================\n"
                     << "=======ERROR: ID " << it->idNum << " Its already in Use========\n"
                     << "================================================\n\n";
                newProduct.idNum = "";
            }
            else if (newProduct.idNum.length() != ID_LENGTH)
            {
                cout << "\n=============================================\n";
                cout << "=====ERROR: ID number must have 4 digits=====\n";
                cout << "=============================================\n";
            }
        } while (newProduct.idNum.length() != ID_LENGTH);

        cout << "Enter Name of the Product: ";
        validateStringInput(newProduct.name);
        if (newProduct.name.length() > MAX_NAME_LENGTH)
        {
            cout << "\n=========================================================\n"
                 << "=====ERROR: Name Can't have more than 20 characters======\n"
                 << "=========================================================\n";
            continue;
        }

        cout << "Enter the category (food, drink, etc...): ";
        validateStringInput(newProduct.category);

        do
        {
            cout << "Enter the Price of the Product:";

            // Harrys Santiago Santana
            validateInput(newProduct.price);
            cin.ignore();

            // Keven Paulino Ferrer
            if (newProduct.price < 0)
            {
                cout << "\n===========================================\n"
                     << "=====ERROR: Price Can't be Less than 0======\n"
                     << "===========================================\n";
            }
        } while (newProduct.price < 0);

        do
        {
            cout << "Enter the Amount in Stock:";

            // Harrys Santiago Santana
            validateInput(newProduct.stock);
            cin.ignore();

            // Keven Paulino Ferrer
            if (newProduct.stock < 0)
            {
                cout << "\n============================================\n"
                     << "======ERROR: Stock Can't be Less tha 0======\n"
                     << "============================================\n";
            }

        } while (newProduct.stock < 0);
        do
        {
            cout << "Enter Unit  of measurement (units, lbs, kg, etc...): ";
            validateStringInput(newProduct.Units);
            if (newProduct.Units.length() > 5)
            {
                cout << "\n=========================================================\n"
                     << "=====ERROR: Units Can't have more than 5 characters======\n"
                     << "=========================================================\n";
            }

        } while (newProduct.Units.length() > 5);

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

// Harrys Santiago Santana
void updateProduct(vector<Product> &userProducts)
{
    // Create a variable to search if 'id' is = to 'idNum' on userProducts
    string id;
    int userChoice;

    cout << "\n===========================================\n"
         << "========Inventory Management System========\n"
         << "==============Updating Product=============\n"
         << "Enter Product ID to update: ";
    cin >> id;
    validateStringInput(id);
    validateIdLength(id);
    cin.ignore(); // Clean Buffer

    // Search the product in vector 'userProduct' by ID
    auto it = find_if(userProducts.begin(), userProducts.end(), [&id](Product &userProduct)
                      { return userProduct.idNum == id; });

    // If product is found, proceed to update its details
    if (it != userProducts.end())
    {
        string newName;
        string newCategory;
        string newUnits;
        double newStock;
        double newPrice;

        // Show current product details
        cout << "\n===========================================\n"
             << "Current product name: " << it->name << endl
             << "============================================\n";
        getUserChoice(userChoice);

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

        cout << "\n===========================================\n"
             << "Current product category: " << it->category << endl
             << "============================================\n";
        getUserChoice(userChoice);

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

        cout << "\n===========================================\n"
             << "Current price: $" << std::fixed << std::setprecision(2) << it->price << endl
             << "============================================\n\n";
        getUserChoice(userChoice);

        if (userChoice == 1)
        {
            do
            {
                cout << "Enter product stock to update: ";
                validateInput(newPrice);

                if (newPrice < 0)
                {
                    cout << "\n============================================\n"
                         << "======ERROR: Price Can't be Less tha 0======\n"
                         << "============================================\n";
                }

            } while (newPrice < 0);
            it->price = newPrice;
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }

        cout << "\n===========================================\n"
             << "Current stock: " << it->stock << endl
             << "============================================\n\n";
        getUserChoice(userChoice);

        if (userChoice == 1)
        {
            do
            {
                cout << "Enter product stock to update: ";
                validateInput(newStock);
                if (newStock < 0)
                {
                    cout << "\n============================================\n"
                         << "======ERROR: Stock Can't be Less tha 0======\n"
                         << "============================================\n";
                }

            } while (newStock < 0);
            it->stock = newStock;
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }

        cout << "\n===========================================\n"
             << "Current product Measuring Units: " << it->Units << endl
             << "============================================\n";
        getUserChoice(userChoice);

        if (userChoice == 1)
        {
            do
            {
                cout << "Enter product Unit to update (Abbreviation Ex. lbs, kg): ";
                std::getline(cin, newUnits);
                it->Units = newUnits;
                if (it->Units.length() > 5)
                {
                    cout << "\n=========================================================\n"
                         << "=====ERROR: Units Can't have more than 5 characters======\n"
                         << "=========================================================\n";
                }
            } while (it->Units.length() > 5);
        }
        else if (userChoice == 2)
        {
            cout << "No changes made." << endl;
        }
    }
    else
    {
        cout << "\n=======================================\n"
             << "=========ERROR: ID not found=========\n"
             << "=========================================\n";
    }
}

// Harrys Santiago Santana
void printInventory(vector<Product> &userProducts)
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

    for (auto &product : userProducts) // Third row of inventory (All Products)
    {
        cout << "| " << std::setw(6) << product.idNum
             << "| " << std::setw(20) << product.name
             << "| " << std::setw(20) << product.category
             << "| " << std::setw(15) << product.stock
             << "| " << std::setw(15) << product.Units
             << "| " << std::setw(0) << "$"
             << std::setw(15) << std::fixed << std::setprecision(2) << product.price
             << std::endl;
    }
    cout << "===============================================================================================\n"; // Fourth row of inventory (End Line)
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
        cout << "\n===========================================\n"
             << "========Inventory Management System========\n"
             << "==============Deleting Product=============\n";
        do
        {
            cout << "1- Delete product\n"
                    "2- Clear Inventory\n"
                    "3- Exit \n"
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
            cout << "Enter the ID of the product to delete: ";

            validateStringInput(itemId.idNum);
            validateIdLength(itemId.idNum);

            for (auto i = 0; i < userProducts.size(); ++i) //  loop to access index
            {

                if (itemId.idNum == userProducts[i].idNum) // end loop if found item
                {
                    // Harrys Santiago Santana
                    found = true;

                    cout << "\n===========================================\n"
                         << "========Inventory Management System========\n"
                         << "==============Deleting Product=============\n\n"
                         << "The following product will be deleted:\n";

                    cout << "\n"
                         << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
                         << "| " << std::setw(20) << "Name"
                         << "| " << std::setw(20) << "Category"
                         << "| " << std::setw(15) << "Stock"
                         << "| " << std::setw(15) << "Units"
                         << "| " << std::setw(15) << "Price"
                         << std::endl;

                    cout << "===============================================================================================\n"; // Second row of inventory (Divider Line)

                    cout << "| " << std::setw(6) << userProducts.at(i).idNum
                         << "| " << std::setw(20) << userProducts.at(i).name
                         << "| " << std::setw(20) << userProducts.at(i).category
                         << "| " << std::setw(15) << userProducts.at(i).stock
                         << "| " << std::setw(15) << userProducts.at(i).Units
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
                        cout << "Product successfully deleted." << endl;
                    }
                    else if (clearInv == 'N')
                    {
                        cout << "Deletion cancelled." << endl;
                        break;
                    }
                    else
                    {
                        cout << "ERROR: Invalid input. Please try again.\n";
                        break;
                    }
                }
            }

            if (found == false) //
            {
                cout << "\n=========================================\n"
                     << "===========ERROR: ID not found===========\n"
                     << "=========================================\n";
                break;
            }
            return;
        case 2: // delete all inventory
            cout << "\nWARNING: YOU ARE ABOUT TO DELETE ALL INVENTORY.\n";
            printInventory(userProducts);
            cout << "\nAre you sure to delete all? [Y/N]: ";
            cin >> clearInv;
            clearInv = toupper(clearInv);
            cin.ignore(1000, '\n');
            if (clearInv == 'Y')
            {
                userProducts.clear();
                cout << "Inventory successfully cleared." << endl;
            }
            else if (clearInv == 'N')
            {
                cout << "Clearing inventory cancelled." << endl;
                break;
            }
            else
            {
                cout << "ERROR: Invalid input. Please try again.\n";
                break;
            }
        case 3:
            cout << "\nExiting delete menu...\n";
            break;
        }

    } while (answer != 3); // Exit the delete menu
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
            cout << "\n"
                 << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
                 << "| " << std::setw(20) << "Name"
                 << "| " << std::setw(20) << "Category"
                 << "| " << std::setw(15) << "Stock"
                 << "| " << std::setw(15) << "Units"
                 << "| " << std::setw(15) << "Price"
                 << std::endl;

            cout << "======================================================================================================\n";

            cout << "| " << std::setw(6) << it->idNum
                 << "| " << std::setw(20) << it->name
                 << "| " << std::setw(20) << it->category
                 << "| " << std::setw(15) << it->stock
                 << "| " << std::setw(15) << it->Units
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
            cout << "\n=============================================\n"
                 << "======ERROR: Category Couldn't be Found======\n"
                 << "=============================================\n";
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
            cout << "\n=========================================\n"
                 << "======ERROR: Name Couldn't be Found======\n"
                 << "=========================================\n";
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
        cout << "\n============================================\n"
             << "========Inventory Management System=========\n"
             << "================Search Menu=================\n"
             << "1. Search by ID \n"
             << "2. Search by category \n"
             << "3. Search by Name \n"
             << "4.Return \n"
             << "Enter your choice: ";
        validateInput(searchChoice);
        cin.ignore();

    } while (searchChoice < 1 || searchChoice > 4);

    if (searchChoice != 4)
    {
        searchBy_Category_Name_id(userProducts, searchProduct, searchChoice);
    }

    if (searchChoice == 2 || searchChoice == 3)
    {
        if (!searchProduct.empty())
        {
            // Harrys Santiago Santana
            cout << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
                 << "| " << std::setw(20) << "Name"
                 << "| " << std::setw(20) << "Category"
                 << "| " << std::setw(15) << "Stock"
                 << "| " << std::setw(15) << "Units"
                 << "| " << std::setw(15) << "Price"
                 << std::endl;

            cout << "=================================================================================================\n";
            // Keven Paulino Ferrer
            for (Product Search : searchProduct)
            {
                // Harrys Santiago Santana
                cout << "| " << std::setw(6) << Search.idNum
                     << "| " << std::setw(20) << Search.name
                     << "| " << std::setw(20) << Search.category
                     << "| " << std::setw(15) << Search.stock
                     << "| " << std::setw(15) << Search.Units
                     << "| " << std::setw(0) << "$"
                     << std::setw(15) << std::fixed << std::setprecision(2) << Search.price
                     << std::endl;
            }
        }
        searchProduct.clear(); // clears vector just in case
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
    std::cout << R"(
  _____                      _                     __  __                                              _      _____           _                 
 |_   _|                    | |                   |  \/  |                                            | |    / ____|         | |                
   | |  _ ____   _____ _ __ | |_ ___  _ __ _   _  | \  / | __ _ _ __   __ _  __ _ _ __ ___   ___ _ __ | |_  | (___  _   _ ___| |_ ___ _ __ ____
   | | | '_ \ \ / / _ | '_ \| __/ _ \| '__| | | | | |\/| |/ _` | '_ \ / _` |/ _` | '_ ` _ \ / _ | '_ \| __|  \___ \| | | / __| __/ _ | '_ ` _ _|
  _| |_| | | \ V |  __| | | | || (_) | |  | |_| | | |  | | (_| | | | | (_| | (_| | | | | | |  __| | | | |_   ____) | |_| \__ | ||  __| | | | | |
 |_____|_| |_|\_/ \___|_| |_|\__\___/|_|   \__, | |_|  |_|\__,_|_| |_|\__,_|\__, |_| |_| |_|\___|_| |_|\__| |_____/ \__, |___/\__\___|_| |_| |_|
                                            __/ |                            __/ |                                   __/ |                      
                                           |___/                            |___/                                   |___/                       
)";
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
                printInventory(userProducts);
            }
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
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