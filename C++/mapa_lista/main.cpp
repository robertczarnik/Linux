#include <iostream>
using namespace std;

template<class T,class E>
class el
{
public:
    T first;
    E second;
    el<T,E> *next;

    el()
    {
        next=nullptr;
    }

};

template<class T,class E>
class MAPA 
{
public:
    el<T,E> *pierw;

    MAPA()
    {
        pierw=nullptr;
    }

    E &operator[](const T &o1) {
        el<T,E> *w, *wp, *wn;

        for (w = pierw, wp = nullptr; w != nullptr; w = w->next) {
            if (w->first == o1)
                return w->second;
            wp = w;
        }

        wn = new el<T,E>;
        wn->first = o1;
        wn->next = nullptr;

        if (wp == nullptr)
        {
            pierw = wn;
        }
        else {
            wp->next = wn;
            return wn->second;
        }
    }

/*
    
    class iteratorek {
    public:
        el<E, T> *ws;

        int operator!=(const iteratorek &o1) {
            if (ws != o1.ws) return 1;
            return 0;
        }

        iteratorek &operator++(int) {
            ws = ws->next;
            return *this;
        }

        el<T, E> *operator->() {
            return ws;
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
    }*/
};


int main() {
    MAPA <string,string> m;

    m["aa"]="bb";
    m["cc"]="dd";
    //cout << m["aa"];
}