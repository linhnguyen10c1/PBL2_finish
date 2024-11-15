#include "record.h"

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