#include "record.h"

long long Record::set_id = 5000000;
Doctor* assign_doctor(LinkedList<Doctor>& doctor_list, LinkedList<Record>& record_list) {
    Doctor* assigned_doctor = nullptr;
    int min_waiting = INT_MAX;

    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        int patients_today = record_list.count_patients_today(doctor.get_id());
        if (doctor.get_specialization() == "General" 
            && !doctor.get_is_deleted() 
            && patients_today < 65) {
            if (doctor.get_waiting() < min_waiting) {
                min_waiting = doctor.get_waiting();
                assigned_doctor = &doctor;
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
         << "Status Payment: " << status_payment << ", "
         << "Follow-up-appointment: " << follow_up_appointment << endl;
}

void Record::set_data(){
    LinkedList<Patient> patient_list;
    LinkedList<Doctor> doctor_list;
    LinkedList<Record> record_list;
    // kiểm tra bệnh nhân đã tồn tại trong danh sách
    bool patient_exists = false;
    do {
        cout << "Enter patient ID: ";
        cin >> id_patient;
        cin.ignore();
        read_data_from_file(patient_list,"patients.txt");
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
      cout << "Priority 1-3: ";
      cin >> priority;
      cin.ignore();
    }

     // set dữ liệu id_checking, urgent
    id_checking = set_id++;
    cout << "ID checking: " << id_checking << endl;
   
    // phần luồng khám đến khám bác sĩ nào
    read_data_from_file(doctor_list, "doctors.txt");
     Doctor* assigned_doctor = assign_doctor(doctor_list, record_list);

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
