#include "imp.cpp"
using namespace std;
int main()
{string s;
cout<<"Welcome to Machine Language Simulator!\n";
cout<<"Enter File Instruction Name :";
cin>>s;
bool valid;
execute h;
do{valid=true;
    h.set_file_name(s);
    h.load_store_in();
    if(h.check_valid())
    {  cout<<"Edit Instruction in The File!";
        valid=false;
    }
}while(!valid);
    h.store_memory();
    h.executei();
    h.print();

    return 0;
}