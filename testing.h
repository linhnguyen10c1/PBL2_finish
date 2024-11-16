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
   long long id_doctor2;
   string type;
   //string imagine;

   public:
   void display() const;
   void set_data(long long id_checking, const string &type, int priority);
   void update_data();

   void read_a_object_from_file(const string &line);
   void write_a_object_to_file(ofstream &file);
};
#endif