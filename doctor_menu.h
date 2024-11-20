#ifndef DOCTORMENU_H
#define DOCTORMEUNU_H
#include "linklist.h"
#include "doctor.h"
#include "record.h"
#include "medicine.h"
#include "prescription.h"
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
			testing_list.display_list_waiting(ID_doctor);
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
        // xem lại đoạn này 
        // kiểm tra tồn tại, đã được ghi hay chưa, và có đg thực hiện test khác không -> thỏa mãn điều kiện mới update
        checking_exists = testing_list.check_test_having_another_test(ID_checking, ID_doctor);

        if (checking_exists == 0) {
            int choice;
            cout << "Checking ID not found or Patient is having another test. Choose an option:" << endl;
            cout << "1. Re-enter checking ID" << endl;
            cout << "2. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();
            if (choice == 2) {
                return;
            }
        }

    } while (checking_exists == 0);
    
			 write_data_to_file(testing_list, "testings.txt");
             // sau khi update thì chỉ ra bệnh nhân nên đi đến đâu tiếp theo
             where(ID_checking, testing_list);
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
            record_list.display_list_waiting(ID_doctor);
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

            // kiểm tra xem checking đã có tồn tại hay chưa, và bác sĩ có khám cho ID đó không
            long long ID_checking;
            bool checking_exists = false;
            do
            {
                cout << "Enter checking ID: ";
                cin >> ID_checking;
                cin.ignore();
                // coi lại đoạn này vì nếu bác sĩ đó không có khám ID_checkign
                checking_exists = record_list.check_a_doctor_has_ID_checking(ID_checking, ID_doctor, "check");

                if (!checking_exists)
                {
                    int choice;
                    cout << "Checking ID not found. Choose an option:" << endl;
                    cout << "1. Re-enter checking ID" << endl;
                    cout << "2. Exit" << endl;
                    cout << "Choose an option: ";
                    cin >> choice;
                    cin.ignore();
                    if (choice == 2)
                    {
                        return;
                    }
                }
            } while (!checking_exists);

            // nếu đã tồn tại mở ở ra các chức năng tiếp theo
            // các chức năng
            int choice;
            do
            {
                cout << "1. Checking general" << endl
                     << "2. Result Testing" << endl
                     << "3. Prescription" << endl
                     << "4. Appointment" << endl
                     << "0. Exit" << endl;
                cout << "Choose your choice: ";
                cin >> choice;
                cin.ignore();
                switch (choice)
                {
                case 1:
                { // kiểm tra đã được khám trước đó chưa
                    if (record_list.check_a_doctor_has_ID_checking(ID_checking, ID_doctor, "update"))
                    { // nếu chưa thì ghi vào thì sẽ ghi kết quả bth
                        write_data_to_file(record_list, "records.txt");
                    }
                    else
                        cout << "General result updated" << endl;
                    break;
                }
                case 2:
                {
                    LinkedList<Testing> testing_list;
                    read_data_from_file_for_test(testing_list, "testings.txt");
                    // kiểm tra record có testing hay không
                    if (record_list.checkExist_updateResult_for_record(ID_checking, "check_test_or_not"))
                    {
                        // nếu có

                        testing_list.display_result_testing(ID_checking);

                        // Kiểm tra xem kết quả testing đã được cập nhật bởi bác sĩ test hay chưa
                        if (testing_list.check_doctor_updated_result(ID_checking) == 1)
                        {
                            // Cho phép bác sĩ General cập nhật kết quả cho record
                            record_list.checkExist_updateResult_for_record(ID_checking, "update_result");
                            write_data_to_file(record_list, "records.txt");
                        }
                        else
                        {
                            cout << "Testing results have not been updated by the test doctor yet." << endl;
                        }
                    }
                    else
                    {
                        cout << "This ID checking doesn't have testing." << endl;
                    }
                    break;
                }
                case 3:
                {
                    long long ID_medicine;
                    LinkedList<Medicine> medicine_list;
                    LinkedList<Prescription> prescription_list;

                    // Đọc danh sách thuốc và đơn thuốc từ file
                    read_data_from_file(medicine_list, "medicines.txt");
                    read_data_from_file(prescription_list, "prescriptions.txt");

                    // Kiểm tra điều kiện kê đơn
                    if (!record_list.checkExist_updateResult_for_record(ID_checking, "check_completed"))
                    {
                        cout << "Cannot prescribe medicine. Ensure the examination or testing results are completed first." << endl;
                        break;
                    }

                    int option = 0;
                    while (option != 2)
                    {
                        cout << "1. Add a medicine to the prescription" << endl
                             << "2. Finish prescription" << endl
                             << "Choose your option: ";
                        cin >> option;

                        if (option == 1)
                        {
                            cout << "Enter the ID of the medicine: ";
                            cin >> ID_medicine;

                            // Kiểm tra thuốc có tồn tại trong danh sách
                            if (!medicine_list.search_check_update_delete_recover_by_id(ID_medicine, "check"))
                            {
                                cout << "Medicine not found. Please try again." << endl;
                                continue;
                            }

                            // Nhập thông tin kê đơn
                            int quantity;
                            string instruction;
                            cout << "Enter the quantity: ";
                            cin >> quantity;
                            cin.ignore(); // Xóa ký tự newline trong bộ đệm
                            cout << "Enter the usage instruction: ";
                            getline(cin, instruction);

                            // Tạo đơn thuốc và thêm vào danh sách
                            Prescription prescription;
                            prescription.set_data(ID_checking, ID_medicine, quantity, instruction, medicine_list);
                            prescription_list.add(prescription);

                            cout << "Medicine added to the prescription." << endl;
                        }
                    }

                    // Lưu danh sách đơn thuốc vào file
                    write_data_to_file(prescription_list, "prescriptions.txt");
                    cout << "Prescription saved successfully!" << endl;
                    break;
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