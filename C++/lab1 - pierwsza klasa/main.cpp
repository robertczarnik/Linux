#include <iostream>

using namespace std;

class czas
{
    int godz,minuta,sek;
public:

    void zapamietaj_czas(int g, int m, int s)
    {
        godz=g;
        minuta=m;
        sek=s;
    }

    void zapamietaj_czas(char *cz)
    {
        sscanf (cz,"%d:%d:%d",&godz,&minuta,&sek);
    }

    void zwroc_czas(int &g, int &m, int &s)
    {
        g=godz;
        m=minuta;
        s=sek;
    }

    void zwroc_czas(char *cz)
    {
        sprintf (cz,"%d:%d:%d",godz,minuta,sek);
    }

    void zwieksz_o_sekundy(int sekundy)
    {
        sek+=sekundy;
        minuta+=sek/60;
        sek%=60;
        godz+=minuta/60;
        minuta%=60;
        godz%=24;
    }

    void zwieksz_o(char *cz)
    {
        int dodaj_g,dodaj_m,dodaj_s;
        sscanf (cz,"%d:%d:%d",&dodaj_g,&dodaj_m,&dodaj_s);

        sek+=dodaj_s;
        dodaj_m+=sek/60;
        sek%=60;

        minuta+=dodaj_m;
        dodaj_g+=minuta/60;
        minuta%=60;

        godz+=dodaj_g;
        godz%=24;
    }
};

int main()
{
    czas obiekt1{};
    int g,m,s;
    char czas[100];


    obiekt1.zapamietaj_czas(20,45,12);
    obiekt1.zwroc_czas(g,m,s);
    cout << g << " " << m << " " << s << endl;

    obiekt1.zapamietaj_czas((char*)"24:0:59");
    obiekt1.zwroc_czas(czas);
    cout << czas << endl;

    obiekt1.zwieksz_o_sekundy(3661);

    obiekt1.zwroc_czas(czas);
    cout << czas << endl;

    obiekt1.zwieksz_o((char*)("26:61:61"));

    obiekt1.zwroc_czas(czas);
    cout << czas << endl;
}
