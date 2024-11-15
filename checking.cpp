#include "checking.h"

long long Checking::set_id = 5000000;

void Checking::display() const {
    cout << "ID checking: " << id_checking << ", "
         << "Urgent: " << urgent << ", "
         << "Room: " << room << ", "
         << "Status Checking: " << status_checking << ", "
         << "Start Checking: " << start_checking << ", "
         << "End Checking: " << end_checking << ", "
         << "Result: " << final_result << ", "
         << "Doctor Note: " << doctor_note
         << "Cost: " << cost << ", "
         << "Is_deleted: " << is_deleted << ", ";
}