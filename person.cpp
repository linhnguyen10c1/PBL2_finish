#include "person.h"

string Person::generate_random_password(int length) {
        const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        random_device rd;  // Seed for the random number engine
        mt19937 generator(rd());  // Mersenne Twister random number engine
        uniform_int_distribution<> distribution(0, characters.size() - 1);

        string password;
        for (int i = 0; i < length; ++i) {
            password += characters[distribution(generator)];
        }

        return password;
    }

void Person::set_data() {
    
    cout << "Enter full name: ";
    getline(cin, name);
    
    cout << "Enter birthday d-m-y: ";
    getline(cin, birthday);

    cout << "Enter gender (Male/Female): ";
    getline(cin, gender);
        
    cout << "Enter address: "; 
    getline(cin, address);
        
    cout << "Enter email: ";
    getline(cin, email);

    cout << "Enter phone (10 digits): ";
    cin >> phone;

    while (phone.length() != 10 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
        cout << "Invalid phone number. Enter again (10 digits): ";
        cin >> phone;
    }
}

void Person::update_password(){
    string mk;
    cout << "Enter password you want change: ";
    cin >> mk;
    password = mk;
}

void Person::update_is_deleted(){
    is_deleted = true;
}
void Person::update_is_recovered(){
    is_deleted = false;
}

void Person::display_for_out_person() const{
    cout << "ID: " << ID
         << ", Full Name: " << name 
         //<< "Password: " << password
         << ", Birthday: " << birthday
         << ", Gender: " << gender 
         << ", Address: " << address
         << ", Email: " << email
         << ", Phone: " << phone
         << ", Is_deleted: " << is_deleted;
}

