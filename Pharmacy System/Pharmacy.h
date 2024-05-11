#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

#define File_PHAR1 "Pharmacy_file1.txt"
#define Delimiter_char '|'
#define Delete_char '*'


class PharmacySystem
{
private:
    int ID;
    char Name[50];
    float Price;
    int Quantity;
    char Category[50];
public:
    void Menu();            // Pharmacy Management System Main Menu
    void AddMedicine();
    void Search();              // Search For Certain Medicine
    bool CheckAvailable();
    void TakeOrder();           // Orders To Be Taken
    void Delete();         // Delete The Medicine
    void Update();              // Modify The Medicine
    void DailySummary();        // Display The Summary List
    void displayMedicineAvail();     // Displays The Set Of Medicine
    void displayMedicineUnavail();

};
void PharmacySystem::Menu() {
    int choice;
    do
    {
        cout << "\n\t    Pharmacy Management System \n";
        cout << "==================================================\n\n";
        cout << "--------------------------------------------------\n";
        cout << "||\t1) Add Medicine in Pharmacy \t\t\t||\n";
        cout << "||\t2) Search For The Medicine  \t\t||\n";
        cout << "||\t3) New Medicine Order \t\t\t||\n";
        cout << "||\t4) Delete a Medicine From The Pharmacy ||\n";
        cout << "||\t5) Update a Medicine From The Pharmacy \t\t\t||\n";
        cout << "||\t6) Daily Summary Of Total Sales \t||\n";
        cout << "||\t7) Display Available Medicine \t\t||\n";
        cout << "||\t8) Display Unavailable Medicine At The Pharmacy \t\t||\n";
        cout << "||\t9. Exit \t\t\t\t||\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            AddMedicine();
            break;
        }

        case 2:
        {
            Search();
            break;
        }

        case 3:
        {
            TakeOrder();
            break;
        }

        case 4:
        {
            Delete();
            break;
        }

        case 5:
        {
            Update();
            break;
        }

        case 6:
        {
            DailySummary();
            break;
        }

        case 7:
        {
            displayMedicineAvail();
            break;
        }

        case 8:
        {
            displayMedicineUnavail();
            break;
        }

        case 9:
        {
            exit(0);
            system("puase");
            break;
        }

        default:
        {
            cout << "You Entered An Invalid Key Input\nKindly, Re-enter The Input! \n"
                << endl;
            break;
        }
        }

    } while (choice != 9);
}

void PharmacySystem::AddMedicine() {
    //input
    //you need to take the data (id, name , price ,quantity,category)  from the user
    // do this steps
    //search by name and category if you find this product, update the quantity in the file
    //else store the data in the file

}

void PharmacySystem::Search() {
    //input name and category
    //output quantity, name and price
}

bool PharmacySystem::CheckAvailable() {
    //input id and category
    //Check Available Mwdicine at Pharmacy
}

void PharmacySystem::TakeOrder() {
    //input name and category
    //do fun SubMenu {delete sub order, add medicine,update,display invoice}
    //do all fun in submenu 
}

void PharmacySystem::Delete() {
    //input name and catergory
    //Delete a Medicine From The Pharmacy
}

void PharmacySystem::Update() {
    //input name and catergory
    //Update a Medicine From The Pharmacy
}

void PharmacySystem::DailySummary() {
    //input Today's date
    //output total price in day
}

void PharmacySystem::displayMedicineAvail() {

}

void PharmacySystem::displayMedicineUnavail() {

}


