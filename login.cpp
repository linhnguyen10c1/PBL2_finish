#include <iostream>
#include "linklist.h"
#include "admin.h"
#include "admin_menu.h"
#include "doctor_menu.h"

using namespace std;

template <typename T>
bool is_exist_in_file(long long ID, string password, const string& filename){
  LinkedList<T> list;
  read_data_from_file(list, filename);
  return list.check_id_password(ID, password);
}


void login()
{
  int role;
  do
  {
    long long ID;
    string password;
    cout << "------LOGIN------" << endl;
    cout << "1. You are administrator\n"
         << "2. You are doctor\n"
         << "3. You are patient\n"
         << "0. Exit\n";
    cout << "-----------------" << endl;
    cout << "Choose your option: ";
    cin >> role;
    cin.ignore();

    if(role == 0){
      break;
    }
    
    cout << "Enter your ID: ";
    cin >> ID;
    cout << "Enter your password: ";
    cin >> password;

    switch (role)
    {
    case 1:
    {
      if (is_exist_in_file<Admin>(ID, password,"admins.txt"))
        menu_admin();
      else
        break;
      break;
    }
    case 2:
    {
      if (is_exist_in_file<Doctor>(ID, password, "doctors.txt"))
        menu_doctor(ID);
      else
        break;
      break;
    }
    case 3:
    {
      // if (is_exist_in_file<Patient>(ID, password, "patients.txt"))
      //   //menu_patient(ID);
      //   int x = 1;
      // else
      //   break;
      // break;
    }

    default: {
            cout << "Invalid option. Please try again." << endl;
            break;
    }
    }

  } while (role != 0);
}

int main(){
  LinkedList<Admin> admin_list;
  Admin ad;
  admin_list.add(ad);
  write_data_to_file(admin_list, "admins.txt");
  login();
}