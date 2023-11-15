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
        string g=s.substr(2,1)+s.substr(5,1)+s.substr(8,2);
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
int memory::hexa_to_decimal(string c)
{
    string binary;//to store number in binary
    string b2 ;//will store half binary num
    string b3;//will store another half number
    string A_F="ABCDEF"; // the benefit from this string to check if the char not num
    int k,d,decimal;//k is the char that will be transform,d is store the diff size to complete missing by zero/decimal to store decimal num
    int flag=0;// boolean that mean if it is =1 that char is character not num
    for(int i=0;i<2;i++) {
        flag=0;
        for (int j = 0; j < 7; j++){
            if (c[i] == A_F[j]) {
                k = j + 10;//to make k= 10 or 11 or 12.....
                flag = 1;
            }
        }
        if(flag==0)
            k=c[i]-'0';
        if(i==0) {
            while (k != 0) {
                b2 += to_string(k % 2);
                k /= 2;
            }
            reverse(b2.begin(),b2.end());// reverse bec when we transform it wriiten for ex 01 and I want it 10
            d=4-b2.size();
            for(int i=0;i<d;i++)
            {
                b2="0"+b2;
            }
        }
        else
        {
            while (k != 0) {
                b3 += to_string(k % 2);
                k /= 2;
            }
            reverse(b3.begin(),b3.end());
            d=4-b3.size();
            for(int i=0;i<d;i++)
            {
                b3="0"+b3;
            }
        }

    }
    binary=b2+b3;// we do b2 and b3 to make each of them 4bite and after we add become 8
    for(int k=7;k>=0;k--)
    {
        decimal+=((binary[k]-'0')*pow(2,7-k));
    }
    return decimal;
}
void execute::executei() {
    for(int counter=0;counter<256;counter++) {
        string s = memory_vector[counter];
        counter++;
        if (s[0] == '2') {
            register_vector[s[1] - '0'] = memory_vector[counter];
        }
        if (s[0] == '3') {
            cout<<memory_vector[counter]<<endl<<endl<<endl;
            int l = hexa_to_decimal(memory_vector[counter]);

            memory_vector[l] = register_vector[s[1] - '0'];
        }

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