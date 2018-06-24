#include <iostream>
using namespace std;

template <class T>
class LE
{
public:
    T *tab;
    int size;
    LE *next;
};

template <class T>
class ArrayList
{
public:
    LE<T> *head;

    ArrayList()
    {
        head = nullptr;
    }

    ArrayList(const ArrayList &o1)
    {
        LE<T> *tmp = o1.head,*gdzie;

        if(tmp!= nullptr)
        {
            head=new LE<T>;
            head->size=tmp->size;
            head->tab=new T[head->size];
            head->next= nullptr;

            for(int i=0;i<head->size;i++)
            {
                head->tab[i]=tmp->tab[i];
            }

            gdzie=head;
            tmp=tmp->next;
        }

        while(tmp != nullptr)
        {
            LE<T> *node = new LE<T>;
            node->size=tmp->size;
            node->next= nullptr;
            node->tab= new T[node->size];

            for(int i=0;i<node->size;i++)
            {
                node->tab[i]=tmp->tab[i];
            }

            gdzie->next=node;
            gdzie=node;
            tmp=tmp->next;
        }
    }

    ~ArrayList()
    {
        LE<T> *nast,*node=head;

        if(head!= nullptr) {
            while (node != nullptr) {
                nast = node->next;

                delete [] node->tab;
                delete node;

                node = nast;
            }
            head = nullptr;
        }
    }

    void add(const T*t, int size)
    {
        LE<T> *node=head;
        LE<T> *tmp = new LE<T>;

        tmp->size=size;
        tmp->next= nullptr;
        tmp->tab = new T[size];

        for(int i=0;i<size;i++)
        {
            tmp->tab[i]=t[i];
        }

        if(head == nullptr)
            head=tmp;
        else
        {
            while(node->next!= nullptr)
            {
                node = node->next;
            }

            node->next=tmp;
        }

    }

    ArrayList &operator=(const ArrayList<T> &o1)
    {
        if(this==&o1)
            return *this;

        (*this).~ArrayList();

        LE<T> *tmp = o1.head,*gdzie;

        if(tmp!= nullptr)
        {
            head=new LE<T>;
            head->size=tmp->size;
            head->tab=new T[head->size];
            head->next= nullptr;

            for(int i=0;i<head->size;i++)
            {
                head->tab[i]=tmp->tab[i];
            }

            gdzie=head;
            tmp=tmp->next;
        }

        while(tmp != nullptr)
        {
            LE<T> *node = new LE<T>;
            node->size=tmp->size;
            node->next= nullptr;
            node->tab= new T[node->size];

            for(int i=0;i<node->size;i++)
            {
                node->tab[i]=tmp->tab[i];
            }

            gdzie->next=node;
            gdzie=node;
            tmp=tmp->next;
        }

        return *this;

    }

    void show()
    {
        LE<T> *node=head;
        while(node!= nullptr)
        {
            for(int i=0;i<node->size;i++)
            {
                cout << node->tab[i] << " ";
            }

            node = node->next;
        }
    }
};

int main() {
    ArrayList<int> o1;

    int tab[4]={1,5,12,69};
    int tab2[4]={1,5,12,19};
    o1.add(tab,4);
    o1.add(tab2,4);
    o1.show();

    ArrayList<int> o2(o1);

    cout << endl;
    o2.show();
    cout << endl;

    o1=o2;

    o1.show();
}