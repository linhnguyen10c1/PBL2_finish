#include "medicine.h"

long long Medicine::set_id = 4000000;

void Medicine::set_data() {
    id_medicine = set_id++;
    update_info();
    cout << "Enter quantity: ";
    cin >> quantity;
    cin.ignore();
}

void Medicine::display() const {
    cout << "ID: " << id_medicine
         << ", Name: " << name
         << ", Type: " << type
         << ", Usage: " << usage
         << ", Dosage: " << dosage
         << ", Side Effects: " << side_effects
         << ", Warnings: " << warnings
         << ", NSX: " << NSX
         << ", HSD: " << HSD
         << ", Quantity: " << quantity
         << ", Cost: " << cost
         << ", Is Deleted: " << (is_deleted ? "Yes" : "No") << endl;
}

void Medicine::update_info() {
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter type: ";
    getline(cin, type);
    cout << "Enter usage: ";
    getline(cin, usage);
    cout << "Enter dosage: ";
    getline(cin, dosage);
    cout << "Enter side effects: ";
    getline(cin, side_effects);
    cout << "Enter warnings: ";
    getline(cin, warnings);
    cout << "Enter NSX: ";
    getline(cin, NSX);
    cout << "Enter HSD (in months): ";
    cin >> HSD;
    cin.ignore();
    cout << "Enter cost: ";
    cin >> cost;
    cin.ignore();
}

void Medicine::update_data(){
    int choice;
    do{
    cout << "1. Update Information\n"
         << "2. Update Quantity\n" 
         << "3. Exit\n";
    cout << "Choose your option: ";
    cin >> choice;
    cin.ignore();

    switch (choice){
        case 1:{
              update_info();
              cout << "Update successfully" << endl;
              display();
              cout << "\n";
              break;
        }
        case 2:{
              int x;
              cout << "How many new drugs are imported?: ";
              cin >> x;
              cin.ignore();
              update_quantity(x);
              display();
              cout << "\n";
              break;
        }
        case 3: {
              break;
        }

        default: {
              cout << "Invalid choice. Please try again." << endl;
              break;
            }
    }
    } while(choice != 3);
}

void Medicine::update_is_deleted() {
    is_deleted = true;
}

void Medicine::update_is_recovered() {
    is_deleted = false;
}


void Medicine::read_a_object_from_file(const string &line) {
    stringstream ss(line);
    string item;

    getline(ss, item, ',');
    id_medicine = stoll(item);

    getline(ss, name, ',');
    getline(ss, type, ',');
    getline(ss, usage, ',');
    getline(ss, dosage, ',');
    getline(ss, side_effects, ',');
    getline(ss, warnings, ',');
    getline(ss, NSX, ',');

    getline(ss, item, ',');
    HSD = stoi(item);

    getline(ss, item, ',');
    quantity = stoi(item);

    getline(ss, item, ',');
    cost = stod(item);

    getline(ss, item, ',');
    is_deleted = (item == "1");
}

void Medicine::write_a_object_to_file(ofstream &file) {
    if (file.is_open()) {
        file << id_medicine << ","
             << name << ","
             << type << ","
             << usage << ","
             << dosage << ","
             << side_effects << ","
             << warnings << ","
             << NSX << ","
             << HSD << ","
             << quantity << ","
             << cost << ","
             << (is_deleted ? "1" : "0") << endl;
    } else {
        cerr << "Error: File is not open." << endl;
    }
}