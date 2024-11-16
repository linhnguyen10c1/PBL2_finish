#include "testing.h"
Doctor* assign_doctor(LinkedList<Doctor>& doctor_list, LinkedList<Testing>& testing_list, int priority, const string &type) {
    Doctor* assigned_doctor = nullptr;
    int min_waiting = INT_MAX;

    Node<Doctor>* current = doctor_list.get_head();
    while (current != nullptr) {
        Doctor& doctor = current->data;
        int patients_today = testing_list.count_patients_today(doctor.get_id());
        int priority_1_patients = testing_list.count_patients_by_priority(doctor.get_id(), 1);
        if (doctor.get_specialization() == type
            && !doctor.get_is_deleted() 
            && patients_today < 65) {
            if (priority == 1) {
                if (priority_1_patients < min_waiting) {
                    min_waiting = priority_1_patients;
                    assigned_doctor = &doctor;
                }
            } else {
                if (doctor.get_waiting() < min_waiting) {
                    min_waiting = doctor.get_waiting();
                    assigned_doctor = &doctor;
                }
            }
        }
        current = current->next;
    }

    return assigned_doctor;
}

void Testing::set_data(long long ID_checking, const string &type, int priority){
      id_checking = ID_checking;
      this->type = type;
      this->priority = priority;
      // làm sao chỉ định đến bệnh nhân đến bác sĩ nào
}

void Testing::update_data(){
      update_start_day();
      status_checking = "processing";
      update_patients_waiting_in_list(get_id_doctor(), "decreasing", get_room());
      Checking::update_result_by_doctor();
}

