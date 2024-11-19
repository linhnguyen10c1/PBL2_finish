#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <random>

using namespace std;
// Base class for common person attributes
class Person {
protected:
    long long ID;
    string name;
    string password = generate_random_password(5);
    string birthday;
    string gender;
    string address;
    string email;
    string phone;
    bool is_deleted = false;
public:
    static string generate_random_password(int length);
    
    void set_data();
    
    long long get_id() const {return ID;}
    string get_password() const {return password;}
    bool get_is_deleted() const{return is_deleted;}
   
    // cập nhật thông tin cá nhân + mật khẩu
    void update_password();
    void update_is_deleted();
    void update_is_recovered();

    void display_for_out_person() const;
};

#endif