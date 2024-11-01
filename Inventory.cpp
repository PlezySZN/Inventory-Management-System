#include <iostream> 
#include <iomanip> 
#include <string> 
#include <algorithm> 
#include <vector> 

    using std::vector, std::string, std::cout, std::cin, std::endl;

    struct Product{
        string idNum;
        string name;
        string category;
        double price;
        double stock;
    } ;
    //Keven Paulino Ferrer
    void addProduct(vector <Product> &userProducts) {
        Product newProduct;
        char continuar;
        do{
            cout << "\n===========================================\n";
            cout << "========Inventory Management System========\n";
            cout << "=============Adding New Product=============\n";    

            do {
            cout << "Enter Identification Number (----): ";
            std::getline(cin, newProduct.idNum);

                if (newProduct.idNum.length() > 4) {
                    cout <<"\n===========================================\n";
                    cout << "=====ERROR: ID Can't be more than 9999=====\n";
                    cout <<"===========================================\n";
                    continue;

                    } else if (newProduct.idNum.length() < 4) {
                        cout << "\n============================================\n";
                        cout << "======ERROR: ID Can't be less than 1000====== \n";
                        cout << "============================================\n";
                        continue;
                }

            } while (newProduct.idNum.length() < 4);

            cout << "Enter Name of the Product: ";
            std::getline (cin, newProduct.name);
            cout << "Enter the category (food, drink, etc...): ";
            std::getline (cin, newProduct.category);

            do {
                cout << "Enter the Price of the Product:";
                cin>> newProduct.price;
                
                if (!(cin, newProduct.price)) {
                        cout << "\n===========================================\n";
                        cout << "=====ERROR: Invalid input. Please Enter a number ===== \n";
                        cout << "===========================================\n";

                        cin.clear();
                        cin.ignore();
                        
                        continue;
                    }
                        if (newProduct.price<0) {
                            cout << "\n===========================================\n";
                            cout << "=====ERROR: Price Can't be Less than 0===== \n";
                            cout << "===========================================\n";
                        }
            } while (newProduct.price<0);

            do {
                cout << "Enter the Amount in Stock:";
                cin>> newProduct.stock;

                if (!(cin, newProduct.price)) {
                        cout << "\n===========================================\n";
                        cout << "=====ERROR: Invalid input. Please Enter a number ===== \n";
                        cout << "===========================================\n";

                        cin.clear();
                        cin.ignore();
                        
                        continue;
                    }

                        if (newProduct.stock<0) {
                            cout << "\n============================================\n";
                            cout << "======ERROR: Stock Can't be Less tha 0====== \n";
                            cout << "============================================\n";
                        }

            } while (newProduct.stock<0);

            userProducts.push_back(newProduct);  
            
            cout<< "Do You Wish to Continue Adding Products (Y/N)";
            cin >> continuar;
            cin.ignore();
            continuar = toupper(continuar); 
            if (continuar=='N') {
                break;
            } 
        } while (continuar=='Y');     
    }

    void deleteProduct() {
    }

    //Harrys Santiago Santana
    void updateProduct(vector <Product> &userProducts) {
    string id;

    cout << "\n===========================================\n";
    cout << "========Inventory Management System========\n";
    cout << "==============Updating Product==============\n"; 
    cout << "Enter Product ID to update: ";
    cin >> id;
    cin.ignore();

    auto it = find_if(userProducts.begin(), userProducts.end(),[&id](Product &matchedProduct) {
        return matchedProduct.idNum == id;
    });

    if (it != userProducts.end()) {
        string newName;
        string newCategory;
        double newStock;
        double newPrice;

        cout << "===========================================\n";
        cout << "Current product name: " << it->name << endl;
        cout << "============================================\n\n";
        cout << "Enter product name to update: ";
        std::getline(cin, newName);

        if (!newName.empty()) {
            it->name = newName;
        } else {
            cout << "No changes made." << endl;
        }

        cout << "===========================================\n";
        cout << "Current product category: " << it->category << endl;
        cout << "============================================\n\n";
        cout << "Enter product category to update: ";
        std::getline(cin, newCategory);

        if (!newCategory.empty()) {
            it->category = newCategory;
        } else {
            cout << "No changes made." << endl;
        }

        cout << "===========================================\n";
        cout << "Current price: $" << std::fixed << std::setprecision(2) << it->price << endl;
        cout << "============================================\n\n";
        cout << "Enter price to update: ";
        cin >> newPrice;

        if (newPrice < 0) {
            cout << "\n=======================================\n";
            cout << "=====ERROR: Price Can't be Less 0===== \n";
            cout << "=========================================";
    }

            if (!newPrice < 0) {
                it->price = newPrice;
            }

        cout << "===========================================\n";
        cout << "Current stock: " << it->stock << endl;
        cout << "============================================\n\n";
        cout << "Enter stock to update: ";
        cin >> newStock;
        it->stock = newStock;

        
        if (newStock < 0) {
            cout << "\n=======================================\n";
            cout << "=====ERROR: Stock Can't be Less 0===== \n";
            cout << "=========================================";
    }

            if (!newStock < 0) {
                it->stock = newStock;
            }

    } else {
        cout << "\n=======================================\n";
        cout << "=========ERROR: ID not found=========\n";
        cout << "=========================================\n";
    }

}
    int searchProduct() {
        return 0;
    }

    void printInventory(vector <Product> &userProducts) {

            std::cout << std::left << std::setw(10) << "ID" 
            << std::setw(10) << "Name" 
            << std::setw(15) << "Category" 
            << std::setw(15) << "Stock" 
            << std::setw(15) << "Price" 
            << std::endl;

        for (auto &product : userProducts) {
            
            std::cout << std::setw(10) << product.idNum 
            << std::setw(10) << product.name 
            << std::setw(15) << product.category 
            << std::setw(15) << product.stock 
            << std::setw(0)  << "$" 
            << std::setw(20) << std::fixed << std::setprecision(2) 
            << product.price
            << std::endl;

        }   
    }
    int main () {
        int menuChoice;
        vector <Product> userProducts;
        do {
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
            
            switch (menuChoice){

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
                searchProduct();
                break;
            case 5:
                printInventory(userProducts);
                break;
            }
            
        } while(menuChoice !=6);
        return 0;
    }