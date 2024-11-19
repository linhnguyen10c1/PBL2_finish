#ifndef DOCTORMENU_H
#define DOCTORMEUNU_H
#include "linklist.h"
#include "doctor.h"
#include "record.h"
#include "testing.h"

// kiểm tra chuyên môn hóa của bác sĩ là gì, để phân ra menu
int check_specialization(long long ID_doctor, LinkedList<Doctor> &doctor_list){
           Node<Doctor>* current = doctor_list.get_head();
         if(current == nullptr){
            cout << "List empty" << endl;
            return 0;
         }
        while (current) {
            if(current->data.get_id() == ID_doctor && current->data.get_is_deleted() == false)
                 if(current->data.get_specialization() == "General"){
                      return 1;}
                 else return 2;
    
            current = current->next;
        }
        return 0;
}

// in ra danh sách waiting
void display_list_waiting(long long ID_doctor, LinkedList<Record> &record_list){
    Node<Record> *current = record_list.get_head();
    if(current == nullptr){
      cout << "List empty" << endl;
      return;
    }
    Node<Record>* temp = current;
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

void  display_list_waiting_in_testing(long long ID, LinkedList<Testing> &record_list){
    Node<Testing> *current = record_list.get_head();
    if(current == nullptr){
      cout << "List empty" << endl;
      return;
    }
    Node<Testing>* temp = current;
    while (temp != nullptr) {
        if (temp->data.get_id_doctor() == ID && !temp->data.get_is_deleted() && temp->data.get_status_checking() == "waiting" && temp->data.get_priority() == 1) {
            temp->data.display();
        }
        temp = temp->next;
    }

    // Print records with priority 2
    temp = current;
    while (temp != nullptr) {
        if (temp->data.get_id_doctor() == ID && !temp->data.get_is_deleted() && temp->data.get_status_checking() == "waiting" && temp->data.get_priority() == 2) {
            temp->data.display();
        }
        temp = temp->next;
    }

    // Print records with priority 3
    temp = current;
    while (temp != nullptr) {
        if (temp->data.get_id_doctor() == ID && !temp->data.get_is_deleted() && temp->data.get_status_checking() == "waiting" && temp->data.get_priority() == 3) {
            temp->data.display();
        }
        temp = temp->next;
    }
}


void search_record_patient(long long ID_patient, LinkedList<Record> &record_list) {
    Node<Record>* current = record_list.get_head();
    if (current == nullptr) {
        cout << "List empty" << endl;
        return;
    }

    bool found = false;
    while (current != nullptr) {
        if (current->data.get_id_patient() == ID_patient && !current->data.get_is_deleted()) {
            current->data.display();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No records found for patient ID: " << ID_patient << endl;
    }
}

void Menu_detail_doctor(long long ID_doctor, LinkedList<Record> &record_list, LinkedList<Doctor> &doctor_list){
    int choice;
		LinkedList<Testing> testing_list;
	  read_data_from_file_for_test(testing_list, "testings.txt");
	do
	{
		cout << "1. Waiting List" << endl
				 << "2. List Records of a Patient" << endl
				 << "3. Testing" << endl
				 << "0. Exit" << endl;
		cout << "Choose your option: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			display_list_waiting_in_testing(ID_doctor, testing_list);
			break;
		}
		case 2:
		{
			long long ID_patient;
			cout << "ID patient you want search records: ";
			cin >> ID_patient;
			cin.ignore();
			search_record_patient(ID_patient, record_list);
			break;
		}
		case 3: {
      long long ID_checking;
    bool checking_exists = false;
    do {
        cout << "Enter checking ID: ";
        cin >> ID_checking;
        cin.ignore();
        // ngoài tồn tại ra thì còn điều kiện không đang test một cái khác
        checking_exists = testing_list.search_check_update_delete_recover_by_id(ID_checking, "check");

        if (!checking_exists) {
            int choice;
            cout << "Checking ID not found. Choose an option:" << endl;
            cout << "1. Re-enter checking ID" << endl;
            cout << "2. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();
            if (choice == 2) {
                return;
            }
        }
    } while (!checking_exists);
           // sau khi update thì chỉ ra bệnh nhân nên đi đến đâu tiếp theo
		   testing_list.update_data_in_testing(ID_checking, ID_doctor);
			 write_data_to_file(testing_list, "testings.txt");
		}
		case 0:{

		}

		}
	}while(choice != 0);
}

void Menu_general_doctor(long long ID_doctor, LinkedList<Record> &record_list, LinkedList<Doctor> &doctor_list)
{
	int choice;
	do
	{
		cout << "1. Waiting List" << endl
				 << "2. List Records of a Patient" << endl
				 << "3. Checking" << endl
				 << "0. Exit" << endl;
		cout << "Choose your option: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			display_list_waiting(ID_doctor,record_list);
			break;
		}
		case 2:
		{
			long long ID_patient;
			cout << "ID patient you want search records: ";
			cin >> ID_patient;
			cin.ignore();
			search_record_patient(ID_patient, record_list);
			break;
		}

		case 3:
		{

    // kiểm tra xem checking đã có tồn tại hay chưa
    long long ID_checking;
    bool checking_exists = false;
    do {
        cout << "Enter checking ID: ";
        cin >> ID_checking;
        cin.ignore();
        checking_exists = record_list.search_check_update_delete_recover_by_id(ID_checking, "check");

        if (!checking_exists) {
            int choice;
            cout << "Checking ID not found. Choose an option:" << endl;
            cout << "1. Re-enter checking ID" << endl;
            cout << "2. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();
            if (choice == 2) {
                return;
            }
        }
    } while (!checking_exists);
    // các chức năng
    int choice;
			do
			{
				cout << "1. Checking general" << endl
                      << "2. Result Testing" << endl // hiện ra kết quả khám, và update lại kết quả khám
            // trạng thái checking, cost, start_checking, heart, blood, symptom, diagnosis, status patient, testing, transfer_hospital
						 << "3. Prescription" << endl
						 << "4. Appointment" << endl
						 << "0. Exit" << endl;
				cout << "Choose your choice: ";
				cin >> choice;
				cin.ignore();
				switch (choice)
				{
				case 1:
				{
					record_list.search_check_update_delete_recover_by_id(ID_checking, "update");
					write_data_to_file(record_list, "records.txt");
					break;
				}
				case 2:
				{
					if(record_list.update_check_for_test(ID_checking, "check_test_or_not")){
						LinkedList<Testing> testing_list;
						read_data_from_file_for_test(testing_list, "testings.txt");
						testing_list.display_list_for_test(ID_checking);
						record_list.update_check_for_test(ID_checking, "update_result");
						write_data_to_file(record_list, "records.txt");
					}
					else {
						cout << "This ID checking don't has testing" << endl;
					}
              // để truy cập được chức năng này thì trong record có testing_or_not=yes					
        			// testing_list.display_list_testing(ID_checking);
							// break;
				}
				case 3:
				{

				}
				case 4:
				{
				}
				case 0:
				{
				}
				}
			} while (choice != 0);
		}
		}
	} while (choice != 0);
}



void menu_doctor(long long ID_doctor){
  LinkedList<Doctor> doctor_list;
  read_data_from_file(doctor_list, "doctors.txt");
  LinkedList<Record> record_list;
  read_data_from_file(record_list, "records.txt");
  int choice;
	do
	{
		cout << "1. Manage your information" << endl
				 << "2. Manage medical record" << endl
				 << "0. Exit" << endl;
		cout << "Choose your option: ";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1:
		{
			module_menu_manage_personal_information(ID_doctor, doctor_list, "doctors.txt");
			break;
		}
		case 2:
		{
			// nếu là bác sĩ lâm sàng
			if (check_specialization(ID_doctor, doctor_list) == 1)
			{
				  Menu_general_doctor(ID_doctor, record_list, doctor_list);
			}
			else if (check_specialization(ID_doctor, doctor_list) == 2)
			{
				Menu_detail_doctor(ID_doctor, record_list, doctor_list);
			}
			// nếu là bác sĩ cận lâm sàng
		}
		}
	} while (choice != 0);

}

#endif