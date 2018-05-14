#include <iostream>
#include <sstream>
using  namespace std;

class Bigint
{
    friend istream & operator>>(istream &s1, Bigint &o1);
    friend ostream & operator<<(ostream &s1, Bigint const &o1);

protected:

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

class Bigint_extended : public Bigint
{
public:

    Bigint_extended &operator=(const Bigint &o1)
    {
        Bigint::operator=(o1);
        return *this;
    }

    bool operator==(Bigint_extended const &o1)
    {
        return (this->data == o1.data);
    }

    bool operator!=(Bigint_extended const &o1)
    {
        return (this->data != o1.data);
    }

    bool operator<(Bigint_extended const &o1)
    {
        if(this->data.size()<o1.data.size())
            return true;
        else if(this->data.size()==o1.data.size())
        {
            for(int i=0;i<this->data.size();i++)
            {
                if(this->data[i]!=o1.data[i])
                {
                    return (this->data.size() < o1.data.size());
                }
            }
        }

        return false;
    }

    bool operator>(Bigint_extended const &o1)
    {
        if(this->data.size()>o1.data.size())
            return true;
        else if(this->data.size()==o1.data.size())
        {
            for(int i=0;i<this->data.size();i++)
            {
                if(this->data[i]!=o1.data[i])
                {
                    return (this->data.size() > o1.data.size());
                }
            }
        }

        return false;
    }

    Bigint_extended operator*(Bigint_extended const &o1)
    {
        Bigint_extended result;
        result.data="0";
        Bigint_extended tab[10];
        unsigned long tmp,add;
        int num;
        char number;
        string zeros;
        zeros = "";

        for(int j=0;j<10;j++)
        {
            tmp = 0;

            for (unsigned long i = this->data.size(); i > 0; i--)
            {
                num = this->data[i - 1] - '0';
                add = (num * j) + tmp;

                tmp = add / 10;
                add = add % 10;
                number = static_cast<char>(add + 48);

                tab[j].data = number + tab[j].data;
            }

            if(tmp)
            {
                ostringstream ss; // conversion to string
                ss << tmp;
                tab[j].data = ss.str() + tab[j].data;
            }
        }

        for (unsigned long i = o1.data.size(); i > 0; i--)
        {
            Bigint_extended tmp2;
            tmp2.data=tab[o1.data[i-1]-'0'].data + zeros; // adding zeros at the end
            result = result + tmp2;
            zeros.insert(0,"0");
        }

        return result;
    }

};


int main()
{
    Bigint_extended a,b,c,d;

    cin >> a;
    cout << a << endl;

    cin >> b;
    cout << b << endl;

    d=a*b;

    cout << "d: " << d << endl;


    //99999999999999999999999999999999999999999999999999999999999999999999999999999999
}