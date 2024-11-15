#include "patient.h"

long long Patient::set_id = 2000000;

void Patient::set_data() {
    ID = set_id++;
    Patient::update_info();
    cout << "Patient has ID: " << ID << ", password: " << password << endl;
}

void Patient::update_info() {
    Person::set_data();
    cin.ignore();
    cout << "Enter allergy: ";
    getline(cin, allergy);
    cout << "Enter family phone: ";
    getline(cin, phone_family);
}

void Patient::update_data() {
    int choice;
    do {
        cout << "1. Update Information\n"
             << "2. Update password\n"
             << "3. Exit\n";
        cout << "Choose your option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Patient::update_info();
                cout << "Update successfully" << endl;
                display();
                cout << "\n";
                break;
            }
            case 2: {
                Person::update_password();
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
    } while (choice != 3);
}

void Patient::display() const {
    Person::display_for_out_person();
    cout << ", Password: " << password;
    cout << ", Allergy: " << allergy
         << ", Family Phone: " << phone_family << endl;
}

void Patient::read_a_object_from_file(const string &line) {
    stringstream ss(line);
    string item;

    // Read Patient specific data
    getline(ss, item, ',');
    ID = stoll(item);

    getline(ss, name, ',');
    getline(ss, password, ',');
    getline(ss, birthday, ',');
    getline(ss, gender, ',');
    getline(ss, address, ',');
    getline(ss, email, ',');
    getline(ss, phone, ',');
    getline(ss, item, ',');
    is_deleted = (item == "1");

    getline(ss, allergy, ',');
    getline(ss, phone_family, ',');
}

void Patient::write_a_object_to_file(ofstream &file) {
    if (file.is_open()) {
        file << ID << ","
             << name << ","
             << password << ","
             << birthday << ","
             << gender << ","
             << address << ","
             << email << ","
             << phone << ","
             << (is_deleted ? "1" : "0") << ","
             << allergy << ","
             << phone_family << endl;
    } else {
        cerr << "Error: File is not open." << endl;
    }
}