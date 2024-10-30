#include <iostream> 
#include <iomanip> 
#include <string> 
#include <algorithm> 
#include <vector> 

    using std::vector, std::string, std::cout, std::cin, std::endl;

    struct product{
        string idNum;
        string name;
        string category;
        double price;
        double stock;
    };

    void addProduct() {
    }

    void deleteProduct() {
    }

    void updateProduct() {
    }

    int searchProduct() {
        return 0;
    }

    void printInventory() {
    }


    int main () {
        int menuChoice;
        vector <product> userProduct(1);

        do {    
            cout << "\n===========================================\n";
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

        } while (menuChoice != 6);
        return 0;
    }