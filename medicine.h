#ifndef MEDICINE_H
#define MEDICINE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;


class Medicine
{
private:
    long long id_medicine;
    string name;
    string type;
    string usage;// công dụng
    string dosage;// số lượng dùng nhiều nhất trong một ngày
    string side_effects;// tác dụng phụ
    string warnings;// cảnh báo
    string NSX;
    int HSD; // month
    int quantity;
    double cost;// giá tiền trên một đơn vị đựng thuốc
    bool is_deleted = false;

public:
    static long long set_id;
    void set_data();
    void update_info();
    void display() const;
    void update_data();
    void update_quantity(int x){
      quantity += x;
    }
    void update_is_deleted();
    void update_is_recovered();

    void decrease_quantity();// khi kê đơn cho thì hệ thống tự động trừ quatity trong kho

    void read_a_object_from_file(const string &line);
    void write_a_object_to_file(ofstream &file);
   
    long long get_id() const { return id_medicine; }
    bool get_is_deleted() const {return is_deleted;}
    string get_name() const { return name; }
    int get_quantity()const { return quantity;}
};

#endif