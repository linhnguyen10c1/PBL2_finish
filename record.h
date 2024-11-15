#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include "checking.h"

using namespace std;

class Record :public Checking{
private:
    long long id_patient;
    double heart = 0;
    double blood = 0;
    string symptom = "0";
    string diagnosis = "0";
    string status_patient = "0";
    bool testing_or_not = false;
    bool transfer_hospital = false;
    double status_payment = -1;
    string follow_up_appointment = "0";

public:
    static long long set_id;
    // dành cho administrator KHÓ
    void set_data(); 

    void display() const;
  
    // dành cho doctor_general
    void update_data_general_doctor(double x);

    // void update_status_payment_doctor(){
    //     status_payment = -total_cost;
    // }
    // void update_result_record_doctor();
    // void update_is_delete(int x);
    // void display() const;
    // long long get_id() const { return id_checking; }
    // long long get_id_patient() const { return id_patient; }
    // long long get_id_doctor() const {return id_doctor;}
    // bool get_is_delete() const{return is_delete;}
    // string get_status_checking() const{return status_checking;}
    // void read_a_object_from_file(const string &line);
    // void write_a_object_to_file(ofstream &file);
};

#endif 
