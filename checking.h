#ifndef CHECKING_H
#define CHECKING_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include "linklist.h"
#include "doctor.h"

using namespace std;

void update_patients_waiting_in_list(long long ID_doctor, const string &modify);

class Checking {
protected:
    long long id_doctor;
    long long id_checking;
    
    /*phải xem xét có khẩn cấp không, và xem danh sách đợi của bác
    sĩ để mà phân luông người khám ra sao*/
    int priority = 0;
    // sau khi phân luồng sẽ cho thông tin bác sĩ khám
    string room = "0";
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
    string get_date() const {return start_checking;}
    
    // dành cho người dùng là manager
    void update_data(){ cout << "You are not allowed to update main data in record" << endl;}
    // chỉ được xóa giai đoạn đầu thôi, sau khi bác sĩ ghi vào rồi thì không được xóa nữa
    void update_is_deleted(){
        if(start_checking == "0"){
            is_deleted = true;
            update_patients_waiting_in_list(get_id_doctor(), "decreasing");
            }
        else {
            cout << "You don't allow delete when doctor is updating data" << endl;
        }

    // chỉ được phục hồi khi bản ghi đã hòan thành
    // còn mới ghi vào thì chỉ có xóa luôn, muốn khám lại
    // chỉ còn cách ID mới, vì bác sĩ được ghi trước đó số người đợi đã khác
    }

    void update_is_recovered() {
        if(end_checking != "0"){
        is_deleted = false;
        }
        else {
            cout << "You nedd new record, can't recover" << endl;
        }
    }
    void update_start_day();
    void update_end_day();

    // dành cho bác sĩ
  

};


#endif 
