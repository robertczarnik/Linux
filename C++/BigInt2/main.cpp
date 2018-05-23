#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class BigInt
{
private:
    friend istream &operator>>( istream &s1, BigInt &o1 );
    friend ostream &operator<<( ostream &s1, BigInt const &o1);

protected:
    char *data;
    size_t size;

public:
    BigInt();
    ~BigInt();
    BigInt(const BigInt &o1);

    BigInt &operator=(BigInt const &o1);
    BigInt operator+(BigInt const &o1);
};

BigInt::BigInt()
{
    size = 2;
    data = new char[2];
    data[0]='0';
    data[1]='\0';
}

BigInt::~BigInt()
{
    delete [] data;
}

BigInt::BigInt(const BigInt &o1)
{
    data = new char[o1.size];
    size = o1.size;
    memcpy(data,o1.data,size);
}

BigInt &BigInt::operator=(BigInt const &o1)
{
    if(this==&o1) // a=a
        return *this;

    delete [] data;
    size = o1.size;
    data = new char[size];

    memcpy( data, o1.data, size );

    return *this;
}

BigInt BigInt::operator+(BigInt const &o1)
{
    string tmp_result="";
    int tmp=0,num1,num2,sum;
    char number;
    unsigned long size1 = size-1;
    unsigned long size2 = o1.size-1;
    unsigned long iterations;

    iterations = (size1>=size2) ? size2 : size1;

    for(unsigned long i=0;i<iterations;i++)
    {
        num1=data[size1-1-i] - '0';
        num2=o1.data[size2-1-i] - '0';
        sum=num1+num2+tmp;


        tmp=sum/10;
        sum=sum%10;
        number = static_cast<char>(sum+48);

        tmp_result = number + tmp_result;
    }

    if(size1>size2)
    {
        for(unsigned long i=iterations;i<size1;i++)
        {
            num1=data[size1-1-i] - '0';
            sum=num1+tmp;

            tmp=sum/10;
            sum=sum%10;
            number = static_cast<char>(sum+48);

            tmp_result = number + tmp_result;
        }
    }
    else if(size1<size2)
    {
        for(unsigned long i=iterations;i<size2;i++)
        {
            num2=o1.data[size2-1-i] - '0';
            sum=num2+tmp;

            tmp=sum/10;
            sum=sum%10;
            number = static_cast<char>(sum+48);

            tmp_result = number + tmp_result;
        }
    }

    if(tmp)
        tmp_result = '1' + tmp_result;

    BigInt result;
    result.size = tmp_result.size()+1;
    result.data = new char[result.size];

    for(int i=0;i<result.size-1;i++)
    {
        result.data[i]=tmp_result[i];
    }

    result.data[result.size-1]='\0';

    return result;
}

istream &operator>>( istream &s1, BigInt &o1 )
{
    string s;
    s1 >> s;

    delete [] o1.data;

    unsigned long rozmiar = s.size();
    rozmiar++;
    o1.data = new char [rozmiar];
    o1.size = rozmiar;

    for(int i=0;i<rozmiar-1;i++)
    {
        o1.data[i]=s[i];
    }

    o1.data[rozmiar-1]='\0';

    return s1;
}

ostream &operator<<( ostream &s1, BigInt const &o1 )
{
    for( int i = 0; i < o1.size-1; i++ )
        s1 << o1.data[i];

    return s1;
}

class Bigint_extended : public BigInt
{
public:

    Bigint_extended &operator=(const BigInt &o1)
    {
        BigInt::operator=(o1);
        return *this;
    }

    bool operator==(Bigint_extended const &o1)
    {
        if(size!=o1.size)
            return false;

        for(int i=0;i<size-1;i++)
        {
            if(data[i]!=o1.data[i])
                return false;
        }

        return true;
    }

    bool operator!=(Bigint_extended const &o1)
    {
        if(size!=o1.size)
            return true;

        for(int i=0;i<size-1;i++)
        {
            if(data[i]!=o1.data[i])
                return true;
        }

        return false;
    }

    bool operator<(Bigint_extended const &o1)
    {
        if(size<o1.size)
            return true;
        else if(size==o1.size)
        {
            for(int i=0;i<size-1;i++)
            {
                if(data[i]!=o1.data[i])
                {
                    return (data[i] < o1.data[i]);
                }
            }
        }

        return false;
    }

    bool operator>(Bigint_extended const &o1)
    {
        if(size>o1.size)
            return true;
        else if(size==o1.size)
        {
            for(int i=0;i<size-1;i++)
            {
                if(data[i]!=o1.data[i])
                {
                    return (data[i] > o1.data[i]);
                }
            }
        }

        return false;
    }

    Bigint_extended operator*(Bigint_extended const &o1)
    {
        Bigint_extended result;
        string result_tmp="0";
        string tab[10]={"0"};
        unsigned long tmp,add;
        int num;
        char number;
        string zeros;
        zeros = "";

        for(int j=0;j<10;j++)
        {
            tmp = 0;

            for (unsigned long i = size-1; i > 0; i--)
            {
                num = this->data[i - 1] - '0';
                add = (num * j) + tmp;

                tmp = add / 10;
                add = add % 10;
                number = static_cast<char>(add + 48);

                tab[j] = number + tab[j];
            }

            if(tmp)
            {
                ostringstream ss; // conversion to string
                ss << tmp;
                tab[j] = ss.str() + tab[j];
            }
        }

        for (unsigned long i = o1.size-1; i > 0; i--)
        {
            Bigint_extended tmp2;
            string str;
            str=tab[o1.data[i-1]-'0'] + zeros; // adding zeros at the end

            tmp2.size=str.size()+1;
            tmp2.data= new char[tmp2.size];

            for(int j=0;j<tmp2.size-1;j++)
                tmp2.data[j]=str[j];

            tmp2.data[tmp2.size-1]='\0';
            result = result + tmp2;
            zeros.insert(0,"0");

        }


        return result;
    }

};

int main()
{
    Bigint_extended a,b,d,e;

    cin >> a;
    cin >> b;

    Bigint_extended c(a);

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "copy a: " << c << endl;

    d=a+b;
    e=a*b;

    cout << "d=a+b: " << d << endl;
    cout << "e=a*b: " << e << endl;

    cout << "a==b: " << (a==b) << endl;
    cout << "a!=b: " << (a!=b) << endl;
    cout << "a<b: " << (a<b) << endl;
    cout << "a>b: " << (a>b) << endl;
}