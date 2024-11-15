#include "doctor.h"

long long Doctor::set_id = 1000000;

void Doctor::set_data(){
  ID = set_id++;
  Doctor::update_info();
  cout << "Doctor has ID: " << ID << ", password: " << password << endl;
}

// chỉ mỗi thông tin cá nhân thôi
void Doctor::update_info(){
  Person::set_data();
  cin.ignore();
  cout << "Enter specialization: ";
  getline(cin, specialization);
  cout << "Enter room: ";
  getline(cin, room);
  cout << "Enter experience year: ";
  cin >> experience_year;
  cin.ignore();
  cout << "Enter price checking: ";
  cin >> price;
  cin.ignore();
}

// tất cả thông tin và password
void Doctor::update_data(){
   int choice;
    do{
    cout << "1. Update Information\n"
         << "2. Update password\n" 
         << "3. Exit\n";
    cout << "Choose your option: ";
    cin >> choice;
    cin.ignore();

    switch (choice){
        case 1:{
              Doctor::update_info();
              cout << "Update successfully" << endl;
              display();
              cout << "\n";
              break;
        }
        case 2:{
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
    } while(choice != 3);
}

void Doctor::update_patients_waiting(const string &modify){
  if(modify == "increasing"){
    ++patients_waiting;
  }
  else if (modify == "decreasing" && patients_waiting > 0){
    --patients_waiting;
  }
}

void Doctor::display() const{
  Person::display_for_out_person();
  cout << ", Password: " << password;
  cout << ", Experience Years: " << experience_year
       << ", Specialization: " << specialization 
       << ", Room: " << room
       << ", Patient Waiting: " << patients_waiting
       << ", Price: " << price << endl;
}

void Doctor::read_a_object_from_file(const string &line) {
    stringstream ss(line);
    string item;
    
    getline(ss, item, ',');
    ID = stoll(item);

    getline(ss, name, ',');
    getline(ss, password, ',');
    getline(ss, birthday, ',');
    getline(ss, gender, ',');
    getline(ss, address, ',');
    getline(ss, email,',');
    getline(ss, phone, ',');
    getline(ss, item, ',');
    is_deleted = (item == "1");
    // Read Doctor specific data
    getline(ss, specialization, ',');
    getline(ss, room, ',');

    getline(ss, item, ',');
    experience_year = stoi(item);

    getline(ss, item, ',');
    patients_waiting = stoi(item);

    getline(ss, item, ',');
    price = stod(item);

}

void Doctor::write_a_object_to_file(ofstream &file) {
    if(file.is_open()){
        file << ID << ","
             << name << ","
             << password << ","
             << birthday << ","
             << gender << ","
             << address << ","
             << email << ","
             << phone << ","
             << (is_deleted ? "1" : "0") << ","
             << specialization << ","
             << room << ","
             << experience_year << ","
             << patients_waiting << ","
             << price << endl;
    } else{
        cerr << "Error: File is not open." << endl;
    }
}