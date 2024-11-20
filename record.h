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
#include "testing.h"
using namespace std;

class Testing;

void where(long long ID_checking,LinkedList<Testing> &testing_list);

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
    void update_data();

    long long get_id_patient() const{ return id_patient;}
    bool get_testing_or_not()const {return testing_or_not;}

    void read_a_object_from_file(const string &line);
    void write_a_object_to_file(ofstream &file);
    
    void testing_detail(long long ID_checking, int priority);
   
};



#endif 
