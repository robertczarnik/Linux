#include <iostream>
using namespace std;
class A
{
public:
    virtual void f(int i){
        printf("A.f:%d ",i);
    }

    A(int i){f(i);}
    ~A(){f(5);}
};

class B : public A
{
public:
    void f(int i){
        printf("B.f:%d ",i);
    }

    B(int i=0):A(-1){
        if(i<0) throw 0;
        else f(i);
    }
};

B b;

int main() {
    try{
        A *a = new B(-2);
        a->f(1);
    }catch(int e){
        printf("Exc ");
    }

    return 0;

    // A.f:-1 B.f:0 A.f:-1 A.f:5 Exc A.f:5
}