#include "imp.cpp"
using namespace std;
int main()
{string s;
//cout<<"Welcome to Machine Language Simulator!\n";
//cout<<"Enter File Instruction Name :";
//cin>>s;
execute h;
    h.set_file_name("saloka");
    h.load_store_in();
    if(h.check_valid())
        return 0;
    h.store_memory();
    h.executei();
    h.print();
    cout<<"Counter is Equal to :"<<hex<<h.counter+1;
    return 0;
}