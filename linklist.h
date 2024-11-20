#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "admin.h"

using namespace std;

// Node structure for linked list
template <typename T>
struct Node {
    T data;
    Node* next;
};

// Base class for linked list operations
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    
    LinkedList() : head(nullptr) {}

    Node<T>* get_head() const { return head; }

    // USE IN MENU ADMIN interact list MEDICINE, PATIENT, DOCTOR, RECORD
    // use in login 
    int check_id_password(long long id, string &password);
    //add a object has unique key
    void add(const T& item);
    // use get id_max from file
    long long get_id_from_file();
    //event object was deleted, still display
    void display_list() const;
    int search_check_update_delete_recover_by_id(long long ID,const string &function);

   
     
    // DOCTOR interact list RECORD, TESTING
    // to add a object has 2 foreign key
    void add_for_test(const T& item);
    // display result of testing for general Doctor update final result
    void display_result_testing(long long ID) const;
    // check a record has a attribute testing_or_not and update result for a record by general doctor, after watching result testing
    int checkExist_updateResult_for_record(long long ID, const string &function);
    // kiểm tra xem bác sĩ có ID _checking đó trong record không
    int check_a_doctor_has_ID_checking(long long ID_checking, long long ID_doctor, const string &function);
    int count_patients(long long ID_doctor,const string &function, int priority = 100);
    // display in order, to doctor can call patient in room to check
    void display_list_waiting(long long ID_doctor) const;
    int check_doctor_updated_result(long long ID_checking);
    int check_test_having_another_test(long long ID_checking, long long ID_doctor);

};

// ADMIN
// check a object exist, id, password -> TRUE so can access system
template <typename T>
int LinkedList<T>::check_id_password(long long id, string &password){
     Node<T>* current = head;
        if(current == nullptr){
            cout << "List empty" << endl;
            return 0;
        }
        while (current) {
            if(current->data.get_id() == id 
               && current->data.get_password() == password
               && current->data.get_is_deleted() == false){
                  current->data.display();
                return 1;
            }
            current = current->next;
        }
        cout << "Item don't exist" << endl;
        return 0;
}

template <typename T>
void LinkedList<T>::add(const T& item) {
        Node<T>* newNode = new Node<T>{item, nullptr};
        if (!head) {
            head = newNode;
            return;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                if(temp->data.get_id() == item.get_id()){
                    cout << "Item existed" << endl;
                    return;
                }
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

template <typename T>
long long LinkedList<T>::get_id_from_file(){
    Node<T> *current = head;
    if(current == nullptr){
        return T::set_id;
    }
    else{
        while(current->next){
            current = current->next;
        }
        return (current->data.get_id())+1;
    }
}

template <typename T>
void LinkedList<T>::display_list() const{
        Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return;
    }
    while (current != nullptr) {
            current->data.display();
            current = current->next;
        }
    }

template <typename T>
int LinkedList<T>::search_check_update_delete_recover_by_id(long long ID, const string &function){
    Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr) {
        if (current->data.get_id() == ID) {
            if(function == "search"){
                current->data.display();
                return 1;
            }
            else if((function == "check") || (function == "update") || (function == "delete")){
                if(current->data.get_is_deleted() == false){
                    current->data.display();
                    if(function == "update") current->data.update_data();
                    else if(function == "delete") current->data.update_is_deleted();
                    return 1;
                }
                else {
                    cout << "Item don't exist" << endl;
                    return 0;
                }
            }
            else if(function == "recover"){
                if(current->data.get_is_deleted() == true){
                    current->data.display();
                    current->data.update_is_recovered();
                    return 1;
                }
                else{
                    cout << "Item may still not deleted " << endl;
                    return 0;
                }
            }
        }

        current = current->next;
    }
    cout << "Item don't exist" << endl;
    return 0;
    }



//DOCTOR
template <typename T>
void LinkedList<T>::add_for_test(const T& item) {
        Node<T>* newNode = new Node<T>{item, nullptr};
        if (!head) {
            head = newNode;
            return;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                if(temp->data.get_id() == item.get_id() && temp->data.get_id_doctor()==item.get_id_doctor()){
                    cout << "Item existed" << endl;
                    return;
                }
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

template <typename T>
void LinkedList<T>::display_list_waiting(long long ID_doctor) const{
        Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return;
    }

    // Print records with priority 2
    Node<T>* temp = current;
    while (temp != nullptr) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() && temp->data.get_status_checking() == "waiting" && temp->data.get_priority() == 1) {
            temp->data.display();
        }
        temp = temp->next;
    }

    // Print records with priority 2
    temp = current;
    while (temp != nullptr) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() && temp->data.get_status_checking() == "waiting" && temp->data.get_priority() == 2) {
            temp->data.display();
        }
        temp = temp->next;
    }

    // Print records with priority 3
    temp = current;
    while (temp != nullptr) {
        if (temp->data.get_id_doctor() == ID_doctor && !temp->data.get_is_deleted() && temp->data.get_status_checking() == "waiting" && temp->data.get_priority() == 3) {
            temp->data.display();
        }
        temp = temp->next;
    }
}

template <typename T>
int LinkedList<T>::count_patients(long long ID_doctor, const string &function, int priority){
    int count = 0;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string current_date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);
    Node<T> *current = head;
    
    if (current == nullptr){
        cout << "List is empty" << endl;
    }
    while (current != nullptr) {
        const T& record = current->data;
        if (record.get_id_doctor() == ID_doctor && !record.get_is_deleted()){
            if(function == "today"){
               if( record.get_date().substr(0, 10) == current_date) count++;
            }
            else if(function == "waiting"){
                if(record.get_status_checking() == "waiting") count ++;
            }
            else if(function == "priority"){
                if(record.get_status_checking() == "waiting" && record.get_priority() == priority) count ++;
            }
        }
        current = current->next;
    }
    return count;
}

template <typename T> 
int LinkedList<T>::check_test_having_another_test(long long ID_checking, long long ID_doctor){
    Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return 0;
    }
    while(current != nullptr){
        // chưa update
        if(current->data.get_id_doctor()== ID_doctor && current->data.get_id() == ID_checking && current->data.get_date() == "0" && !current->data.get_is_having_another_testing() ){
            current->data.update_data();
            return 1;
        }
        current = current->next;
    }
    // update rồi
    return 0;
}

template <typename T>
void LinkedList<T>::display_result_testing(long long ID) const{
        Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return;
    }
    while (current != nullptr){
        // date!= 0 -> has result testing -> doctor(general)-> watch, and update result
        if(current->data.get_id() == ID && current->data.get_date() != "0" && !current->data.get_is_deleted() )  {
            current->data.display();
        }
          current = current->next;
    }
}

template <typename T>
int LinkedList<T>::checkExist_updateResult_for_record(long long ID, const string &function){
    Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr) {
        if (current->data.get_id() == ID) {
           if(function == "check_test_or_not"){
                if(current->data.get_testing_or_not()) return 1;
                else return 0;
           }
           else if(function == "update_result"){
                 current->data.update_result_by_doctor();
                 return 1;
           }
        }
        current = current->next;
    }
    return 0;
}

// kiểm tra xem bác sĩ đó có ID khám đó không
template <typename T>
int LinkedList<T>::check_a_doctor_has_ID_checking(long long ID_checking, long long ID_doctor, const string &function)
{
    Node<T> *current = head;
    if (current == nullptr)
    {
        cout << "List empty" << endl;
        return 0;
    }
    while (current != nullptr)
    {
        if (current->data.get_id() == ID_checking && current->data.get_id_doctor() == ID_doctor && !current->data.get_is_deleted())
        {
            if (function == "check")
                return 1;
            else if (function == "update")
            {
                if (current->data.get_date() == "0")
                {
                    current->data.update_data();
                    return 1;
                }
            }
        }
        current = current->next;
    }
    return 0;
}

template <typename T> 
int LinkedList<T>::check_doctor_updated_result(long long ID_checking){
    Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return 2;
    }
    while(current != nullptr){
        // chưa update
        if(current->data.get_id() == ID_checking && current->data.get_date() == "0" )
        return 0;

        current = current->next;
    }
    // update rồi
    return 1;
}

//FILE
template <typename T>
void read_data_from_file(LinkedList<T>& list, const string& filename) {
    ifstream file(filename); 
    string line;
    while (getline(file, line)) {  
        T item;
        item.read_a_object_from_file(line); 
        list.add(item); 
    }
    file.close();  
}

template <typename T>
void read_data_from_file_for_test(LinkedList<T>& list, const string& filename) {
    ifstream file(filename); 
    string line;
    while (getline(file, line)) {  
        T item;
        item.read_a_object_from_file(line); 
        list.add_for_test(item); 
    }
    file.close();  
}

template <typename T>
void write_data_to_file(LinkedList<T>& list,const string& filename) {
    ofstream file(filename);
    Node<T>* temp = list.get_head();
	  while (temp != nullptr) {
			  temp->data.write_a_object_to_file(file);
	      temp = temp->next;
	    }

    file.close();
    cout << "Data was wrote in: " << filename << endl;
}


// chung DOCTOR, PATIENT
template <typename T>
void module_menu_manage_personal_information(long long ID, LinkedList<T> &list, const string &filename)
{
	//read_data_from_file(list, filename);
	int choice;
	do
	{
		cout << "1. Display your information" << endl
				 << "2. Update your information" << endl
				 << "0. Exit" << endl;
		cout << "Choose your option: ";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1:
		{
			list.search_check_update_delete_recover_by_id(ID, "check");
			break;
		}
		case 2:
		{
			list.search_check_update_delete_recover_by_id(ID, "update");
			write_data_to_file(list, filename);
			break;
		}
		case 0:
		{
		}
		}

	} while (choice != 0);
}

 #endif 