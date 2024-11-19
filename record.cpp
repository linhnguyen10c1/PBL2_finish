#include "record.h"

long long Record::set_id = 5000000;
void where(long long ID_checking,LinkedList<Testing> &testing_list, int priority);

// điều kiện để chỉ định bác sĩ nào khám cho bạn
Doctor* assign_doctor(LinkedList<Doctor>& doctor_list, LinkedList<Record>& record_list, int priority) {
    Doctor* assigned_doctor = nullptr;
    int min_priority_1_patients = INT_MAX;
    int min_total_waiting = INT_MAX;

    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        int patients_today = record_list.count_patients_today(doctor.get_id());
        if (doctor.get_specialization() == "General" 
            && !doctor.get_is_deleted() 
            && patients_today < 65) {
            int priority_1_patients = record_list.count_patients_by_priority(doctor.get_id(), 1);
            if (priority == 1) {
                if (priority_1_patients < min_priority_1_patients || 
                    (priority_1_patients == min_priority_1_patients && doctor.get_waiting() < min_total_waiting)) {
                    min_priority_1_patients = priority_1_patients;
                    min_total_waiting = doctor.get_waiting();
                    assigned_doctor = &doctor;
                }
            } else {
                if (doctor.get_waiting() < min_total_waiting || 
                    (doctor.get_waiting() == min_total_waiting && priority_1_patients < min_priority_1_patients)) {
                    min_total_waiting = doctor.get_waiting();
                    min_priority_1_patients = priority_1_patients;
                    assigned_doctor = &doctor;
                }
            }
        }
        current = current->next;
    }

    return assigned_doctor;
}

void Record::display() const{
    cout << "ID Patient: " << id_patient << ", "
         << "ID Doctor: " << id_doctor << ", ";
    Checking::display();
    cout << "Heart Rate: " << heart << ", "
         << "Blood Pressure: " << blood << ", "
         << "Symptom: " << symptom << ", "
         << "Diagnosis: " << diagnosis << ", "
         << "Status Patient: " << status_patient << ", "
         << "Testing or not: " << testing_or_not << ", "
         << "Transfer or not: " << transfer_hospital << ", "
         << "Cost: " << cost << ", "
         << "Status Payment: " << status_payment << ", "
         << "Follow-up-appointment: " << follow_up_appointment << endl;
}

// dành cho admin sẽ khởi tạo dữ liệu và thuật toán sẽ đưa ra bác sĩ khám cho bệnh nhân
void Record::set_data(){
    LinkedList<Patient> patient_list;
    LinkedList<Doctor> doctor_list;
    LinkedList<Record> record_list;
    read_data_from_file(patient_list,"patients.txt");
    read_data_from_file(record_list, "records.txt");
    // kiểm tra bệnh nhân đã tồn tại trong danh sách
    bool patient_exists = false;
    do {
        cout << "Enter patient ID: ";
        cin >> id_patient;
        cin.ignore();
        patient_exists = patient_list.search_check_update_delete_recover_by_id(id_patient, "check");

        if (!patient_exists) {
            int choice;
            cout << "Patient ID not found. Choose an option:" << endl;
            cout << "1. Re-enter patient ID" << endl;
            cout << "2. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore();

            if (choice == 2) {
                return;
            }
        }
    } while (!patient_exists);

  // độ ưu tiên 1 là khẩn cấp, 3 là không, 2 là đã đặt trước đó rồi

    if(priority == 0){
      cout << "Priority 1 or 3: ";
      cin >> priority;
      cin.ignore();
    }

    cout << "priority: " << priority;

     // set dữ liệu id_checking, urgent
    id_checking = set_id++;
    cout << "ID checking: " << id_checking << endl;
   
    // phần luồng khám đến khám bác sĩ nào
    read_data_from_file(doctor_list, "doctors.txt");
     Doctor* assigned_doctor = assign_doctor(doctor_list, record_list, priority);

    // Check if a suitable doctor was found
    if (assigned_doctor) {
        id_doctor = assigned_doctor->get_id();
        room = assigned_doctor->get_room();
        assigned_doctor->update_patients_waiting("increasing");
        cout << "Assigned to doctor ID: " << id_doctor
             << ", At room: " << room << endl;
        write_data_to_file(doctor_list, "doctors.txt");
    } else {
        cout << "No suitable doctor found." << endl;
    }

}

void Record::read_a_object_from_file(const string &line) {
    stringstream ss(line);
    string item;

    // Read and convert id_checking
    getline(ss, item, ',');
    id_checking = stoll(item);
    // Read the rest of the record's data
    getline(ss, item, ',');
    id_patient = stoll(item);
    getline(ss, item, ',');
    id_doctor = stoll(item);
    getline(ss, item, ',');
    priority = stoi(item);

    getline(ss, room, ',');
    getline(ss, status_checking, ',');
    getline(ss, start_checking, ',');
    getline(ss, end_checking, ',');

    getline(ss, item, ',');
    heart = stod(item);
    getline(ss, item, ',');
    blood = stod(item);

    getline(ss, symptom, ',');
    getline(ss, diagnosis, ',');
    getline(ss, status_patient, ',');

    //testing or not
    //transfer_hospital or not
    getline(ss, item, ',');
    testing_or_not = (item == "Yes");
    getline(ss, item, ',');
    transfer_hospital = (item == "Yes");

    getline(ss, final_result, ',');
    getline(ss, doctor_note, ',');
    getline(ss, follow_up_appointment, ',');

    getline(ss, item, ',');
    cost = stod(item);
    getline(ss, item, ',');
    status_payment = stod(item);
    getline(ss, item, ',');
    is_deleted = (item == "Yes");
}

void Record::write_a_object_to_file(ofstream &file) {
    if (file.is_open()) {
        file << id_checking << ","
             << id_patient << ","
             << id_doctor << ","
             << priority << ","
             << room << ","
             << status_checking << ","
             << start_checking << ","
             << end_checking << ","
             << heart << ","
             << blood << ","
             << symptom << ","
             << diagnosis << ","
             << status_patient << ","
             << (testing_or_not ? "Yes" : "No") << ","
             << (transfer_hospital ? "Yes" : "No") << ","
             << final_result << ","
             << doctor_note << ","
             << follow_up_appointment << ","
             << cost << ","
             << status_payment << ","
             << (is_deleted ? "Yes" : "No") << endl;
    } else {
        cerr << "Error: File is not open." << endl;
    }
}


// dành cho bác sĩ có chức năng viết dữ liệu vào file 
void Record::update_data(){
    status_checking = "processing";
    // decreasing?? doctors.txt
    update_patients_waiting_in_list(get_id_doctor(), "decreasing");

    update_start_day();

    // Update heart rate
    cout << "Heart Rate: ";
    cin >> heart;
    cin.ignore();

    // Update blood pressure
    cout << "Blood Pressure: ";
    cin >> blood;
    cin.ignore();

    // Update symptom
    cout << "Symptom: ";
    getline(cin, symptom);

    // Update diagnosis
    cout << "Diagnosis: ";
    getline(cin, diagnosis);

    // Update status of the patient
    cout << "Status Patient: ";
    getline(cin, status_patient);

    
    int testing;
    do {
        x = 0;
        cout << "Testing or not (1 for Yes, 0 for No): ";
        cin >> testing;
        cin.ignore();
        if (testing != 1 && testing != 0) {
            cout << "Invalid input. Please enter 1 for Yes or 0 for No." << endl;
        }
    } while (testing != 1 && testing != 0);
    testing_or_not = (testing == 1);
    if (testing_or_not) {
        testing_detail(get_id(), get_priority());
        return;
    }

    // Update transfer hospital status
    int transfer;
    do {
        cout << "Transfer Hospital (1 for Yes, 0 for No): ";
        cin >> transfer;
        cin.ignore();
        if (transfer != 1 && transfer != 0) {
            cout << "Invalid input. Please enter 1 for Yes or 0 for No." << endl;
        }
    } while (transfer != 1 && transfer != 0);
    transfer_hospital = (transfer == 1);
    if (transfer_hospital) {
        status_checking = "completed";
        update_end_day();
        cost = 0;
        return;
    }

    update_result_by_doctor();
}

void Record::testing_detail(long long ID_checking, int priority){
    LinkedList<Testing> testing_list;
	read_data_from_file_for_test(testing_list, "testings.txt");
	Testing item;
	    int choice;
		    do
			{
			cout << "1. X-ray" << endl
				 << "2. Endoscopy" << endl
				 << "3. Ultrasound" << endl
				 << "4. Blood and Urine Test" << endl
				 << "5. Electrocardiogram" << endl
				 << "0. Exit" << endl;
					 cout << "Choose your choice: ";
					 cin >> choice;
					 cin.ignore();
						switch (choice)
						{
						case 1:
						{   string part_body;
                            cout << "Enter part of body need testing: ";
                            getline(cin, part_body);
							item.set_data(ID_checking, "X-ray", priority, part_body);
							testing_list.add_for_test(item);
							write_data_to_file(testing_list, "testings.txt");
							break;
						}
						case 2:
						{
                            string part_body;
                            cout << "Enter part of body need testing: ";
                            getline(cin, part_body);
							item.set_data(ID_checking, "Endoscopy", priority, part_body);
							testing_list.add_for_test(item);
							write_data_to_file(testing_list, "testings.txt");
							break;
						}
						case 3:
						{
                            string part_body;
                            cout << "Enter part of body need testing: ";
                            getline(cin, part_body);
							item.set_data(ID_checking, "Ultrasound", priority, part_body);
							testing_list.add_for_test(item);
							write_data_to_file(testing_list, "testings.txt");
							break;
						}
						case 4:
						{
							item.set_data(ID_checking, "Blood and Urine Test", priority, "Blood and Urine");
							testing_list.add_for_test(item);
							write_data_to_file(testing_list, "testings.txt");
							break;
						}
						case 5:
						{
							item.set_data(ID_checking, "Electrocardiogram", priority, "Heart");
							testing_list.add_for_test(item);
							write_data_to_file(testing_list, "testings.txt");
							break;
						}

						case 0:
						{
							break;
						}
						}

					} while (choice != 0);
                // chỉ ra bệnh nhân nên đi đến đâu đầu tiên
                where(ID_checking, testing_list, priority); 
                
				}
// coi lại đoạn count_waiting_room
void where(long long ID_checking,LinkedList<Testing> &testing_list, int priority){
   int min_priority_1_patients = INT_MAX;
   int min_total_waiting = INT_MAX;
   Testing *assigned_test = nullptr;
   Node<Testing> *current = testing_list.get_head();
   while(current != nullptr){
    Testing &testing = current->data;
    if(testing.get_id() == ID_checking && testing.get_status_checking() == "waiting"){
        int priority_1_patients = testing_list.count_patients_by_priority(testing.get_id_doctor(), priority);
        int total_waiting = testing_list.count_waiting_room(testing.get_id_doctor()) ;
        if(priority == 1){
            if(priority_1_patients < min_priority_1_patients ||
                 (priority_1_patients == min_priority_1_patients && total_waiting < min_total_waiting)){
                    min_priority_1_patients = priority_1_patients;
                    min_total_waiting = total_waiting;
                    assigned_test = &testing;
            }
        }
        else {
            if(total_waiting < min_total_waiting || (total_waiting == min_total_waiting && priority_1_patients < min_priority_1_patients)){
                min_total_waiting = total_waiting;
                min_priority_1_patients = priority_1_patients;
                assigned_test = &testing;
            }
        }
    }
    current = current->next;
   }
   cout << "You should go to: " << (*assigned_test).get_room() << " first" << endl;
   (*assigned_test). update_data_have_another_testing();
   write_data_to_file(testing_list, "testings.txt");

}
