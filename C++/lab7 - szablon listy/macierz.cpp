#include "macierz.h"

Macierz::Macierz()
{
    ws = nullptr;
    rozmiar = 0;
}

Macierz::Macierz(const Macierz &o1)
{
    if(o1.rozmiar>0 && o1.ws != nullptr)
    {
        ws = new double[o1.rozmiar * o1.rozmiar];
        rozmiar = o1.rozmiar;

        for (int i = 0; i < rozmiar * rozmiar; i++)
        {
            ws[i] = o1.ws[i];
        }
    }
    else
    {
        ws = nullptr;
        rozmiar = o1.rozmiar;
    }
}

Macierz::Macierz(int rozmiar_macierzy)
{
    if(rozmiar_macierzy>0)
    {
        ws = new double[rozmiar_macierzy * rozmiar_macierzy];
        rozmiar = rozmiar_macierzy;

        for (int i = 0; i < rozmiar * rozmiar; i++)
        {
            ws[i] = 0;
        }
    }
    else {
        ws = nullptr;
        rozmiar = rozmiar_macierzy;
    }
}

Macierz::Macierz(int rozmiar_macierzy,int wypelniacz)
{
    if(rozmiar_macierzy>0)
    {
        ws = new double[rozmiar_macierzy * rozmiar_macierzy];
        rozmiar = rozmiar_macierzy;

        for (int i = 0; i < rozmiar * rozmiar; i++)
        {
            ws[i] = wypelniacz;
        }
    }
    else
    {
        ws = nullptr;
        rozmiar = rozmiar_macierzy;
    }
}

Macierz::~Macierz()
{
    if(ws!=nullptr)
    {
        delete [] ws; // nie jest zmieniana wartosc wskaznika
        ws=nullptr;
    }
}

Macierz& Macierz::operator=(const Macierz & o1)
{
    if(this==&o1) // a=a
        return *this;

    delete [] ws;

    if(o1.rozmiar<1 || o1.ws==nullptr)
    {
        rozmiar=o1.rozmiar;
        ws = nullptr;
        return *this;
    }



    ws=new double[o1.rozmiar*o1.rozmiar];
    rozmiar=o1.rozmiar;

    for(int i=0;i<(o1.rozmiar*o1.rozmiar);i++)
    {
        ws[i]=o1.ws[i];
    }

    return *this; // zawsze to robimy (zapamietac) Jest to po to zeby mozna bylo a=b=c;
}

Macierz Macierz::operator+(const Macierz &o1)
{
    Macierz wynik_dodawania;

    if(rozmiar<0 || o1.rozmiar<0)
    {
        wynik_dodawania.ws= nullptr;
        wynik_dodawania.rozmiar=0;
        return wynik_dodawania;
    }

    if(rozmiar==o1.rozmiar)
    {   wynik_dodawania.rozmiar=o1.rozmiar;
        wynik_dodawania.ws=new double[o1.rozmiar*o1.rozmiar];

        for(int i=0;i<o1.rozmiar*o1.rozmiar;i++)
        {
            wynik_dodawania.ws[i]=ws[i]+o1.ws[i];
        }

        return wynik_dodawania;
    }
    else
    {
        wynik_dodawania.ws= nullptr;
        wynik_dodawania.rozmiar=0;
        return wynik_dodawania;
    }
}

Macierz Macierz::operator-(const Macierz &o1)
{
    Macierz wynik_odejmowania;

    if(rozmiar<0 || o1.rozmiar<0)
    {
        wynik_odejmowania.ws= nullptr;
        wynik_odejmowania.rozmiar=0;
        return wynik_odejmowania;
    }

    if(rozmiar==o1.rozmiar)
    {
        wynik_odejmowania.rozmiar=o1.rozmiar;
        wynik_odejmowania.ws=new double[o1.rozmiar*o1.rozmiar];

        for(int i=0;i<o1.rozmiar*o1.rozmiar;i++)
        {
            wynik_odejmowania.ws[i]=ws[i]-o1.ws[i];
        }

        return wynik_odejmowania;
    }
    else
    {
        wynik_odejmowania.ws= nullptr;
        wynik_odejmowania.rozmiar=0;
        return wynik_odejmowania;
    }

}

Macierz Macierz::operator*(const Macierz &o1)
{
    Macierz wynik;

    if(rozmiar<0 || o1.rozmiar<0)
    {
        wynik.ws= nullptr;
        wynik.rozmiar=0;
        return wynik;
    }

    if(rozmiar==o1.rozmiar)
    {
        wynik.rozmiar=rozmiar;
        wynik.ws=new double[rozmiar*rozmiar];
        int kolumna,wiersz;

        for (int i = 0; i < rozmiar * rozmiar; i++)
        {
            wynik.ws[i] = 0;
            kolumna = i % rozmiar;
            wiersz = i / rozmiar;

            for (int j = wiersz * rozmiar; j < (rozmiar * wiersz + rozmiar); j++)
            {
                wynik.ws[i] += (ws[j] * o1.ws[kolumna]);
                kolumna += rozmiar;
            }
        }

        return wynik;
    }
    else
    {
        wynik.ws= nullptr;
        wynik.rozmiar=0;
        return wynik;
    }
}

bool Macierz::operator==(const Macierz &o1)
{
    if(rozmiar==o1.rozmiar && rozmiar>=0) {
        for (int i = 0; i < rozmiar * rozmiar; i++) {
            if (ws[i] != o1.ws[i])
                return false;
        }

        return true;
    }
    else if(rozmiar==o1.rozmiar)
        return true;

    return false;
}

bool Macierz::operator!=(const Macierz &o1)
{
    if(rozmiar==o1.rozmiar && rozmiar>0) {
        for (int i = 0; i < rozmiar * rozmiar; i++) {
            if (ws[i] != o1.ws[i]) {
                return true;
            }
        }

        return false;
    }
    else if(rozmiar==o1.rozmiar)
        return false;

    return true;
}

bool Macierz::operator>(const Macierz &o1)
{
    if(rozmiar==o1.rozmiar && rozmiar>0) {
        for (int i = 0; i < rozmiar * rozmiar; i++) {
            if (ws[i] <= o1.ws[i])
                return false;
        }

        return true;
    }

    return false;
}

bool Macierz::operator>=(const Macierz &o1)
{
    if(rozmiar==o1.rozmiar && rozmiar>=0) {
        for (int i = 0; i < rozmiar * rozmiar; i++) {
            if (ws[i] < o1.ws[i])
                return false;
        }

        return true;
    }

    return false;
}

bool Macierz::operator<(const Macierz &o1)
{
    if(rozmiar==o1.rozmiar && rozmiar>0) {
        for (int i = 0; i < rozmiar * rozmiar; i++) {
            if (ws[i] >= o1.ws[i])
                return false;
        }

        return true;
    }

    return false;
}

bool Macierz::operator<=(const Macierz &o1)
{
    if(rozmiar==o1.rozmiar && rozmiar>=0)
    {
        for (int i = 0; i < rozmiar * rozmiar; i++)
        {
            if (ws[i] > o1.ws[i])
                return false;
        }

        return true;
    }

    return false;
}

istream & operator>>(istream & s1,Macierz & o1)
{
    if(o1.ws!=nullptr)
    {
        delete[] o1.ws;
        o1.ws = nullptr;
    }
    s1>>o1.rozmiar;

    if(o1.rozmiar>0)
    {
        o1.ws = new double[o1.rozmiar*o1.rozmiar];

        for(int i=0;i<(o1.rozmiar*o1.rozmiar);i++)
        {
            s1>>o1.ws[i];
        }

    }

    return s1;
}

ostream & operator<<(ostream & s1, const Macierz & o1)
{
    if(o1.ws!=nullptr)
    {

        for(int i=0;i<(o1.rozmiar*o1.rozmiar);i++)
        {
            if((i%o1.rozmiar)==0 && i!=0)
                s1 << endl;
            s1 << o1.ws[i] << " ";
        }
        s1<<endl;
    }

    return s1;
}