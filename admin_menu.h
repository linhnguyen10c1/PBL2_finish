#ifndef ADMINMENU_H
#define ADMINMEUNU_H

#include "doctor.h"
#include "patient.h"
#include "medicine.h"
#include "record.h"
#include "linklist.h"
#include <iostream>
using namespace std;

template <typename T>
void module_menu_admin(LinkedList<T>& list,const string& filename){
	read_data_from_file(list, filename);
	int choice;
	do {
		cout << "----------------------" << endl;
		cout << "1. Add an object" << endl
         << "2. Display list objects"<< endl
         << "3. Search an object" << endl 
		     << "4. Update an object"<< endl
         << "5. Delete" << endl
				 << "6. Recover" << endl
         << "0. Exit" << endl;
    cout << "----------------------" << endl;

		cout << "Choose an option: ";
		cin >> choice;
		cin.ignore();
		
		switch (choice){
			case 1:{
        T::set_id = list.get_id_from_file();
				T item;
				item.set_data(); // set_data() của record vẫn chưa làm được
				list.add(item);
				write_data_to_file(list,filename);
				cout << "Object added successfully" << endl;
				break;
			}
			case 2:{
				list.display_list();
				break;
			}
			case 3:{
				long long id;
				cout << "Enter ID you want search: ";
				cin >> id;
				list.search_check_update_delete_recover_by_id(id, "search");
				break;
			}
			case 4:{
				long long id;
				cout << "Enter ID you want update: ";
				cin  >> id;
				cin.ignore();
				list.search_check_update_delete_recover_by_id(id, "update");
				write_data_to_file(list,filename);
				break;
			}
			case 5:{
				long long id;
				cout << "Enter ID you want delete: ";
				cin >> id;
				cin.ignore();
				list.search_check_update_delete_recover_by_id(id,"delete");
				write_data_to_file(list,filename);
				break;
			}
			case 6: {
				long long id;
				cout << "Enter ID you want recover: ";
				cin >> id;
        cin.ignore();
				list.search_check_update_delete_recover_by_id(id,"recover");
				write_data_to_file(list,filename);
				break;
			}
		}
	} while(choice != 0);
}


void menu_admin(){
   LinkedList<Patient> patient_list;
   LinkedList<Doctor> doctor_list;
	 LinkedList<Medicine> medicine_list;
   LinkedList<Record> record_list;
	int choice;
	  do{
    cout << "----------------------" << endl;
		cout<< "1. Manage doctors"<< endl
		    << "2. Manage patients"<< endl
			  << "3. Manage medicines "<<endl
        << "4. Manage medical record" << endl
				<< "5. Statistic (mở rộng sau)" << endl 
				<< "0. exit"<< endl;
    cout << "----------------------" << endl;

		cout << "Choose an option: ";
		cin>>choice;
		cin.ignore();
		switch (choice){
			case 1:
				 module_menu_admin(doctor_list,"doctors.txt");
				break;
			case 2:
				 module_menu_admin(patient_list,"patients.txt");
				break;
			case 3:
				 module_menu_admin(medicine_list,"medicines.txt");
				break;
			case 4: 
         module_menu_admin(record_list, "records.txt");
				 /* cần giải quyết add một cái record mới: hệ thống
				 cần chỉ ra đến bác sĩ nào là tối ưu*/
				break;
			case 0: 








			  break;
		}
	}while(choice != 0);
}

#endif 