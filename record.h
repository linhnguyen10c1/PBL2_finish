#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include "checking.h"
#include "patient.h"
#include "doctor.h"
#include "linklist.h"

using namespace std;

class Record :public Checking{
private:
    long long id_patient;
    double heart = 0;
    double blood = 0;
    string symptom = "0";
    string diagnosis = "0";
    string status_patient = "0";
    bool testing_or_not = false;// có thực hiện test hay không
    bool transfer_hospital = false;// có chuyển viện hay không
    double status_payment = 0;
    string follow_up_appointment = "0";

public:
    static long long set_id;
    // dành cho administrator KHÓ
    /*1. đưa ra ID checking tự động
      2. cho bt ai là người khám, phòng nào
      dựa vào độ khẩn cấp, bác sĩ đang có người chờ ít nhất
      3. trạng thái waiting*/
    void set_data();

    void display() const;
  
    // dành cho doctor_general
    void update_data_general_doctor(double x);

    void read_a_object_from_file(const string &line);
    void write_a_object_to_file(ofstream &file);
   
};


#endif 
