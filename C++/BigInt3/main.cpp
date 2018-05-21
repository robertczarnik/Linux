#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

class BigInt
{
private:
    char *liczba;
    int ilosc;
public:
/*
		BigInt & operator=(long a)
		{
			bool wart = false;
			if(a < 0)
			{
				wart = true;
				a = abs(a);
			}

			long temp = a;
			int licznik = 0;
			while(temp)
			{
				temp/=10;
				licznik++;
			}

			liczba = new char[licznik+1];
			if(wart) liczba[0] = 1 + 48;
			else liczba[0] = 0 + 48;
			for(int i = licznik; i>0; i--)
			{
				liczba[i] = a%10 + 48;
				a /= 10;
			}
			ilosc = licznik;
		}

		*/

    BigInt & operator=(string s)
    {
        ilosc = s.length();
        delete [] liczba;
        liczba = new char[ilosc+1];
        if((int)s[0] == 45)
        {
            liczba[0] = 1 + 48;
            for(int i = 1 ; i<=ilosc ; i++ )
            {
                liczba[i] = s[i-1];
            }
        }
        else
        {
            liczba[0] = 0 + 48;
            for(int i = 1 ; i<=ilosc ; i++ )
            {
                liczba[i] = s[i-1];
            }
        }
    }


    BigInt & operator=(const BigInt &b)
    {
        ilosc = b.ilosc;
        delete [] liczba;
        liczba = new char[b.ilosc+1];

        for(int i = 0 ; i<=ilosc ;i++)
        {
            liczba[i] = b.liczba[i];
        }
    }

    BigInt(long a = 0)
    {
        bool wart = false;
        if(a < 0)
        {
            wart = true;
            a = abs(a);
        }

        long temp = a;
        int licznik = 0;
        while(temp)
        {
            temp/=10;
            licznik++;
        }
        if(a == 0) licznik++;
        liczba = new char[licznik+1];
        if(wart) liczba[0] = 1 + 48;
        else liczba[0] = 0 + 48;
        for(int i = licznik; i>0; i--)
        {
            liczba[i] = a%10 + 48;
            a /= 10;
        }
        ilosc = licznik;

    }

    BigInt(string tab)
    {
        bool wart = false;
        if((int)tab[0] == 45)
        {
            wart = true;
        }
        int i = tab.length();
        liczba = new char[i];

        if(wart) liczba[0] = 1 + 48;
        else liczba[0] = 0 + 48;

        for(int j = 1; j<=i ; j++)
        {
            liczba[j] = tab[j-1];
        }
        ilosc = i;
    }

    ~BigInt()
    {
        delete [] liczba;
    }

    int get_ilosc()
    {
        return ilosc;
    }

    void Print()
    {
        for(int i = 1; i<=ilosc ;i++)
        {
            cout<<liczba[i];
        }
        cout<<endl;
    }

    friend ostream & operator<<(ostream& os,const BigInt &b)
    {
        if(b.liczba[0] == 1 + 48) os<<"-";
        for(int i = 1; i<=b.ilosc ;i++)
        {
            os<<b.liczba[i];
        }
        return os;
    }

    friend istream & operator>>(istream & is, BigInt &b)
    {
        string str;
        is>>str;
        b = str;
        return is;
    }
    void operator++(int);
    void operator--(int);
    short operator[](unsigned int idx);
    bool operator==( BigInt &b2);
    bool operator!=( BigInt &b2);
    bool operator<( BigInt &b2);
    bool operator>( BigInt &b2);
    bool operator<=( BigInt &b2);
    bool operator>=( BigInt &b2);
    BigInt operator+(BigInt &b2);
    BigInt operator*(BigInt &b2);
    BigInt operator/(BigInt &b2);
    BigInt operator-(BigInt &b2);
    void operator+=(BigInt &b2);
    void operator-=(BigInt &b2);
    void operator*=(BigInt &b2);
    void operator/=(BigInt &b2);
    BigInt operator%(BigInt &b2);
    BigInt operator*(long a);
    BigInt operator/(long a);
    BigInt operator+(long a);
    BigInt operator-(long a);
    void operator++();
    void operator--();
    void operator-();
};


short BigInt::operator[](unsigned int idx)
{
    if(idx <= ilosc)
    {
        idx = ilosc - idx;
        return this->liczba[idx] - 48;
    }
}


void BigInt::operator++(int)
{
    int i=ilosc;
    bool wart = true;
    while(wart)
    {
        if(i == 0)
        {
            string a;
            a += 1 + 48;
            for(int i = 1; i<=ilosc ; i++)
            {
                a += liczba[i];
            }

            BigInt wynik(a);

            (*this) = wynik;
            return;
        }


        if((int)liczba[i] < 57)
        {
            liczba[i] = (int)liczba[i] + 1 ;
            return;
        }
        else
        {
            liczba[i] = 0 + 48;
            i--;
        }

    }
}


BigInt BigInt::operator+(BigInt &b2)
{
    string wynik;				// Obiekt zwracany
    int sum=0,licznik;			// zmienne pomocnicze
    short wn;					// Iterowany wynik
    char temp;					// Zmiana kolejnosci wyniku


//------------ Decydowanie ilosci iteracji w petli--------

    if(ilosc>b2.ilosc) licznik = b2.ilosc;
    else licznik = ilosc;

//------------ Dodawanie w swopku ------------------------

    for(int i = 0; i<licznik ; i++)
    {
        wn = (*this)[i] + b2[i] + sum;
        if(wn>9)
        {
            wn-=10;
            sum = 1;
        }
        else sum = 0;

        wynik+=wn+48;
    }

//--------- Dopisywanie wynikow --------------------------

    if(ilosc > b2.ilosc)
    {
        while(licznik < ilosc)
        {
            wn = (*this)[licznik] + sum ;
            if(wn>9)
            {
                wn-=10;
                sum = 1;
            }
            else sum = 0;

            wynik+= wn + 48;
            licznik++;
        }
    }
    else
    {
        while(licznik < b2.ilosc)
        {
            wn = b2[licznik] + sum ;
            if(wn>9)
            {
                wn-=10;
                sum = 1;
            }
            else sum = 0;

            wynik+= wn + 48;
            licznik++;
        }
    }

    if(sum!=0)
    {
        licznik++;
        wynik+= 1 + 48;
    }

//--------- Zapisanie w normalnej kolejnosci -------------

    BigInt res(wynik);

    for(int i = 1; i<=(licznik+1)/2;i++)
    {
        temp = res.liczba[i];
        res.liczba[i] = res.liczba[licznik-i+1];
        res.liczba[licznik-i+1] = temp;
    }

    return res;
}


void BigInt::operator+=(BigInt &b2)
{
    (*this) =  (*this) + b2;
}


BigInt BigInt::operator*(BigInt &b2)
{
    bool wart = false;
    if((*this).liczba[0] == 1 + 48 || b2.liczba[0] == 1 + 48) wart = true;


    short wn, ost = 0;
    string tab[b2.ilosc];
    for(int i = 0; i < b2.ilosc ; i++)
    {
        for(int j = 0 ; j < ilosc ; j++)
        {
            wn = (*this)[j] * b2[i] + ost;

            if(wn>9)
            {
                ost = wn/10;
                wn = wn%10;
            }
            else ost = 0;

            tab[i] += wn + 48;

        }
        if(ost != 0) tab[i] += ost + 48;
    }


    for(int i = 0; i<b2.ilosc ; i++)
    {
        for(int j = 0 ; j< tab[i].length()/2; j++)
        {
            char c = tab[i][j];
            tab[i][j] = tab[i][(tab[i].length()) - j - 1];
            tab[i][(tab[i].length()) - j - 1] = c;
        }

    }


    for(int i = 1; i<b2.ilosc; i++)
    {
        for(int j = 0; j<i ; j++)
        {
            tab[i] += 0 + 48;
        }
    }

    BigInt s[b2.ilosc];
    BigInt result;

    for(int i = 0; i<b2.ilosc ; i++)
    {
        s[i] = tab[i];
    }
/*
	for(int i = 0; i<b2.ilosc ; i++)
	{
		s[i].Print();
	}
*/
    for(int i = 0 ; i<b2.ilosc ; i++)
    {
        result +=  s[i];
    }

    if(wart) result.liczba[0] = 1 + 48;

    return result;
}

bool BigInt::operator==( BigInt &b2)
{
    if(ilosc != b2.ilosc) return false;

    for(int i = 0 ; i<ilosc ; i++)
    {
        if((int)(*this)[i] != (int)b2[i]) return false;
    }

    return true;

}

bool BigInt::operator!=(BigInt &b2)
{
    if(ilosc != b2.ilosc) return true;

    for(int i = 0 ; i<ilosc ; i++)
    {
        if((int)(*this)[i] != (int)b2[i]) return true;
    }

    return false;
}

bool BigInt::operator<=(BigInt &b2)
{
    if(ilosc < b2.ilosc) return true;

    if(ilosc > b2.ilosc) return false;

    for(int i = ilosc ; i>=0 ; i--)
    {
        if((*this)[i] < b2[i]) return true;
        else if((*this)[i] > b2[i]) return false;


        if(i == 0 && (*this)[i] == b2[i]) return true;
    }

    return false;

}

bool BigInt::operator>=(BigInt &b2)
{
    if(ilosc > b2.ilosc) return true;

    if(ilosc < b2.ilosc) return false;

    for(int i = ilosc ; i>=0 ; i--)
    {
        if((*this)[i] > b2[i]) return true;
        else if((*this)[i]<b2[i]) return false;


        if(i == 0 && (*this)[i] == b2[i]) return true;
    }

    return false;
}


bool BigInt::operator>(BigInt &b2)
{
    if(ilosc > b2.ilosc) return true;

    if(ilosc < b2.ilosc) return false;

    for(int i = ilosc ; i>=0 ; i--)
    {
        if((*this)[i] > b2[i]) return true;
    }

    return false;
}

bool BigInt::operator<(BigInt &b2)
{
    if(ilosc < b2.ilosc) return true;

    if(ilosc > b2.ilosc) return false;

    for(int i = ilosc ; i>=0 ; i--)
    {
        if((*this)[i] < b2[i]) return true;
    }

    return false;
}

void BigInt::operator--(int)
{
    int i=ilosc;
    bool wart = true;
    while(wart)
    {
        if(i == 1)
        {
            string a;
            for(int i = 2; i<=ilosc ; i++)
            {
                a += liczba[i];
            }

            BigInt wynik(a);


            (*this) = wynik;
            return;
        }
        if((int)liczba[i] > 48)
        {
            liczba[i] = (int)liczba[i] - 1 ;
            return;
        }
        else
        {
            liczba[i] = 9 + 48;
            i--;
        }
    }
}


BigInt BigInt::operator-(BigInt &b2)
{
    BigInt licz,licz2;
    int licznik;
    short wn,sum = 0;
    string wynik;

    if((*this)>b2)
    {
        licz = (*this);
        licz2 = b2;
        licznik = b2.ilosc;
    }

    for(int i = 0; i<licznik ; i++)
    {
        wn = licz[i] - licz2[i] - sum;

        if(wn<0)
        {
            wn += 10;
            sum = 1;
        }
        else sum = 0;

        wynik += wn + 48;
    }

//--------------Dopisywanie wynikow----------------
    while(licznik < licz.ilosc)
    {
        wn = licz[licznik] - sum ;
        if(wn<0)
        {
            wn+=10;
            sum = 1;
        }
        else sum = 0;

        wynik+= wn + 48;
        licznik++;
    }
//-------------------------------------------------

    licznik = wynik.length();
    for(int i = 0; i<licznik/2;i++)
    {
        char t = wynik[i];
        wynik[i] = wynik[licznik-i-1];
        wynik[licznik-i-1] = t;
    }
//----------------Zabieramy zera-------------------------
    if(wynik[0] == 0 + 48)
    {
        string temp = wynik;
        int i = 0;

        while(temp[i] == 0+48)
        {
            i++;
        }

        wynik = "";
        for(int j = i; j<temp.length(); j++ )
        {
            wynik += temp[j];
        }
    }

    BigInt res(wynik);

    return res;
}

BigInt BigInt::operator/(BigInt &b2)
{
    BigInt temp = (*this),wynik;
    bool wart = false;
    if(temp.liczba[0] == 1 +48 || wynik.liczba[0] == 1 + 48) wart = true;

    while(temp >= b2)
    {
        temp = temp - b2;
        wynik++;
    }
    if(wart) wynik.liczba[0] = 1 + 48;
    return wynik;
}

void BigInt::operator-=(BigInt &b2)
{
    (*this) = (*this) - b2;
}
void BigInt::operator*=(BigInt &b2)
{
    (*this) = (*this) * b2;
}
void BigInt::operator/=(BigInt &b2)
{
    (*this) = (*this) / b2;
}

BigInt BigInt::operator%(BigInt &b2)
{
    if((*this) < b2) return (*this);

    BigInt temp = (*this);
    while(temp >= b2)
    {
        temp = temp - b2;
    }
    return temp;
}

BigInt BigInt::operator*(long a)
{
    BigInt temp(a);

    return (*this)*temp;
}

BigInt BigInt::operator/(long a)
{
    BigInt temp(a);

    return (*this)/temp;
}

BigInt BigInt::operator+(long a)
{
    BigInt temp(a);

    return (*this)+temp;
}

BigInt BigInt::operator-(long a)
{
    BigInt temp(a);

    return (*this)-temp;
}

void BigInt::operator++()
{
    int i=ilosc;
    bool wart = true;
    while(wart)
    {
        if(i == 0)
        {
            string a;
            a += 1 + 48;
            for(int i = 1; i<=ilosc ; i++)
            {
                a += liczba[i];
            }

            BigInt wynik(a);

            (*this) = wynik;
            return;
        }


        if((int)liczba[i] < 57)
        {
            liczba[i] = (int)liczba[i] + 1 ;
            return;
        }
        else
        {
            liczba[i] = 0 + 48;
            i--;
        }

    }
}

void BigInt::operator--()
{
    int i=ilosc;
    bool wart = true;
    while(wart)
    {
        if(i == 1)
        {
            string a;
            for(int i = 2; i<=ilosc ; i++)
            {
                a += liczba[i];
            }

            BigInt wynik(a);


            (*this) = wynik;
            return;
        }
        if((int)liczba[i] > 48)
        {
            liczba[i] = (int)liczba[i] - 1 ;
            return;
        }
        else
        {
            liczba[i] = 9 + 48;
            i--;
        }
    }
}

void BigInt::operator-()
{
    if(liczba[0] == 0 + 48) liczba[0] = 1 +48;
    else liczba[0] = 0 + 48;
}

int main()
{
    BigInt a(-3929),b("400"),c("1");

    c = a/b;
    cout<<c;


    return 0;
}