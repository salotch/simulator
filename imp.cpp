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
bool machine :: check_valid() {
    for (int i = 0; i < instruction.size(); ++i) {

        if (!regex_match(instruction[i], regex("^[1-5BC][0-9A-F]*")))
        {
            cout << "There is Invalid Instruction";
            return true;
        }
    }
    return false;
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
string memory:: add(string c1,string s1)
{
    int c=0;
    string n1=c1;
    string n2=s1;
    string s,A_F={"ABCDEF"};// the sum, and hexadecimal numbers
    for(int k=1;0<=k;k--)//just 2 digits to neglect the overflow
    {
        int x=0,y=0,l=0;
        if(n1[k]>=48&&n2[k]<=57)
            x=n1[k]-'0';//to convert the string to int
        if(n2[k]>=48&&n2[k]<=57)//to convert the string to int
            y=n2[k]-'0';
        for (int j = 0; j < 7; j++){
            if (n1[k] == A_F[j]) {
                x = j + 10;//to make k= 10 or 11 or 12...
            }
        }
        for (int j = 0; j < 7; j++){
            if (n2[k] == A_F[j]) {
                y = j + 10;//to make k= 10 or 11 or 12...
            }
        }
        l=x+y+c;
        if(l >= 16)//to save the carry
        {
            l -= 16;
            c = 1;
        }
        for(int j=0;j<7;j++)//this loop to give every number his value in hexadecimal
            if(l==10+j)
                s+=A_F[j];
        if(l<10)
            s+= to_string(l);

    }
    reverse(s.begin(), s.end());//the data was stored reversed
    return s;
}
int memory::hexa_to_decimal(string c)
{
    string binary;//to store number in binary
    string b2 ;//will store half binary num
    string b3;//will store another half number
    string A_F="ABCDEF"; // the benefit from this string to check if the char not num
    int k,d,decimal=0;//k is the char that will be transform,d is store the diff size to complete missing by zero/decimal to store decimal num
    int flag;// boolean that mean if it is =1 that char is character not num
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
            for(int j=0;j<d;j++)
            {
                b2="0"+b2;
            }
        }
        else if(i==1)
        {
            while (k != 0) {
                b3 += to_string(k % 2);
                k /= 2;
            }
            reverse(b3.begin(),b3.end());
            d=4-b3.size();
            for(int j=0;j<d;j++)
            {
                b3="0"+b3;
            }
        }
    }
    binary=b2+b3;// we do b2 and b3 to make each of them 4bite and after we add become 8
    for(int j=7;j>=0;j--)
    {
        decimal+=( (binary[j]-'0')*pow(2,7-j) );
    }
    return decimal;
}
void execute::executei() {
    for(counter=0;counter<256;counter++) {
        string s = memory_vector[counter];
        counter++;
        if (s[0] == '1') {
            int  decimal_value=hexa_to_decimal(memory_vector[counter]) ;
            register_vector[s[1] - '0'] = memory_vector[decimal_value];
        }// this code if the first char ==1 will make the contest of the certain adress to be accessed and saved in memory that specified

        else if (s[0] == '2') {
            register_vector[s[1] - '0'] = execute2();
        }
        else if (s[0] == '3') {
            string k=memory_vector[counter];
            int l = hexa_to_decimal(k);
            memory_vector[l] = register_vector[s[1] - '0'];
        }
        else if (s[0] == '4') {
            register_vector[s[3] - '0'] =register_vector[s[2] - '0'] ;
        }//this code saves the contests of the seccond register to the first register

        else if (s[0]=='5') {
            string k = memory_vector[counter];
            register_vector[s[1] - '0'] = add(register_vector[k[0] - '0'], register_vector[k[1] - '0']);
        }
        else if (s[0]=='B') //B mean that we want to jump and escape from another instruction if the condition is satisfied
        {
            if(register_vector[s[1] - '0']==register_vector[0]) { //check the code if it is satisfied
                string k=memory_vector[counter];
                int l = hexa_to_decimal(k);
                counter = l-1;//that make the jump
            }
        }

        else if (s[0]=='C' && s[1]=='0' && memory_vector[counter]=="00" )
            break;
    }
}
string execute::execute2() {
    return memory_vector[counter];
}

void execute::print() {
    cout<<"Memory content:               \n";
    for (int i = 0; i < memory_vector.size(); ++i) {
        if(i<10)
            cout<<"0"<<i;
        else
            cout<<hex<<uppercase<<i;
        cout<<" : "<<memory_vector[i]<<endl;
    }
    cout<<"Register content:               \n";
    for (int i = 0; i < register_vector.size(); ++i) {
        if(i<10)
            cout<<"0"<<i;
        else
          cout<<"0"<<hex<<uppercase<<i;
        cout<<" : "<<register_vector[i]<<endl;
    }
}