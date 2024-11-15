#ifndef CHECKING_H
#define CHECKING_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

class Checking {
protected:
    long long id_doctor;
    long long id_checking;
    /*phải xem xét có khẩn cấp không, và xem danh sách đợi của bác
    sĩ để mà phân luông người khám ra sao*/
    bool urgent;
    // sau khi phân luồng sẽ cho thông tin bác sĩ khám
    string room;
    string status_checking = "waiting";// waiting, processing, completed
    string start_checking = "0";
    string end_checking ="0";
    /* nếu bác sĩ lâm sàng kết quả khám cuối cùng
    nếu là bác sĩ cận lâm sàng kết quả testing*/
    string final_result = "0";

    string doctor_note = "0";
    double cost = 0;
    bool is_deleted = false;

public:
    static long long set_id;
    void display() const;
    

    long long get_id() const {return id_checking;}
    long long get_id_doctor() const {return id_doctor;}
    string get_status_checking() const {return status_checking;}
    bool get_is_deleted() const{return is_deleted;}
    double get_cost() const{return cost;}
    
    // dành cho người dùng là manager
    void update_data(){ cout << "You are not allowed to update main data in record" << endl;}
    void update_is_deleted(){is_deleted = true;}
    void update_is_recovered(){is_deleted = false;}

    // dành cho bác sĩ
  

};

#endif 
