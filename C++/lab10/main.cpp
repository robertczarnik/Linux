#include <iostream>
#include <map>
#include <list>
using namespace std;

int main() {
    string slowo;
    map <string,string> slownik;
    slownik["prokrastynacja"] = "procrastination";
    slownik["jajko"] = "egg";
    slownik["chleb"] = "bread";
    slownik["palec"] = "finger";

    cout << "Jakiego wyrazu poszukujesz?" << endl;
    cin >> slowo;
    cout << slowo << " -> " << slownik[slowo] << endl << endl;


    cout << "What word are you looking for?" << endl;
    cin >> slowo;


    for(map<string,string>::iterator i = slownik.begin();i!=slownik.end();i++)
    {
        if(i->second==slowo)
        {
            cout << slowo << " -> " << i->second << endl << endl;
            break;
        }
    }


    list<string> lista;
    lista.push_back("Robert");
    lista.push_back("Bob");
    lista.push_back("Rob");
    lista.push_back("Robson");
    lista.sort();

    for(list<string>::iterator i = lista.begin();i!=lista.end();i++)
    {
        cout << "* " << *i << endl;
    }

}