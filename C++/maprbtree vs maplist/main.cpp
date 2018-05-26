#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

template <typename key,typename value>
class MAP_LIST;

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

template <typename key,typename value>
class MAP; // declaration

template <typename key,typename value>
class Element
{
    friend class MAP<key,value>;
public:
    Element<key,value>  *parent;
    Element<key,value>  *left;
    Element<key,value>  *right;
    char colour;

    Element()
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        colour = 'B';
    }

public:
    key first;
    value second;
};

template <typename key,typename value>
class MAP
{
public:
    Element<key,value> *root;

    MAP()
    {
        root= nullptr;
    }

    ~MAP()
    {
        DeleteNode(root);
    }

    void DeleteNode(Element<key,value> *node)
    {
        if (!node)
        {
            return;
        }

        if (node->left)
        {
            DeleteNode(node->left);
        }

        if (node->right)
        {
            DeleteNode(node->right);
        }

        delete node;
    }

    void RotateLeft(Element<key,value> *x) //OK
    {
        Element<key,value> *y;

        y = x->right;
        x->right = y->left;
        if (y->left)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;
        y->left = x;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        x->parent = y;
    }

    void RotateRight(Element<key,value> *y)
    {
        Element<key,value>  *x;

        x = y->left;
        y->left = x->right;
        if (x->right)
        {
            x->right->parent = y;
        }

        x->parent = y->parent;
        x->right = y;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }

        y->parent = x;
    }

    Element<key,value>* insert(const key &o1)
    {
        Element<key,value> *Z;
        Z = new Element<key,value>;
        Z->first = o1;

        Element<key,value> *y = nullptr;
        Element<key,value> *x = root;
        while (x != nullptr) {
            y = x;
            if (Z->first < x->first)
                x = x->left;
            else
                x = x->right;
        }
        Z->parent = y;
        if (y == nullptr)
            root = Z;
        else if (Z->first < y->first)
            y->left = Z;
        else
            y->right = Z;

        Z->colour = 'R';
        Element<key,value> *wynik=Z;

        while((Z != root) && (Z->parent->colour == 'R'))
        {//cout << "hi" << endl;
            if(Z->parent == Z->parent->parent->left)
            {

                Element<key,value> *uncle = Z->parent->parent->right; // Y -> wujek X
                if(uncle)
                {
                    if (uncle->colour == 'R')  // Przypadek 1
                    {
                        //cout << "Z-first_przyp1 " << Z->first << endl;
                        Z->parent->colour = 'B';
                        uncle->colour = 'B';
                        Z->parent->parent->colour = 'R';
                        Z = Z->parent->parent;
                        continue;
                    }
                }

                if(Z == Z->parent->right) // Przypadek 2
                {
                    //cout << "Z-first_przyp2 " << Z->first << endl;
                    Z = Z->parent;
                    RotateLeft(Z);
                }

                Z->parent->colour = 'B'; // Przypadek 3
                Z->parent->parent->colour = 'R';
                RotateRight(Z->parent->parent);
                break;
            }
            else
            {                  // Przypadki lustrzane
                Element<key,value> *uncle = Z->parent->parent->left;

                if(uncle)
                {
                    if (y->colour == 'R') // Przypadek 1
                    {
                        //cout << "Z-first_przyp1_lust " << Z->first << endl;
                        Z->parent->colour = 'B';
                        y->colour = 'B';
                        Z->parent->parent->colour = 'R';
                        Z = Z->parent->parent;
                        continue;
                    }
                }

                if(Z == Z->parent->left) // Przypadek 2
                {
                    Z = Z->parent;
                    RotateRight(Z);
                }
                //cout << "obracanko" << endl;
                Z->parent->colour = 'B'; // Przypadek 3
                Z->parent->parent->colour = 'R';
                RotateLeft(Z->parent->parent);
                break;
            }
        }

        root->colour = 'B';
        return wynik;
    }

    value& operator[](const key &o1)
    {
        Element<key,value> *nowy,*wsk=root;

        while((wsk != nullptr) && (wsk->first != o1))
        {
            if(o1 < wsk->first)
            {
                wsk = wsk->left;
                //cout << "left" << endl;
            }
            else
            {
                wsk = wsk->right;
                //cout << "right" << endl;
            }
        }

        if(wsk != nullptr) //znaleźliśmy ten index
        {
            return wsk->second;
        }

        nowy = this->insert(o1); //wstawienie elementu do drzewa i zwrócenie jego miejsca w pamięci
        return  nowy->second;
    }

    class iteratorek
    {
    public:
        Element<key,value> *wsk;

        iteratorek()
        {
            wsk = nullptr;
        }

        Element<key,value>* successor(Element<key,value> *p)
        {
            Element<key,value> *r;
            if(p !=nullptr)
            {
                if(p->right != nullptr)
                {
                    r=p->right;
                    if(r->left != nullptr)
                        while(r->left != nullptr)
                        {
                            r = r->left;
                        }

                    return r;
                }
                else
                {
                    r = p->parent;
                    while((r !=nullptr) && (p == r->right))
                    {
                        p = r;
                        r = r->parent;
                    }

                    return r;
                }
            }

            return nullptr;
        }

        bool operator!=(const iteratorek &o1)
        {
            return wsk != o1.wsk;
        }

        iteratorek &operator++(int)
        {
            wsk = successor(wsk); // następnik
            return *this;
        }

        Element<key, value> *operator->()
        {
            return wsk;
        }
    };

    iteratorek begin()
    {
        iteratorek i;
        i.wsk=root;

        while(i.wsk->left != nullptr) // szukam poczatku drzewa
        {
            i.wsk = i.wsk->left;
        }

        return i;
    }

    iteratorek end()
    {
        iteratorek i;
        i.wsk = nullptr; // zakończenie drzewa w przechodzeniu następnikiem
        return i;
    }
};


int main() {
    MAP<int, int> m_rbtree;
    MAP_LIST<int, int> m_list;



    auto start = chrono::system_clock::now();
    for (int i = 1; i < 100000; i++) {
        m_rbtree[i] = i;
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "czas rbtree: " << elapsed_seconds.count() << "s" << endl;



    start = chrono::system_clock::now();
    for (int i = 1; i < 100000; i++) {
        m_list[i] = i;
    }
    end = chrono::system_clock::now();
    elapsed_seconds = end-start;
    cout << "czas list: " << elapsed_seconds.count() << "s" << endl;

}