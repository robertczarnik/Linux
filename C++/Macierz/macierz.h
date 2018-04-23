#ifndef MACIERZ_MACIERZ_H
#define MACIERZ_MACIERZ_H

#include <iostream>
using namespace std;

class Macierz {
    friend ostream &operator<<(ostream &s1, const Macierz &o1);
    friend istream &operator>>(istream &s1, Macierz &o1);

    double *ws;
    int rozmiar;

public:

    Macierz();
    Macierz(const Macierz &o1);
    explicit Macierz(int rozmiar_macierzy);
    Macierz(int rozmiar_macierzy, int wypelniacz);
    ~Macierz();
    Macierz & operator=(const Macierz & o1);
    Macierz operator+(const Macierz &o1);
    Macierz operator-(const Macierz &o1);
    Macierz operator*(const Macierz &o1);
    bool operator==(const Macierz &o1);
    bool operator!=(const Macierz &o1);
    bool operator>(const Macierz &o1);
    bool operator>=(const Macierz &o1);
    bool operator<(const Macierz &o1);
    bool operator<=(const Macierz &o1);
};

#endif
