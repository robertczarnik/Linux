#include <iostream>
using namespace std;

template <typename key,typename value>
class MAP; // declaration

template <typename key,typename value>
class Element
{
    friend class MAP<key,value>;
public:

    Element<key,value>  * up;
    Element<key,value>  * left;
    Element<key,value>  * right;


    char color;
    key first;
    value second;
};

template <typename key,typename value>
class MAP
{
public:
    Element<key,value> S{}; //strażnik
    Element<key,value> *root;

    MAP()
    {
        S.color = 'B';
        S.up    = &S;
        S.left  = &S;
        S.right = &S;
        root    = &S;
    }

    ~MAP()
    {
        DFSRelease(root);
    }

    void DFSRelease(Element<key,value> *p)
    {
        if(p != &S)
        {
            DFSRelease(p->left);
            DFSRelease(p->right);
            delete p;
        }
    }

    Element<key,value>* find(int k)
    {
        Element<key,value> *p;

        p = root;
        while((p != &S) && (p->first != k))
            if(k < p->first)
                p = p->left;
            else
                p = p->right;

        if(p == &S) return nullptr;
        return p;
    }

    void rot_L(Element<key,value> * A)
    {
        Element<key,value> * B, * p;

        B = A->right;
        if(B != &S)
        {
            p = A->up;
            A->right = B->left;
            if(A->right != &S) A->right->up = A;

            B->left = A;
            B->up = p;
            A->up = B;

            if(p != &S)
            {
                if(p->left == A) p->left = B; else p->right = B;
            }
            else root = B;
        }
    }

    void rot_R(Element<key,value> * A)
    {
        Element<key,value> * B, * p;

        B = A->left;
        if(B != &S)
        {
            p = A->up;
            A->left = B->right;
            if(A->left != &S) A->left->up = A;

            B->right = A;
            B->up = p;
            A->up = B;

            if(p != &S)
            {
                if(p->left == A) p->left = B; else p->right = B;
            }
            else root = B;
        }
    }

    Element<key,value>* insert(const key &k)
    {
        Element<key,value> * X, * Y;

        X = new Element<key,value>;        // Tworzymy nowy węzeł
        X->left  = &S;          // Inicjujemy pola
        X->right = &S;
        X->up    = root;
        X->first   = k;
        if(X->up == &S) root = X; // X staje się korzeniem
        else
            while(true)             // Szukamy liścia do zastąpienia przez X
            {
                if(k < X->up->first)
                {
                    if(X->up->left == &S)
                    {
                        X->up->left = X;  // X zastępuje lewy liść
                        break;
                    }
                    X->up = X->up->left;
                }
                else
                {
                    if(X->up->right == &S)
                    {
                        X->up->right = X; // X zastępuje prawy liść
                        break;
                    }
                    X->up = X->up->right;
                }
            }
        X->color = 'R';         // Węzeł kolorujemy na czerwono
        while((X != root) && (X->up->color == 'R'))
        {
            if(X->up == X->up->up->left)
            {
                Y = X->up->up->right; // Y -> wujek X

                if(Y->color == 'R')  // Przypadek 1
                {
                    X->up->color = 'B';
                    Y->color = 'B';
                    X->up->up->color = 'R';
                    X = X->up->up;
                    continue;
                }

                if(X == X->up->right) // Przypadek 2
                {
                    X = X->up;
                    rot_L(X);
                }

                X->up->color = 'B'; // Przypadek 3
                X->up->up->color = 'R';
                rot_R(X->up->up);
                break;
            }
            else
            {                  // Przypadki lustrzane
                Y = X->up->up->left;

                if(Y->color == 'R') // Przypadek 1
                {
                    X->up->color = 'B';
                    Y->color = 'B';
                    X->up->up->color = 'R';
                    X = X->up->up;
                    continue;
                }

                if(X == X->up->left) // Przypadek 2
                {
                    X = X->up;
                    rot_R(X);
                }

                X->up->color = 'B'; // Przypadek 3
                X->up->up->color = 'R';
                rot_L(X->up->up);
                break;
            }
        }
        root->color = 'B';
        return X;
    }
    
    value& operator[](const key &o1)
    {
        Element<key,value> *nowy,*last=nullptr;
        Element<key,value> *wsk=root;

        while((wsk != &S) && (wsk->first != o1))
            if(o1 < wsk->first)
                wsk = wsk->left;
            else
                wsk = wsk->right;

        if(wsk != &S)
        {
            cout << "znalazalem";
            return wsk->second;

        }



        if(root == &S)
        {
            root->first=o1;
            return root->second;
        }
        else
        {
            nowy = this->insert("lolo");
        }
        cout << "nowy: " << nowy << endl;
        return  nowy->second;

    }

    /*
    class iteratorek
    {
    public:
        Element<key,value> *wsk;

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

        Element<key, value> *operator->() {
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
    }*/

};

int main()
{
    MAP <string,string> m;

    m["aa"]="kaszka";
    m["bb"]="BOBI";
    cout << m["bb"];
    /*string s1;
    s1=m["zz"];
    s1=m["gf"];
    m["sznycel"]="dobra szamowa";
    m["cc"]="kappa";

    for(MAP<string,string>::iteratorek i=m.begin();i!=m.end();i++)
    {
        cout << i->first << " " << i->second << endl;
    }*/

}