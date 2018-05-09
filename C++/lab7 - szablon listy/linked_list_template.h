#ifndef LINKED_LIST_TEMPLATE_LINKED_LIST_TEMPLATE_H
#define LINKED_LIST_TEMPLATE_LINKED_LIST_TEMPLATE_H

#include <iostream>
using namespace std;

template <typename T>
class List; // declaration

template <typename T>
class Element
{
    friend class List<T>;

    template <typename TT>
    friend istream &operator>>(istream &s1, List<TT> &o1);

    template <typename TT>
    friend ostream &operator<<(ostream &s1, const List<TT> &o1);

    Element *next;
    T data;
};

template <typename T>
class List
{
    template<typename TT>
    friend istream &operator>>(istream &s1, List<TT> &o1);

    template<typename TT>
    friend ostream &operator<<(ostream &s1, const List<TT> &o1);

    Element<T> *head;

public:
    List();
    List(const List &o1);
    ~List();
    List & operator=(List const &o1);
    List operator+(List const &o1);
    bool operator==(List const &o1);
    bool operator!=(List const &o1);
};

template <typename T>
List<T>::List()
{
    head = nullptr;
}

template <typename T>
List<T>::List(const List<T> &o1)
{

    if(o1.head == nullptr) // for empty list
    {
        head = nullptr;
        return;
    }

    Element<T> *node=o1.head,*remember; // it remembers pointer to next element
    head = new Element<T>;
    head->data = o1.head->data;
    node=node->next;

    if (node == nullptr) // for list with 1 element
    {
        head->next = nullptr;
        return;
    }

    head->next = new Element<T>; // memory allocation
    remember = head->next;

    while(1)
    {
        Element<T> *new_object;
        new_object = remember; // new object become a new element of the list
        new_object->data = node->data;
        node = node->next;

        if (node == nullptr) // for list with more than 1 element
        {
            new_object->next = nullptr;
            return;
        }

        new_object->next = new Element<T>;
        remember = new_object->next;
    }


}

template <typename T>
List<T>::~List()
{
    Element<T> *node=head;

    while(node != nullptr)
    {
        Element<T> *tmp = node->next;
        delete node;
        node=tmp;
    }

    head = nullptr;
}

template <typename T>
List<T> & List<T>::operator=(List<T> const &o1)
{
    if(this==&o1) // a=a
        return *this;

    Element<T> *node=head;
    while(node != nullptr) // deleting left operand
    {
        Element<T> *tmp = node->next;
        delete node;
        node=tmp;
    }
    head = nullptr;

//-------------------------------------------------------------------//
    if(o1.head == nullptr) // for empty list
    {
        head = nullptr;
        return *this;
    }

    node=o1.head;
    Element<T> *remember; // it remembers pointer to next element
    head = new Element<T>;
    head->data = o1.head->data;
    node=node->next;

    if (node == nullptr) // for list with 1 element
    {
        head->next = nullptr;
        return *this;
    }

    head->next = new Element<T>;
    remember = head->next;

    while(1)
    {
        Element<T> *new_object;
        new_object = remember; // new object become a new element of the list
        new_object->data = node->data;
        node = node->next;

        if (node == nullptr) // for list with more than 1 element
        {
            new_object->next = nullptr;
            return *this;
        }

        new_object->next = new Element<T>;
        remember = new_object->next;

    }
}

template <typename T>
List<T> List<T>::operator+(List<T> const &o1)
{
    List<T> result(*this); // copy of first list
    Element<T> *node=o1.head;
    Element<T> *remember;

    if(result.head == nullptr && node == nullptr) // both lists are empty
    {
        return result;
    }

    if(node!= nullptr)
    {
        Element<T> *tmp = result.head;

        if(tmp == nullptr) // first list empty
        {
            result.head = new Element<T>;
            remember = result.head;
        }
        else // first list non-empty
        {
            while (tmp->next != nullptr) { // finding last element of list
                tmp = tmp->next;
            }
            tmp->next = new Element<T>; // memory allocation for new element
            remember = tmp->next;
        }

        while(1)
        {
            Element<T> *new_object;
            new_object = remember; // new object become a new element of the list
            new_object->data = node->data;
            node = node->next;

            if (node == nullptr) // for non-empty second list
            {
                new_object->next = nullptr;
                return result;
            }

            new_object->next = new Element<T>;
            remember = new_object->next;
        }
    }

    return result; // second list is empty
}

template <typename T>
bool List<T>::operator==(List<T> const &o1)
{
    Element<T> *node_1=head,*node_2=o1.head;

    while(node_1 != nullptr || node_2 != nullptr)
    {
        if(node_1 != nullptr && node_2 != nullptr)
        {
            if(node_1->data!=node_2->data)
                return false;

            node_1=node_1->next;
            node_2=node_2->next;
        }
        else // different lengths
            return false;
    }
    return true;
}

template <typename T>
bool List<T>::operator!=(List<T> const &o1)
{
    Element<T> *node_1=head,*node_2=o1.head;

    while(node_1 != nullptr || node_2 != nullptr)
    {
        if(node_1 != nullptr && node_2 != nullptr)
        {
            if(node_1->data!=node_2->data)
                return true;

            node_1=node_1->next;
            node_2=node_2->next;
        }
        else // different lengths
            return true;
    }
    return false;
}

template <typename T>
istream & operator>>(istream &s1,List<T> &o1)
{
    auto *node = new Element<T>;

    if(o1.head==nullptr) // empty list
    {
        s1 >> node->data;
        node->next = nullptr;
        o1.head=node;
    }
    else // non-empty list
    {
        Element<T> *tmp = o1.head;
        while (tmp->next != nullptr) { // finding last element of list
            tmp = tmp->next;
        }
        tmp->next = new Element<T>; // memory allocation for new element
        node = tmp->next; // placing a new node in a list

        s1 >> node->data;
        node->next = nullptr;
    }
    return s1;
}

template <typename T>
ostream & operator<<(ostream &s1, const List<T> &o1)
{
    Element<T> *node=o1.head;
    while(node != nullptr)
    {
        s1<<endl<<node->data<<endl;
        node=node->next;
    }

    return s1;
}

#endif