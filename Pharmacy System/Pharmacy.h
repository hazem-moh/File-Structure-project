#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define PHAR "Pharmacy_file.txt"
#define PrimaryFile "Primary_File.txt"
#define Sales "Sales_file.txt"
#define Delimiter_char '|'
#define DeletionMark '*'


class PharmacySystem
{
private:
    int ID;
    char Name[200];
    float Price;
    int Quantity;
    char Category[10];
    int index;
public:
    void Menu();
    void AddMedicine(int id, char* name, char* category, float price, int quantity);
    void Addmenu();
    void Search();
    int CheckAvailable(int id, char* name);
    void TakeOrder();
    void Delete();
    void DeleteIdName(int id, char* N);
    void Update();
    void UpdateQP(int ind,int TQ);
    void DailySummary();       
    void displayTop5Rcord();

};

void PharmacySystem::Menu() {
    int choice;
    do
    {
        cout << "\n\t    Pharmacy System \n";
        cout << "==================================================================\n\n";
        cout << "------------------------------------------------------------------\n";
        cout << "||\t1) Add Medicine in Pharmacy \t\t\t\t||\n";
        cout << "||\t2) Search For The Medicine  \t\t\t\t||\n";
        cout << "||\t3) New Medicine Order \t\t\t\t\t||\n";
        cout << "||\t4) Delete a Medicine From The Pharmacy \t\t\t||\n";
        cout << "||\t5) Update a Medicine From The Pharmacy \t\t\t||\n";
        cout << "||\t6) Daily Summary Of Total Sales \t\t\t||\n";
        cout << "||\t7) Display Top 5 Records \t\t\t\t||\n";
        cout << "||\t8) Exit \t\t\t\t\t\t||\n";
        cout << "------------------------------------------------------------------\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
             case 1:
             {
                 Addmenu();
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
                 displayTop5Rcord();
                 break;
             }

             case 8:
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

    } while (choice != 8);
}



void PharmacySystem::Addmenu() {

    while (1) {
        cout << endl;
        cout << "If you have finished adding, enter -1 in ID.\n";
        cout << "------------------------------------------------------------------\n";

        cout << "Enter Medicine ID: ";
        cin >> ID;

        if (ID == -1)
            break;

        cout << "Enter Medicine Name: ";
        cin.ignore();
        cin.getline(Name, 100);

        cout << "Enter Category: ";
        cin >> Category;

        cout << "Enter Quantity: ";
        cin >> Quantity;

        cout << "Enter Price: ";
        cin >> Price;

        AddMedicine(ID, Name, Category, Price, Quantity);
        cout << "------------------------------------------------------------------\n";

    }

    
}

void PharmacySystem::AddMedicine(int id, char* name, char* category, float price, int quantity) {
    
    ofstream prim(PrimaryFile, ios::binary | ios::app);
    ofstream MedFile(PHAR, ios::binary | ios::app);
    int ind = CheckAvailable(ID, Name);
    if (!MedFile.is_open()) {
        cout << "File not found\n";
        exit(0);
    }
    //else if (ind != -1) {
    //    UpdateQP(ind,Quantity);//Update Quantity and Price
    //}    
    else {
        if (true) {
            MedFile.seekp(0, ios::end);
            index = MedFile.tellp();
        }
              
        MedFile.write((char*)&id, sizeof(int)); //Id

        int length = strlen(name);
        MedFile.write((char*)&length, sizeof(int)); //Name
        MedFile.write(name, length);

        length = strlen(category);
        MedFile.write((char*)&length, sizeof(int));//Category
        MedFile.write(category, length);

        MedFile.write((char*)&price, sizeof(float));//Price

        MedFile.write((char*)&quantity, sizeof(int));//Quantity

        MedFile.put(Delimiter_char);

        //wite in primary file and Secondary file
        //primary file
        prim.write((char*)&id, sizeof(int)); //id
        prim.write((char*)&index, sizeof(int)); //index

        prim.put(Delimiter_char);
      
        MedFile.close();
        prim.close();
            
    }
       

    
}

void PharmacySystem::Search() {
    char N[100];
    int id;

    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Medicine Name: ";
    cin.ignore();
    cin.getline(N, 100);

    index = CheckAvailable(id, N);
    if (index == -1) {
        cout << "This medication is not available." << endl;
        return;
    }
    else {
        ifstream pri(PHAR, ios::binary);
        pri.seekg(index, ios::beg);

        pri.read((char*)&ID, sizeof(int));

        int length;
        pri.read((char*)&length, sizeof(int));
        pri.read(Name, length);
        Name[length] = '\0';

        pri.read((char*)&length, sizeof(int));
        pri.read(Category, length);
        Category[length] = '\0';

        pri.read((char*)&Price, sizeof(float));

        pri.read((char*)&Quantity, sizeof(int));

        pri.close();
        cout << "  || ID: " << ID << '\t' << "Name: " << '\t' << Name << '\t' << "Category: " << Category << '\t' << "Price: " << Price << '\t' << "Quantity: " << Quantity << endl;
    }

}


int PharmacySystem::CheckAvailable(int id,char* name) {
    vector<pair<int, int>> file;
    ifstream find(PrimaryFile, ios::binary);
    if (!find.is_open()) {
        cout << "File not found\n";
        exit(0);
    }
    else {
        while (1){
            
            if (find.peek() == DeletionMark) {
                char c;
                while (find >> c)
                {
                    if (c == Delimiter_char)
                        break;
                }
            }

            find.read((char*)&ID, sizeof(int));

            find.read((char*)&index, sizeof(int));

            char d;
            find.get(d);
            if (find.eof())
                break;
            file.push_back(make_pair(ID, index));
        }
        sort(file.begin(), file.end());
        int left = 0;
        int right = file.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (file[mid].first == id) {
                ifstream check(PHAR, ios::binary);
                check.seekg(file[mid].second, ios::beg);

                check.read((char*)&ID, sizeof(int));
                int length;
                check.read((char*)&length, sizeof(int));
                check.read(Name, length);
                Name[length] = '\0';
                check.close();
                
                

                if (strcmp(name, Name) == 0) {
                    find.close();
                    
                    return file[mid].second;
                }
                else {
                    find.close();
                    return -1;
                }

                
            }
            
            else if (file[mid].first < id) 
                left = mid + 1; 
            
            else 
                right = mid - 1;
            
        }
        find.close();
        return -1;
        
    }
}

void PharmacySystem::TakeOrder() { 
    int choice;
    vector <char*>orderlist1, orderlist2;
    vector <int>quat;
    vector <float>price;
    char name[100];
    int id;
    int quantity;
    double TotalPrice = 0;


    do
    {
        cout << endl;
        cout << "==================================================================" << endl;
        cout << "\t List Of Orders :\n";
        cout << "==================================================================" << endl;
        cout << "------------------------------------------------------------------\n";
        cout << "||\t1) Add Medicine To Order \t\t\t\t||\n";
        cout << "||\t2) Delete a Medicine From The Order \t\t\t||\n";
        cout << "||\t3) Update The Quantity Of Medication In An Order \t||\n";
        cout << "||\t4) Print The Invoice \t\t\t\t\t||\n";
        cout << "||\t5. Exit and don't save this order \t\t\t||\n";
        cout << "------------------------------------------------------------------\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter Medicine Name: ";
            cin.ignore();
            cin.getline(name, 100);

            cout << "Enter a Quantity: ";
            cin >> quantity;

            int ind = CheckAvailable(id, name);

            if (ind == -1) {
                cout << "This medication is not available." << endl;
                continue;
            }
            ifstream check(PHAR, ios::binary);
            check.seekg(ind, ios::beg);

            check.read((char*)&ID, sizeof(int));

            int length;
            check.read((char*)&length, sizeof(int));
            check.read(Name, length);
            Name[length] = '\0';

            check.read((char*)&length, sizeof(int));
            check.read(Category, length);
            Category[length] = '\0';

            check.read((char*)&Price, sizeof(float));

            check.read((char*)&Quantity, sizeof(int));

            check.close();

            price.push_back(Price * quantity);
            orderlist1.push_back(Name);
            quat.push_back(quantity);
            orderlist2.push_back(Category);

        }
        else if (choice == 2) {
            cout << "Chose the oder to delete" << endl;
            for (int i = 0; i < orderlist1.size(); i++) {
                cout << '\t' << i + 1 << ") " << "Medicine Name: " << orderlist1[i] << '\t' << "Category: " << orderlist2[i] << endl;
            }
            int choi;
            cout << "Enter Your Choice: ";
            cin >> choi;
            orderlist1.erase(orderlist1.begin() + choi - 1);
            orderlist2.erase(orderlist2.begin() + choi - 1);
            quat.erase(quat.begin() + choi - 1);
            price.erase(price.begin() + choi - 1);

        }
        else if (choice == 3) {
            cout << "Chose the oder to Update" << endl;
            for (int i = 0; i < orderlist1.size(); i++) {
                cout << '\t' << i + 1 << ") " << "Medicine Name: " << orderlist1[i] << '\t' << "Category: " << orderlist2[i] << endl;
            }
            int choi;
            cout << "Enter Your Choice: ";
            cin >> choi;
            
            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter Medicine Name: ";
            cin.ignore();
            cin.getline(name, 100);

            cout << "Enter a Quantity: ";
            cin >> quantity;
            
            int ind = CheckAvailable(id, name);
            if (ind == -1) {
                cout << "This medication is not available." << endl;
                orderlist1.erase(orderlist1.begin() + choi - 1);
                orderlist2.erase(orderlist2.begin() + choi - 1);
                quat.erase(quat.begin() + choi - 1);
                price.erase(price.begin() + choi - 1);
                continue;
            }
            ifstream check(PHAR, ios::binary);
            check.seekg(ind, ios::beg);

            check.read((char*)&ID, sizeof(int));

            int length;
            check.read((char*)&length, sizeof(int));
            check.read(Name, length);
            Name[length] = '\0';

            check.read((char*)&length, sizeof(int));
            check.read(Category, length);
            Category[length] = '\0';

            check.read((char*)&Price, sizeof(float));

            check.read((char*)&Quantity, sizeof(int));

            check.close();

            orderlist1[choi - 1] = Name;
            orderlist2[choi - 1] = Category;
            quat[choi - 1] = quantity;
            price[choi - 1]= Price*quantity; 
        }
        else if (choice == 4) {
            double totalprice = 0;
            ofstream sal(Sales, ios::binary | ios::app);
            if (!sal.is_open()) {
                cout << "File not found\n";
                exit(0);
            }
            else {
                cout << "_____________________________________________________" << endl;
                cout << "=====================================================" << endl;
                cout << "|  Medicine Name            | Quantity  |  Price    |" << endl;
                cout << "=====================================================" << endl;
                for (int i = 0; i < orderlist1.size(); i++)
                {
                        int length = strlen(orderlist1[i]);
                        sal.write((char*)&length, sizeof(int)); 
                        sal.write(orderlist1[i], length);

                        length = strlen(orderlist2[i]);
                        sal.write((char*)&length, sizeof(int));
                        sal.write(orderlist2[i], length);

                        sal.write((char*)&price[i], sizeof(float));

                        sal.write((char*)&quat[i], sizeof(int));

                        sal.put(Delimiter_char);

                        TotalPrice += price[i];

                        cout << "|  " << Name << "\t\t\t" << " | " << Quantity << "\t\t\t" << " | " << Price << "\t\t\t" << endl;

                }
                sal.close();
                cout << "=====================================================" << endl;
                cout << "|  Total Price: " << TotalPrice << "\t\t\t" << endl;
                cout << "=====================================================" << endl;
                return;
            }
        }
        else if (choice == 5) {
            return;
        }
        else {
            cout << "You Entered An Invalid Key Input\nKindly, Re-enter The Input! \n"
                << endl;
        }
        

    } while (choice != 5);

}

void PharmacySystem::Delete() {
    char N[100];
    int id;
    cout << "Enter ID: ";
    cin >> id;

    cout << "Enter Medicine Name: ";
    cin.ignore();
    cin.getline(N, 100);
    DeleteIdName(id, N);
}

void PharmacySystem::DeleteIdName(int id,char*N) {
    
    fstream delet(PHAR, ios::in | ios::out | ios::binary);
    fstream delet2(PrimaryFile, ios::in | ios::out | ios::binary);
      
    int ind = CheckAvailable(id, N);
    if (ind == -1) {
        cout << "This medication is not available." << endl;
        return;
    }
    else {
        delet.seekp(ind, ios::beg);
        delet.put(DeletionMark);
        delet.close();

        while (1) {
            if (delet2.peek() == DeletionMark) {
                char c;
                while (delet2 >> c)
                {
                    if (c == Delimiter_char)
                        break;
                }
            }
            int pos = delet2.tellg();
            delet2.read((char*)&ID, sizeof(int));

            delet2.read((char*)&index, sizeof(int));

            char d;
            delet2.get(d);
            if (ID == id) {
                delet2.seekp(pos, ios::beg);
                delet2.put(DeletionMark);
                break;
            }
            if (delet2.eof())
                break;
            
        }
        
        delet2.close();
    }
}

void PharmacySystem::Update() {
    char N[100];
    int id;
    cout << "Enter ID: ";
    cin >> id;

    cout << "Enter Medicine Name: ";
    cin.ignore();
    cin.getline(N, 100);

    int ind = CheckAvailable(id, N);
    if (ind == -1) {
        cout << "This medication is not available." << endl;
        return;
    }
    DeleteIdName(id, N);
    cout << "------------------------------------------------------------------\n";

    cout << "Enter Medicine ID: ";
    cin >> ID;

    cout << "Enter Medicine Name: ";
    cin.ignore();
    cin.getline(Name, 100);

    cout << "Enter Category: ";
    cin >> Category;

    cout << "Enter Quantity: ";
    cin >> Quantity;

    cout << "Enter Price: ";
    cin >> Price;

    AddMedicine(ID, Name, Category, Price, Quantity);
}

void PharmacySystem::UpdateQP(int ind,int TQ) {
    fstream MedFile(PHAR, ios::in | ios::out | ios::binary);
    if (!MedFile.is_open()) {
        cout << "File not found\n";
        exit(0);
    }
    else {
        int Q;
        float P;
        MedFile.seekg(ind, ios::beg);
        MedFile.read((char*)&ID, sizeof(int));

        int length;
        MedFile.read((char*)&length, sizeof(int));
        MedFile.read(Name, length);
        Name[length] = '\0';

        MedFile.read((char*)&length, sizeof(int));
        MedFile.read(Category, length);
        Category[length] = '\0';

        MedFile.read((char*)&P, sizeof(float));

        MedFile.read((char*)&Q, sizeof(int));

        ////////////

        MedFile.seekp(ind, ios::beg);

        MedFile.write((char*)&ID, sizeof(int)); //Id

        length = strlen(Name);
        MedFile.write((char*)&length, sizeof(int)); //Name
        MedFile.write(Name, length);

        length = strlen(Category);
        MedFile.write((char*)&length, sizeof(int));//Category
        MedFile.write(Category, length);

        MedFile.write((char*)&Price, sizeof(float));//Price

        Q += TQ;
        MedFile.write((char*)&Q, sizeof(int));//Quantity

        MedFile.put(Delimiter_char);
    }
}

void PharmacySystem::DailySummary() {
    double TotalSales = 0;
    ifstream sal(Sales, ios::binary);
    if (!sal.is_open()) {
        cout << "File not found\n";
        exit(0);
    }
    else{
        while (true) {


            sal.read((char*)&ID, sizeof(int));

            int length;
            sal.read((char*)&length, sizeof(int));
            sal.read(Name, length);
            

            length;
            sal.read((char*)&length, sizeof(int));
            sal.read(Category, length);
            

            sal.read((char*)&Price, sizeof(float));

            sal.read((char*)&Quantity, sizeof(int));

            char d;
            sal.get(d);

            if (sal.eof()) {
                break;
            }
            TotalSales += Price;

        }
        sal.close();
        cout << "=====================================================" << endl;
        cout << "|  Total Sales in Day : " << TotalSales <<" $"<<" \t\t\t" << endl;
        cout << "=====================================================" << endl;
    }

    
}

void PharmacySystem::displayTop5Rcord() {

    ifstream pri(PHAR, ios::binary);
    if (!pri.is_open()) {
        cout << "File not found\n";
        exit(0);
    }
    else {
        int cnt = 0;
        cout << "------------------------------------------------------------------\n";
        while (cnt < 5) {
            if (pri.peek() == DeletionMark) {
                char c;
                while (pri >> c)
                {
                    if (c == Delimiter_char)
                        break;
                }
            }

            pri.read((char*)&ID, sizeof(int));

            int length;
            pri.read((char*)&length, sizeof(int));
            pri.read(Name, length);
            Name[length] = '\0';

            pri.read((char*)&length, sizeof(int));
            pri.read(Category, length);
            Category[length] = '\0';

            pri.read((char*)&Price, sizeof(float));

            pri.read((char*)&Quantity, sizeof(int));

            char d;
            pri.get(d);

            if (pri.eof())
                break;
            cnt++;

            cout << "  || ID: " << ID << '\t' << "Name: " << '\t' << Name << '\t' << "Category: " << Category << '\t' << "Price: " << Price << '\t' << "Quantity: " << Quantity << endl;
        }
        cout << "------------------------------------------------------------------\n";

        pri.close();
    }
}

