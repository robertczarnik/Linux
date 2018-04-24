#include <iostream>
using  namespace std;

class Bigint
{
    friend istream & operator>>(istream &s1, Bigint &o1);
    friend ostream & operator<<(ostream &s1, Bigint const &o1);

    string data;

public:
    Bigint()
    {
        data="";
    }

    ~Bigint()
    {
        data.clear();
    }

    Bigint & operator=(Bigint const &o1)
    {
        if(data==o1.data)
            return *this;

        data.clear();
        data=o1.data;

        return *this;
    }

    Bigint operator+(Bigint const &o1)
    {
        Bigint result;
        int tmp=0,num1,num2,sum;
        char number;
        unsigned long size1= data.size();
        unsigned long size2= o1.data.size();
        unsigned long iterations = 0;

        iterations = (size1>=size2) ? size2 : size1;

        for(unsigned long i=0;i<iterations;i++)
        {
            num1=data[size1-1-i] - '0';
            num2=o1.data[size2-1-i] - '0';
            sum=num1+num2+tmp;


            tmp=sum/10;
            sum=sum%10;
            number = static_cast<char>(sum+48);

            result.data = number + result.data;

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

                result.data = number + result.data;
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

                result.data = number + result.data;
            }
        }

        if(tmp)
            result.data = '1' + result.data;

        return result;
    }
};

istream & operator>>(istream &s1, Bigint &o1)
{

    s1>>o1.data;
    return s1;
}

ostream & operator<<(ostream &s1, Bigint const &o1)
{

    s1<<o1.data;
    return s1;
}



int main()
{
    Bigint a,b,c;

    cin >> a;
    cout << a << endl;

    cin >> b;
    cout << b << endl;

    c=a+b;
    cout << endl << endl << c;

    //99999999999999999999999999999999999999999999999999999999999999999999999999999999
}