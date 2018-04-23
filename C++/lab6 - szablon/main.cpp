#include <iostream>
//ta liste zmienic na wzorzec klasy sprawdzic na int i macierzy opisac jawnie na jakich moze byc zrealizowana, potrzebne sa np =, +,* itp
//w jaki sposob zaprzyjaznic wzorzec funkcji wewnatrz wzorca klasy
using  namespace std;

class Macierz {
    friend ostream &operator<<(ostream &s1, const Macierz &o1);
    friend istream &operator>>(istream &s1, Macierz &o1);

    double *ws;
    int rozmiar;

public:

    Macierz() // konstruktor
    {
        ws = nullptr;
        rozmiar = 0;
    }

    Macierz(const Macierz &o1) // konstruktor kopiujacy
    {
        if(o1.rozmiar>0 && ws != nullptr)
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

    explicit Macierz(int rozmiar_macierzy) // konstruktor wypelniajacy zerami
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

    Macierz(int rozmiar_macierzy,int wypelniacz) // konstruktor wypelniajacy zadana liczba
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

    ~Macierz() // destruktor
    {
        if(ws!=nullptr)
        {
            delete [] ws; // nie jest zmieniana wartosc wskaznika
            ws=nullptr;
        }
    }

    Macierz & operator=(const Macierz & o1) // a.operator=(b); lub a=b;
    {
        if(this==&o1) // a=a
            return *this;

        if(o1.rozmiar<1 || o1.ws==nullptr)
        {
            rozmiar=o1.rozmiar;
            ws = nullptr;
            return *this;
        }

        delete [] ws;
        ws=nullptr;
        ws=new double[o1.rozmiar*o1.rozmiar];
        rozmiar=o1.rozmiar;

        for(int i=0;i<(o1.rozmiar*o1.rozmiar);i++)
        {
            ws[i]=o1.ws[i];
        }

        return *this; // zawsze to robimy (zapamietac) Jest to po to zeby mozna bylo a=b=c;
    }

    Macierz operator+(const Macierz &o1)
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

    Macierz operator-(const Macierz &o1)
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

    Macierz operator*(const Macierz &o1)
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

    bool operator==(const Macierz &o1)
    {
        if(rozmiar==o1.rozmiar && rozmiar>=0) {
            for (int i = 0; i < rozmiar * rozmiar; i++) {
                if (ws[i] != o1.ws[i])
                    return false;
            }

            return true;
        }

        return false;
    }

    bool operator!=(const Macierz &o1)
    {
        if(rozmiar==o1.rozmiar && rozmiar>0) {
            for (int i = 0; i < rozmiar * rozmiar; i++) {
                if (ws[i] != o1.ws[i]) {
                    return true;
                }
            }

            return false;
        }

        return false;
    }

    bool operator>(const Macierz &o1)
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

    bool operator>=(const Macierz &o1)
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

    bool operator<(const Macierz &o1)
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

    bool operator<=(const Macierz &o1)
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
};

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

template <class T>
class para{

    template <class TT>
    friend istream & operator>>(istream &s, para<TT> &o1);

    template <class TT>
    friend ostream & operator<<(ostream &s, const para<TT> &o1);

    T x,y;

public:

    para<T>(){}

    para<T> (const para &o1) // konstruktor kopiujacy
    {
        x=o1.x;
        y=o1.y;
    }

    para<T> &operator=(const para<T> &o1)
    {
        x=o1.x;
        y=o1.y;
        return *this;
    }

    para<T> operator+(const para<T> &o1)
    {
        para wynik{};
        wynik.x = x + o1.x;
        wynik.y = y + o1.y;
        return wynik;
    }
};

template <class T>
istream & operator>>(istream &s, para<T> &o1)
{
    s>>o1.x>>o1.y;
    return s;
}

template <class T>
ostream & operator<<(ostream &s, const para<T> &o1)
{
    s<<o1.x<<endl<<o1.y<<endl;
    return s;
}

int main()
{
    // na tym typie musi byc zadeklarowane operacje dodawania i przypisania

    // int
    para<int> a,b,c;
    cin >> b >> c;
    a=b+c;
    cout << a;

    cout << endl;

    // macierz
    para<class Macierz> d,e,f;

    cin >> e >> f;
    d=e+f;
    cout << d;
}