#include "imp.cpp"
using namespace std;
int main(){
    execute h;
    h.set_file_name("saloka");
    h.load_store_in();
    h.store_memory();
    h.executei();
    h.print();

    return 0;
}