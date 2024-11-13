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

// Harrys Santiago Santana
void validateInput(double &input)
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

void validateInput(int &input) // so that the input can be int
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

// Keven Paulino Ferrer
void readFile(vector<Product> &UserProduct)
{
    std::ifstream inFile;
    inFile.open("Products.txt");

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
        cout << "\n===========================================\n"
             << "======Failed to open file for reading======\n"
             << "===========================================\n";
    }
}

// Keven Paulino Ferrer
void writeFile(vector<Product> &UserProduct)
{
    std::ofstream Outfile;
    Outfile.open("Products.txt");

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
        cout << "\n===========================================\n";
        cout << "======Failed to open file for writing======\n";
        cout << "===========================================\n";
    }
}

// Keven Paulino Ferrer
void addProduct(vector<Product> &userProducts)
{
    Product newProduct;
    char continuar;

    const int MAX_NAME_LENGTH = 20;

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

            if (newProduct.idNum.length() != 4)
            {
                cout << "\n===========================================================\n"
                     << "=====ERROR: ID Can't be more or less than 4 characters=====\n"
                     << "===========================================================\n";
            }

        } while (newProduct.idNum.length() != 4);

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
        //////////////////////////----------New---------/////////////////////////////
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

        //////////////////////////----------New---------/////////////////////////////
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

    cout << "\n===========================================\n"
         << "========Inventory Management System========\n"
         << "==============Updating Product=============\n"
         << "Enter Product ID to update: ";
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
        //////////////////////////----------New---------/////////////////////////////
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
        } //////////////////////////----------New---------/////////////////////////////
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
    cout << std::left << "| " << std::setw(6) << "ID" // First row of inventory (Header)
         << "| " << std::setw(20) << "Name"
         << "| " << std::setw(20) << "Category"
         << "| " << std::setw(15) << "Stock"
         << "| " << std::setw(15) << "Units"
         << "| " << std::setw(15) << "Price"
         << std::endl;

    cout << "==========================================================================================\n"; // Second row of inventory (Divider Line)

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
            cout << std::left << "| " << std::setw(6) << "ID"
                 << "| " << std::setw(20) << "Name"
                 << "| " << std::setw(15) << "Category"
                 << "| " << std::setw(15) << "Stock"
                 << "| " << std::setw(15) << "Price"
                 << std::endl;

            cout << "=================================================================================================\n";

            cout << "| " << std::setw(6) << it->idNum
                 << "| " << std::setw(20) << it->name
                 << "| " << std::setw(15) << it->category
                 << "| " << std::setw(10) << it->stock << std::setw(5) << it->Units
                 << "| " << std::setw(0) << "$"
                 << std::setw(15) << std::fixed << std::setprecision(2) << it->price
                 << std::endl;
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
    vector<Product> userProducts;
    std::ofstream Myfile("Products.txt", std::ios::app); // to create the file ( std::ios::app  = to not overwrite)
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
            if (!userProducts.empty())
            {
                deleteProduct();
            }
            break;
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
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        if (userProducts.empty())
        {
            cout << "\n============================================\n"
                 << "============Error: No Products==============\n"
                 << "============================================\n";
        }
        writeFile(userProducts);
    } while (menuChoice != 6);
    return 0;
}