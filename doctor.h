#ifndef DOCTOR_H
#define DOCTOR_H
#include "person.h"

class Doctor :public Person {
private:
    string specialization;
    string room;
    int experience_year;
    int patients_waiting = 0;
    double price;

public:
    static long long set_id;
    void set_data();
    void display() const;
    void update_info();
    void update_data();
    void update_patients_waiting(const string &modify);
     

    void read_a_object_from_file(const string &line);
    void write_a_object_to_file(ofstream &file);

    int get_waiting() const { return patients_waiting; }
    string get_specialization()const{return specialization;}
    string get_room()const{return room;}
    double get_price()const{return price;}

};

#endif