#include <iostream>
using namespace std;

class A{
public:
    virtual void f() {
        printf("~A.f ");
    }

    virtual ~A(){
        f();
    }
};

class B :public A{
public:
    A a;
    void f(){
        printf("~B.f ");
    }

    B(int k=0){
        if(k<0)
            throw 0;
    }

    ~B(){
        f();
    }
};

B b;

int main() {
    try{
        A *ptr=new B(-1);
        delete ptr;
    }catch(int o1)
    {
        printf("Esc ");
    }

    return 0;
}