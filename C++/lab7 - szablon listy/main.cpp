#include <iostream>
#include "linked_list_template.h"
#include "macierz.h"
using namespace std;

int main()
{
    List<Macierz> a,b,c;

    cin >> a >> a >> a;
    cin >> b >> b;


    List<Macierz> d(b);
    c=a+b;
    c=a+b;
    c=a+b;

    cout << "List a: " << a << endl;
    cout << "List b: " << b << endl;
    cout << "Copy of b: " << d << endl;
    cout << "a=a:"<< (a=a) << endl;
    cout << "c=a+b:" << c << endl;
    /*cout << "a==b: " << (a==b) << endl;
    cout << "a!=b: "<< (a!=b) << endl;
    cout << "a=b:" << (a=b) << endl;*/

    //cout << "a+b+c" << (a+b+c) << endl;
    // 1 2 2 1 1 1 1 3 1 2 1 2 1 2 3 2 1 1 2 2 12 2 1 23
}