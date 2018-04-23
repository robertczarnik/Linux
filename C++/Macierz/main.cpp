#include <iostream>
#include "macierz.h"
using namespace std;

int main() {
    Macierz a,b,c1,c2,c3,d(3),e(2,7);
    cin>>a>>b;
    Macierz kopia(a);
    c1=a+b;
    c2=a-b;
    c3=a*b;

    cout << endl;
    cout << "konstruktor kopiujacy obiekt a:" << endl << kopia <<endl;
    cout << "konstruktor wypelniajacy zerami:" << endl << d <<endl;
    cout << "konstruktor wypelniajacy zadana liczba:" << endl << e <<endl;
    cout << "a=a:" << endl << (a=a) <<endl;


    cout << "c1=a+b:" << endl << c1 <<endl;
    cout << "c2=a-b:" << endl << c2 <<endl;
    cout << "c3=a*b:" << endl << c3 <<endl;
    cout << "a==b: " << (a==b) << endl;
    cout << "a!=b: " << (a!=b) << endl;
    cout << "a<b: " << (a<b) << endl;
    cout << "a<=b: " << (a<=b) << endl;
    cout << "a>b: " << (a>b) << endl;
    cout << "a>=b: " << (a>=b) << endl;
}