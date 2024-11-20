#include "checking.h"

long long Checking::set_id = 5000000;
int Checking::x = 0;

void Checking::display() const {
    cout << "ID checking: " << id_checking << ", "
         << "Priority: " << priority << ", "
         << "Room: " << room << "," 
         << "Status Checking: " << status_checking << ", "
         << "Start Checking: " << start_checking << ", "
         << "End Checking: " << end_checking << ", "
         << "Result: " << final_result << ", "
         << "Doctor Note: " << doctor_note << ", "
         << "Is_deleted: " << is_deleted << ", ";
}


string get_current_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "-" +
           to_string(1 + ltm->tm_mon) + "-" +
           to_string(1900 + ltm->tm_year) + " " +
           to_string(ltm->tm_hour) + ":" +
           to_string(ltm->tm_min) + ":" +
           to_string(ltm->tm_sec);
}

void Checking::update_start_day() {
    start_checking = get_current_time();
}

void Checking::update_end_day() {
    end_checking = get_current_time();
}

// dành cho admin nên đang là linklist Record
void Checking::update_is_recovered() {
        if(end_checking != "0"){
        is_deleted = false;
        }
        else {
            cout << "Please create new record, because patients_waiting of a doctor changed" << endl;
        }
    }

void Checking:: update_is_deleted(){
        if(start_checking == "0"){
            is_deleted = true;
            update_patients_waiting_in_list(get_id_doctor(), "decreasing");
            }
        else {
            cout << "You don't allow delete when doctor is updating data" << endl;
        }
    }


void Checking::update_result_by_doctor(){
    cout << "Result: ";
    getline(cin, final_result);

    // Update doctor's note
    cout << "Doctor's Note: ";
    getline(cin, doctor_note);

    // Update status checking to completed
    status_checking = "completed";
    update_end_day();
    cout << "id_doctor: " << get_id_doctor() << endl;
    x += get_price_of_doctor(get_id_doctor());
    cost = x;
}

void update_patients_waiting_in_list(long long ID_doctor, const string &modify, string room ) {
        LinkedList<Doctor> doctor_list;
        read_data_from_file(doctor_list, "doctors.txt");
        Node<Doctor>* current = doctor_list.get_head();
        while (current != nullptr) {
            Doctor& doctor = current->data;
            if ((doctor.get_id() == ID_doctor || doctor.get_room() == room) && doctor.get_is_deleted() == false) {
                doctor.update_patients_waiting(modify);
            }
            current = current->next;
        }
        write_data_to_file(doctor_list, "doctors.txt");
    }

double get_price_of_doctor(long long ID_doctor){
        LinkedList<Doctor> doctor_list;
        read_data_from_file(doctor_list, "doctors.txt");
        Node<Doctor>* current = doctor_list.get_head();
        while (current != nullptr) {
            Doctor& doctor = current->data;
            if (doctor.get_id() == ID_doctor && doctor.get_is_deleted() == false) {
                return doctor.get_price();
            }
            current = current->next;
        }
        return 0;
}