#ifndef PATIENT_H
#define PATIENT_H
#include "person.h"
class Patient : public Person
{
private:
    string allergy;
    string phone_family;

public:
    static long long set_id;
    void set_data();
    void display() const;
    void update_info();
    void update_data();
    void read_a_object_from_file(const string &line);
    void write_a_object_to_file(ofstream &file);
    
};

#endif