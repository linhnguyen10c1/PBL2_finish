#include "testing.h"

void Testing::check_condition_doctor(const string &type){
    LinkedList<Doctor> doctor_list;
    read_data_from_file(doctor_list, "doctors.txt");
    LinkedList<Testing> testing_list;
    read_data_from_file(testing_list, "testings.txt");
    Node<Doctor> *current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        int patients_today = testing_list.count_patients_today(doctor.get_id());
        if (doctor.get_specialization() == type&& !doctor.get_is_deleted() && patients_today < 65){
                if (id_doctor2 == 0) {
                this->id_doctor2 = doctor.get_id();
                doctor.update_patients_waiting("increasing");
            } else {
                this->id_doctor = doctor.get_id();
                doctor.update_patients_waiting("increasing");
            }
            room = doctor.get_room();
            Testing::cost = doctor.get_price();
        }
        
        current = current->next;
    }
    write_data_to_file(doctor_list, "doctors.txt");
}

void Testing::set_data(long long ID_checking, const string &type, int priority, const string &part_body){
      id_doctor2 = 0;
      id_checking = ID_checking;
      this->type = type;
      this->priority = priority;
      this->part_of_body_need_test = part_body;
      status_checking = "waiting";
      check_condition_doctor(type);
      cout <<"ID doctor1: " << id_doctor << ", ";
      cout << "ID doctor2: " << id_doctor2 << endl;
      cout << "At room: " << room << endl;
      // xem bác sĩ khám type đó có tồn tại không, có thỏa mãn điều kiện khám bao nhiêu ca một ngày không
      // thì bác sĩ được gán vào, và tăng số lượng người đang chờ đợi
      
}

void Testing::update_data(){
      update_start_day();
      status_checking = "processing";
      
      update_patients_waiting_in_list(get_id_doctor(), "decreasing", get_room());
      Checking::update_result_by_doctor();
}


void Testing::display() const{
    cout << "ID doctor 1: " << id_doctor << ", "
         << "ID doctor 2: " << id_doctor2 << ", ";
    Checking::display();

    cout << "Type: " << type << ", "
         << "Test_part_of_body: " << part_of_body_need_test << ", "
         << "Cost: " << Testing::cost << ", "
         << "Having another test: " << is_having_another_testing << endl;
}

void Testing::read_a_object_from_file(const string &line){
        stringstream ss(line);
    string item;
    getline(ss, item, ',');
    id_doctor = stoll(item);
    getline(ss, item, ',');
    id_doctor2 = stoll(item);
    // Read and convert id_checking
    getline(ss, item, ',');
    id_checking = stoll(item);
    // Read the rest of the record's data
    getline(ss, type, ',');
    getline(ss, part_of_body_need_test, ',');
    getline(ss, item, ',');
    priority = stoi(item);

    getline(ss, room, ',');
    getline(ss, status_checking, ',');
    getline(ss, start_checking, ',');
    getline(ss, end_checking, ',');
    //có đang thực hiện một test khác hay không
    getline(ss, item, ',');
    is_having_another_testing = (item == "Yes");

    getline(ss, final_result, ',');
    getline(ss, doctor_note, ',');

    getline(ss, item, ',');
    cost = stod(item);

    getline(ss, item, ',');
    is_deleted = (item == "Yes");
}

void Testing::write_a_object_to_file(ofstream &file){
        if (file.is_open()) {
        file << id_doctor << ","
             << id_doctor2 << ","
             << id_checking << ","
             << type << ","
             << part_of_body_need_test << ","
             << priority << ","
             << room << ","
             << status_checking << ","
             << start_checking << ","
             << end_checking << ","
             << (is_having_another_testing ? "Yes" : "No") << ","
             << final_result << ","
             << doctor_note << ","
             << cost << ","
             << (is_deleted ? "Yes" : "No") << endl;
    } else {
        cerr << "Error: File is not open." << endl;
    }
}