#ifndef TESTING_H
#define TESTING_H

#include "linklist.h"
#include "checking.h"
#include <iostream>
#include <string>
#include "record.h"

using namespace std;

class Testing :public Checking{
   private:
   long long id_doctor2 = 0;
   string type;
   string part_of_body_need_test;
   bool is_having_another_testing = true;
   double cost;
   //string imagine;

   public:
   void display() const;
   void set_data(long long id_checking, const string &type, int priority, const string &part_body);
   //dùng để cập nhật kết quả từ bác sĩ cận lâm sàn
   void update_data();

   void update_data_have_another_testing(){
      is_having_another_testing = false;
   }
   bool get_is_having_another_testing(){
      return is_having_another_testing;
   }
   void check_condition_doctor(const string &type);
   void read_a_object_from_file(const string &line);
   void write_a_object_to_file(ofstream &file);

};
#endif