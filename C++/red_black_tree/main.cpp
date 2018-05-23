#include <iostream>
using namespace std;

class RBNode
{
public:
    RBNode * up;
    RBNode * left;
    RBNode * right;
    int key;
    char color;
};

class RBTree
{
private:
    RBNode S{};             // Węzeł strażnika
    RBNode * root;        // Korzeń drzewa czerwono-czarnego

public:
    RBTree();             // Konstruktor klasy
    ~RBTree();            // Destruktor klasy
    void DFSRelease(RBNode * p); // Usuwa rekurencyjnie drzewo
    RBNode * findRBT(int k); // Wyszukuje węzeł o kluczu k
    RBNode * succRBT(RBNode * p);// Wyszukuje następnik p
    void rot_L(RBNode * A); // Rotacja w lewo względem A
    void rot_R(RBNode * A); // Rotacja w prawo względem A
    void insertRBT(int k);   // Wstawia węzeł o kluczu k
};

RBTree::RBTree()
{
    S.color = 'B';          // Inicjujemy strażnika
    S.up    = &S;
    S.left  = &S;
    S.right = &S;
    root    = &S;           // Korzeń wskazuje strażnika
}

RBTree::~RBTree()
{
    DFSRelease(root);
}

void RBTree::DFSRelease(RBNode * p)
{
    if(p != &S)
    {
        DFSRelease(p->left);   // usuwamy lewe poddrzewo
        DFSRelease(p->right);  // usuwamy prawe poddrzewo
        delete p;              // usuwamy sam węzeł
    }
}

RBNode * RBTree::findRBT(int k)
{
    RBNode *p;

    p = root;
    while((p != &S) && (p->key != k))
        if(k < p->key)
            p = p->left;
        else
            p = p->right;

    if(p == &S) return nullptr;
    return p;
}

RBNode * RBTree::succRBT(RBNode *p)
{
    RBNode * r;

    if(p != &S)
    {
        if(p->right != &S)
        {
            RBNode * q=p->right;
            if(q->left != &S)
                while(q->left != &S) q = q->left;
            return q;
        }
        else
        {
            r = p->up;
            while((r != &S) && (p == r->right))
            {
                p = r;
                r = r->up;
            }
            return r;
        }
    }
    return &S;
}

void RBTree::rot_L(RBNode * A)
{
    RBNode * B, * p;

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

void RBTree::rot_R(RBNode * A)
{
    RBNode * B, * p;

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

void RBTree::insertRBT(int k)
{
    RBNode * X, * Y;

    X = new RBNode;        // Tworzymy nowy węzeł
    X->left  = &S;          // Inicjujemy pola
    X->right = &S;
    X->up    = root;
    X->key   = k;
    if(X->up == &S) root = X; // X staje się korzeniem
    else
        while(true)             // Szukamy liścia do zastąpienia przez X
        {
            if(k < X->up->key)
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
}


int main()
{
    RBTree o1;
    o1.insertRBT(20);
    o1.insertRBT(2);
    o1.insertRBT(4);
    o1.insertRBT(3);
    o1.insertRBT(9);
    o1.insertRBT(13);
    o1.insertRBT(6);
    o1.insertRBT(7);
    o1.insertRBT(17);
    o1.insertRBT(18);
    o1.insertRBT(15);
    cout << o1.succRBT(o1.findRBT(20))->key;
} 