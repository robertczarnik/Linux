#include <iostream>
#include <set>
#include <vector>
using namespace std;

class City{
public:
    string name;
    string county;
    string region;
    int population;
};


class AS{
public:
    vector<City> city;

    AS()
    = default;

    void addCity(const char*name,int pop,const char*county,const char*region)
    {

        for(auto it=city.begin();it!=city.end();it++)
        {
            if(it->name==name)
            {
                it->name=name;
                it->county=county;
                it->region=region;
                it->population=pop;
                return;
            }
        }


        City o1;

        o1.name=name;
        o1.region=region;
        o1.county=county;
        o1.population=pop;

        city.push_back(o1);
    }

    City* findCity(const char*name)
    {
        for(auto it=city.begin();it!=city.end();it++)
        {
            if(it->name==name)
            {
                return &(*it);
            }
        }

        return nullptr;
    }

    void removeCity(const char *name)
    {
        for(auto it=city.begin();it!=city.end();it++)
        {
            if(it->name==name)
            {
                city.erase(it);
            }
        }
    }

    set<string> getCitiesInCounty(const char*cntname)
    {
        set<string> wynik;

        for(auto it=city.begin();it!=city.end();it++)
        {
            if(it->county==cntname)
            {
                wynik.insert(it->name);
            }
        }

        return wynik;
    }

    set<string> getCitiesInRegion(const char*regname)
    {
        set<string> wynik;

        for(auto it=city.begin();it!=city.end();it++)
        {
            if(it->region==regname)
            {
                wynik.insert(it->name);
            }
        }

        return wynik;
    }

    set<string> getCountries(const char*regname)
    {
        set<string> wynik;

        for(auto it=city.begin();it!=city.end();it++)
        {
            if(it->region==regname)
            {
                wynik.insert(it->county);
            }
        }

        return wynik;
    }

    void show()
    {
        for(auto it=city.begin();it!=city.end();it++)
        {
            cout << it->name << " " << it->population << " " << it->county << " " << it->region << endl;
        }
    }

};


int main() {
    AS o1;

    o1.addCity("Wiercany",1000,"sedz","podk");
    o1.addCity("Pigonia",9100,"Krakowski","podk");
    o1.addCity("Korzanow",3200,"lezajsk","podk");
    o1.addCity("Wadawsaw",3210,"lezajsk","podk");
    o1.addCity("Adra",3250,"lezajsk","podk");
    o1.addCity("Pigonoslania",9200,"Krakowski","Malopolska");
    o1.addCity("Szec",37100,"lezajsk","podk");
    o1.addCity("Wiercany",91100,"lezajsk","podk");

    City *szukany;
    szukany=o1.findCity("Wiercany");

    o1.show();
    o1.removeCity("Wiercany");

    cout << endl;
    //set<string> result = o1.getCitiesInCounty("lezajsk");
    //set<string> result = o1.getCitiesInRegion("podk");
    set<string> result = o1.getCountries("podk");

    for(auto it=result.begin();it!=result.end();it++)
    {
        cout << *it << " ";
    }
    cout << endl;

}