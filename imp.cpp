#include "imp.h"

void machine::set_file_name(string n) {
    name=n;
}
void machine :: load_store_in()
{
    ifstream file(name);
    for(int i=0;!file.eof();++i){
        string s;
        file>>s;
        string g=s.substr(2,1)+s.substr(5,1)+s.substr(8,1)+s.substr(11,1);;
        instruction.push_back(g);
    }
}
void memory::store_memory() {
    for(int i=0,j=0;instruction.size()>i;i++,j++){
        string s;
        s=instruction[i];
        memory_vector[j]=s.substr(0,2);
        j++;
        memory_vector[j]=s.substr(2,2);
    }
}
void execute::executei() {
    string s=memory_vector[counter];
    counter++;
    if(s[0]=='2') {
        register_vector[s[1]-'0'] = execute2();
        counter++;
    }
}
string execute::execute2() {
    return memory_vector[counter];
}

void execute::print() {
    for (int i = 0; i < memory_vector.size(); ++i) {
        cout<<memory_vector[i]<<endl;
    }
    cout<<" register               \n";
    for (int i = 0; i < register_vector.size(); ++i) {
        cout<<register_vector[i]<<endl;
    }

}