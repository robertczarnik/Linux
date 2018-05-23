#include <iostream>
#include <map>
using namespace std;

template <typename key,typename value>
class Element
{
public:
    key first;
    value second;
    Element<key,value> *next;

    Element()
    {
        next = nullptr;
    }
};

template <typename key,typename value>
class MAP
{
public:
    Element<key,value> *head;

    MAP()
    {
        head = nullptr;
    }

    value& operator[](const key &o1)
    {
        Element<key,value> *nowy,*wsk=head,*last=nullptr;

        for(;wsk!=nullptr; wsk=wsk->next)
        {
            if(wsk->first==o1)
            {
                return wsk->second;
            }
            last=wsk;
        }

        nowy = new Element<key,value>;
        nowy->first=o1;
        nowy->next = nullptr;

        if(head == nullptr)
        {
            head=nowy;
        }
        else if(last != nullptr)
        {
            last->next=nowy;
        }

        return  nowy->second;
    }

    class iteratorek
    {
        Element<key,value> *wsk;

        int operator!=(const iteratorek &o1) {
            if (ws != o1.wsk) return 1;
            return 0;
        }

        iteratorek &operator++(int) {
            wsk = wsk->next;
            return *this;
        }

        Element<key, value> *operator->() {
            return wsk;
        }

    };

    iteratorek begin()
    {
        iteratorek i1{};
        i1.ws = pierw; // przy end =0;
        return i1;
    }

    iteratorek end()
    {
        iteratorek i1;
        i1.ws = nullptr; // przy end =0;
        return i1;
    }

};

int main()
{
}