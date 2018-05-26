#include <iostream>
using namespace std;

template <typename key,typename value>
class MAP_LIST; // declaration

template <typename key,typename value>
class Element2
{
    friend class MAP_LIST<key,value>;
    Element2<key,value> *next;

    Element2()
    {
        next = nullptr;
    }

public:
    key first;
    value second;
};

template <typename key,typename value>
class MAP_LIST
{
public:
    Element2<key,value> *head;

    MAP_LIST()
    {
        head = nullptr;
    }

    ~MAP_LIST()
    {
        Element2<key,value> *node=head;

        while(node != nullptr)
        {
            Element2<key,value> *tmp = node->next;
            delete node;
            node=tmp;
        }

        head = nullptr;
    }

    value& operator[](const key &o1)
    {
        Element2<key,value> *nowy,*wsk=head,*last=nullptr;

        for(;wsk!=nullptr; wsk=wsk->next)
        {
            if(wsk->first==o1)
            {
                return wsk->second;
            }
            last=wsk;
        }

        nowy = new Element2<key,value>;
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
    public:
        Element2<key,value> *wsk;

        iteratorek()
        {
            wsk = nullptr;
        }

        bool operator!=(const iteratorek &o1) {
            return wsk != o1.wsk;
        }

        iteratorek &operator++(int) {
            wsk = wsk->next;
            return *this;
        }

        Element2<key, value> *operator->() {
            return wsk;
        }

    };

    iteratorek begin()
    {
        iteratorek i;
        i.wsk = head;
        return i;
    }

    iteratorek end()
    {
        iteratorek i;
        i.wsk = nullptr;
        return i;
    }

};

int main()
{
    MAP_LIST <string,string> m;

    m["aa"]="bb";
    m["cc"]="dd";
    string s1;
    s1=m["zz"];
    s1=m["gf"];
    m["sznycel"]="dobra szamowa";
    m["cc"]="kappa";

    //cout << m.begin()->second << endl;


    for(MAP_LIST<string,string>::iteratorek i=m.begin();i!=m.end();i++)
    {
        cout << i->first << " " << i->second << endl;
    }

}