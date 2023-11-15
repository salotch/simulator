#ifndef UNTITLED_CAR_H
#define UNTITLED_CAR_H
#include<string>
#include <vector>
#include <fstream>
#include <iostream>
#include<algorithm>
#include <cmath>
#include <regex>
using namespace std;
class machine
{
protected:
    int counter = 0;
    string name;
    vector <string> instruction;
public:
    machine(){
        return;
    }
    void set_file_name(string n);
    void load_store_in();
    bool check_valid();
};
class memory:public machine{
public:
    vector <string> memory_vector;
    memory()
    {
        for (int i = 0; i < 256; ++i) {
            memory_vector.emplace_back("00");
        }
    }
    void store_memory();
    int hexa_to_decimal(string c);
    string add(string c1,string s1);

};

class Register : public memory
{
public:
    vector <string> register_vector;
    Register(){
        for (int i = 0; i < 16; ++i) {
            register_vector.emplace_back("00");
        }
    }
};
class execute: public Register
{
public:
    execute(){
        return;
    }
    void executei();
    string execute2();
    void print();
};
#endif //SIMULATOR_IMP_H
