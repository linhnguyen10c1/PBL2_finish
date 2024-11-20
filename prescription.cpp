#include "prescription.h"
#include <sstream>
#include <stdexcept>


// Hàm thiết lập dữ liệu
void Prescription::set_data(long long ID_checking, long long ID_medicine, int quantity, const string &instruction, LinkedList<Medicine> &medicine_list) {
    this->ID_checking = ID_checking;
    this->ID_medicine = ID_medicine;
    this->quantity = quantity;
    this->instruction = instruction;

    Node<Medicine>* current = medicine_list.get_head();
    while (current != nullptr) {
        if (current->data.get_id() == ID_medicine) {
            // Giảm số lượng thuốc trong danh sách
            if (current->data.get_quantity() >= quantity) {
                current->data.decrease_quantity(quantity);
                this->price = current->data.get_price();
                this->function = current->data.get_function();
            } else {
                throw runtime_error("Not enough medicine in stock.");
            }
            break;
        }
        current = current->next;
    }

    if (current == nullptr) {
        throw runtime_error("Medicine ID not found.");
    }
}

// Hàm hiển thị thông tin
void Prescription::display() const {
    cout << "Prescription Details:" << endl;
    cout << "ID Checking: " << ID_checking << endl;
    cout << "ID Medicine: " << ID_medicine << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Cost: " << price << endl;
    cout << "Instruction: " << instruction << endl;
    cout << "Function: " << function << endl;
}

// Hàm đọc một đối tượng từ file
void Prescription::read_a_object_from_file(const string &line) {
    stringstream ss(line);
    ss >> ID_checking >> ID_medicine >> quantity >> price;
    ss.ignore();
    getline(ss, instruction, ';');
    getline(ss, function);
}

// Hàm ghi một đối tượng vào file
void Prescription::write_a_object_to_file(ofstream &file) const {
    file << ID_checking << "," << ID_medicine << "," << quantity << "," << price << ","
         << instruction << "," << function << endl;
}
