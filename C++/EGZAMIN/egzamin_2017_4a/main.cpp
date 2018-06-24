#include <iostream>
using namespace std;

class A
{
public:
    virtual void f(){
        printf("A.f ");
    }

    A(){
        f();
    }

    ~A(){
        printf("~A.f ");
    }
};

class B : public A{
public:
    A *a;
    void f(){
        printf("B.f ");
    }

    B(A*a=0){
        f();
        this->a=a;
    }

    ~B(){
        printf("~B.f ");
        if(a)
            delete a;
    }
};

B b;

int main()
{

    A *a = new B(new A());
    printf("M ");
    delete a;

    // A.f B.f A.f A.f B.f M ~A.f ~B.f ~A.f
    return 0;
}