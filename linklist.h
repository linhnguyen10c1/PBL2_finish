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
// tình trạng mức độ bệnh, 
// Base class for linked list operations
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    
    LinkedList() : head(nullptr) {}

    Node<T>* get_head() const { return head; }
    // check xem tai khoan bac si, benh nhan, admin co ton tai ko
    int check_id_password(long long id, string &password);
    // thêm một node vào file với điều kiện ID khác nhau
    void add(const T& item);
    void add_for_test(const T& item);

    long long get_id_from_file();
    // hiện thị lớp ngày 
    void display_list() const;
    
    void display_list_for_test(long long ID) const;

    int update_check_for_test(long long ID, const string &function);

    void update_data_in_testing(long long ID_checking, long long ID_doctor);

    // đưa ID vào đúng là được data.get_id() = id 
    // search: cho dù ko tồn tại vẫn có thể tìm ra display
    // check: phải tồn tại data.get_is_deleted = false -> return 1
    // update: data.get_is_deleted = false -> data.update

    int search_check_update_delete_recover_by_id(long long ID,const string &function);
    int count_waiting_room(long long doctor_id) const;
    int count_patients_today(long long id_doctor) const;
    int count_patients_by_priority(long long doctor_id, int priority) const ;
};
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
        cout << "Item don't exsit" << endl;
        return 0;
}
// add cho trường hợp csdl có khóa chính
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

// add cho trường hợp csdl chỉ có hai khóa ngoại
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
void LinkedList<T>::display_list_for_test(long long ID) const{
        Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
        return;
    }
    while (current != nullptr){
        if(current->data.get_id() == ID && current->data.get_date() != "0" )  {
            current->data.display();
        }
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

template <typename T>
int LinkedList<T>::update_check_for_test(long long ID, const string &function){
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

template <typename T>
void LinkedList<T>::update_data_in_testing(long long ID_checking, long long ID_doctor){
    Node<T>* current = head;
    if(current == nullptr){
        cout << "List empty" << endl;
    }
    while (current != nullptr) {
        cout << "haha1" << endl;
        if(current->data.get_id() == ID_checking && current->data.get_id_doctor() == ID_doctor){
            cout << "haha" << endl;
            current->data.update_data();
            return;
        }
        current = current->next;
    }
}

template <typename T>
int LinkedList<T>::count_patients_today(long long doctor_id) const {
    int count = 0;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string current_date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);

    Node<T>* current = head;
    while (current != nullptr) {
        const T& record = current->data;
        if (record.get_id_doctor() == doctor_id && record.get_date().substr(0, 10) == current_date && !record.get_is_deleted() ) {
            count++;
        }
        current = current->next;
    }
    return count;
}


template <typename T>
int LinkedList<T>::count_patients_by_priority(long long doctor_id, int priority) const {
    int count = 0;
    Node<T>* current = head;
    if(current == nullptr) {cout << "Danh sách trống"<< endl;}
    while (current != nullptr) {
        const T& record = current->data;
        if (record.get_id_doctor() == doctor_id && record.get_priority() == priority && !record.get_is_deleted()
            && record.get_status_checking() == "waiting") {
            count++;
        }
        current = current->next;
    }
    return count;
}

template <typename T>
int LinkedList<T>::count_waiting_room(long long doctor_id) const{
    int count = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        const T& record = current->data;
        if (record.get_status_checking() == "waiting" && record.get_id_doctor() == doctor_id &&!record.get_is_deleted() ) {
            count++;
        }
        current = current->next;
    }
    return count;
}

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

// vì patient, doctor có cả phần này nên dùng template cho tiện
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