#include <iostream>
#include <cstring>

using namespace std;

class Node{
public:
    char* text;
    Node* next;
};

class TextList{
public:
    Node* head;

    TextList(){
        head = nullptr;
    };

    TextList(const TextList &o1){
        Node *tmp = o1.head,*gdzie;

        head = new Node;
        size_t size = strlen(tmp->text);
        head->text = new char[size+1];
        memcpy(head->text, tmp->text, size);
        head->text[size] = '\0';
        head->next = nullptr;
        gdzie=head;

        tmp=tmp->next;

        while(tmp != nullptr){
            Node * dodaj = new Node;

            size = strlen(tmp->text);
            dodaj->text = new char[size+1];
            memcpy(dodaj->text, tmp->text, size);
            dodaj->text[size] = '\0';

            dodaj->next= nullptr;

            gdzie->next = dodaj;
            gdzie = dodaj;

            tmp=tmp->next;
        }

    }

    ~TextList(){
        if(head!= nullptr)
        {
            Node *tmp = head, *nast;
            while (tmp != nullptr) {
                nast = tmp->next;

                delete[] tmp->text;
                delete tmp;

                tmp = nast;
            }
            head = nullptr;
        }
    }

    void pushBack(const char*t){
        if(head == nullptr)
        {
            head = new Node;
            size_t size = strlen(t);
            head->text = new char[size+1];
            memcpy(head->text, t, size);
            head->text[size] = '\0';
            head->next = nullptr;
        }
        else
        {
            Node *tmp=head;
            while(tmp->next != nullptr)
            {
                tmp=tmp->next;
            }

            tmp->next = new Node;
            tmp=tmp->next;
            size_t size = strlen(t);
            tmp->text = new char[size+1];
            memcpy(tmp->text, t, size);
            tmp->text[size] = '\0';
            tmp->next = nullptr;
        }
    }

    void show(){
        Node *tmp=head;
        while(tmp != nullptr)
        {
            cout << tmp->text << " ";
            tmp=tmp->next;
        }
    }

    TextList &operator=(const TextList &o1)
    {
        if(this==&o1)
            return *this;

        (*this).~TextList();

        Node *tmp = o1.head,*gdzie;

        head = new Node;
        size_t size = strlen(tmp->text);
        head->text = new char[size+1];
        memcpy(head->text, tmp->text, size);
        head->text[size] = '\0';
        head->next = nullptr;
        gdzie=head;

        tmp=tmp->next;

        while(tmp != nullptr){
            Node * dodaj = new Node;

            size = strlen(tmp->text);
            dodaj->text = new char[size+1];
            memcpy(dodaj->text, tmp->text, size);
            dodaj->text[size] = '\0';

            dodaj->next= nullptr;

            gdzie->next = dodaj;
            gdzie = dodaj;

            tmp=tmp->next;
        }

        return *this;
    }

};

int main()
{
    TextList o1;
    o1.pushBack("Robsonikus");
    o1.pushBack("Oli");
    o1.pushBack("Bobi");

    o1.show();

    cout << endl;

    TextList kopia(o1);
    kopia.pushBack("Rob");
    kopia.pushBack("kop");

    o1=kopia;

    o1.show();
}