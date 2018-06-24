#include <iostream>
using namespace std;

int f2(){
    int o1=0,c;
    string o2="tekst bledu";

    throw o2;

    return c;
}

int f1(){
    int b;
    b=f2();
    return b;
}


int main() {

    int a;

    try{

        a=f1();
        cout << a << endl;

    }catch(int o1){
        cout << "blad" << endl;
    }catch (string &o2)
    {
        cout << o2 << endl;
    }


    return 0;
}