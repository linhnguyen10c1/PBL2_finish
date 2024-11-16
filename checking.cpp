#include "checking.h"

long long Checking::set_id = 5000000;

void Checking::display() const {
    cout << "ID checking: " << id_checking << ", "
         << "Priority: " << priority << ", "
         << "Room: " << room << ", "
         << "Status Checking: " << status_checking << ", "
         << "Start Checking: " << start_checking << ", "
         << "End Checking: " << end_checking << ", "
         << "Result: " << final_result << ", "
         << "Doctor Note: " << doctor_note << ", "
         << "Cost: " << cost << ", "
         << "Is_deleted: " << is_deleted << ", ";
}

void Checking::update_start_day(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    start_checking = to_string(ltm->tm_mday) + "-" +
                to_string(1 + ltm->tm_mon) + "-" +
                to_string(1900 + ltm->tm_year) + " " +
                to_string(ltm->tm_hour) + ":" +
                to_string(ltm->tm_min) + ":" +
                to_string(ltm->tm_sec);
}

void Checking::update_end_day(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    end_checking = to_string(ltm->tm_mday) + "-" +
                to_string(1 + ltm->tm_mon) + "-" +
                to_string(1900 + ltm->tm_year) + " " +
                to_string(ltm->tm_hour) + ":" +
                to_string(ltm->tm_min) + ":" +
                to_string(ltm->tm_sec);
}

void update_patients_waiting_in_list(long long ID_doctor, const string &modify) {
        LinkedList<Doctor> doctor_list;
        read_data_from_file(doctor_list, "doctors.txt");
        Node<Doctor>* current = doctor_list.get_head();
        while (current != nullptr) {
            Doctor& doctor = current->data;
            if (doctor.get_id() == ID_doctor) {
                doctor.update_patients_waiting(modify);
                break;
            }
            current = current->next;
        }
        write_data_to_file(doctor_list, "doctors.txt");
    }