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
            cout << "\n============================================\n";
            cout << "========Inventory Management System=========\n";
            cout << "=============Adding New Product=============\n";    
            cout << "Enter Identification Number: ";
            cin>> newProduct.idNum;
            cout << "Enter Name of the Product: ";
            cin>> newProduct.name;
            cout << "Enter the category (foods, drinks, etc...): ";
            cin>> newProduct.category;

            do {
                cout << "Enter the Price of the Product:";
                cin>> newProduct.price;

                if (newProduct.price<0) {
                    cout << "\n===========================================\n";
                    cout << "=====ERROR: Price Can't be Less than 0===== \n";
                    cout << "===========================================\n";
                }
            } while (newProduct.price<0);

            do {
                cout << "Enter the Amount in Stock:";
                cin>> newProduct.stock;
                if (newProduct.stock<0) {
                    cout << "\n============================================\n";
                    cout << "======ERROR: Stock Can't be Less tha 0====== \n";
                    cout << "============================================\n";
                }
            } while (newProduct.stock<0);

            userProducts.push_back(newProduct);  
            
            cout<< "Do You Wish to Continue Adding Products (Y/N)";
            cin >> continuar;
            continuar = toupper(continuar); 
            if (continuar=='N') {
                break;
            } 
        } while (continuar=='Y');     
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
            cout << "3. Search for a product\n";
            cout << "4. Print inventory\n";
            cout << "5. Update a product\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> menuChoice;
            switch (menuChoice){
            case 1:
                addProduct(userProducts);
                break;
            }
            
        } while(menuChoice !=6);
        return 0;
    }