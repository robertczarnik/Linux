#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Word{
public:
    string text;
    string lang;
};

class Meaning {
public:
    Word* first;
    Word* second;
};

class Dict {
public:
    vector<Word> words;
    vector<Meaning> meanings;

    Dict()
    {

    }

    Word* addWord(const char*txt, const char*lan) // b
    {
        for(vector<Word>::iterator it=words.begin();it!=words.end();it++)
        {
            if(it->text==txt && it->lang==lan)
                return &(*it);
        }

        Word* o1 = new Word;
        o1->text=txt;
        o1->lang=lan;

        words.push_back(*o1);
        return o1;
    }

    void addMeaning(const char*t1, const char*lan1,const char*t2, const char*lan2)
    {
        Meaning *o1 = new Meaning;

        for(vector<Word>::iterator it=words.begin();it!=words.end();it++)
        {
            if(it->text==t1 && it->lang==lan1)
            {
                o1->first = &(*it);
            }

            if(it->text==t2 && it->lang==lan2)
            {
                o1->second = &(*it);
            }
        }

        meanings.push_back(*o1);
    }

    void removeWord(const char*txt,const char*lan)
    {
        for(vector<Meaning>::iterator it=meanings.begin();it!=meanings.end();it++)
        {
            if((it->first->text==txt && it->first->lang==lan) || (it->second->text==txt && it->second->lang==lan))
            {
                meanings.erase(it);
            }
        }

        for(vector<Word>::iterator it=words.begin();it!=words.end();it++)
        {
            if(it->text==txt && it->lang==lan)
            {
                words.erase(it);
                break;
            }
        }
    }

    list<string> getAllWordsInLang(string lang)
    {
        list<string> lista;

        for(vector<Word>::iterator it=words.begin();it!=words.end();it++)
        {
            if(it->lang==lang)
            {
                lista.push_back(it->text);
            }
        }

        return lista;
    }

    list<Word> getAllMeaningsInLang(const char*txt,const char*lan)
    {
        list<Word> lista;

        for(vector<Meaning>::iterator it=meanings.begin();it!=meanings.end();it++)
        {
            if(it->first->text==txt && it->first->lang==lan)
            {
                lista.push_back(*it->second);
            }

            if(it->second->text==txt && it->second->lang==lan)
            {
                lista.push_back(*it->first);
            }
        }

        return lista;
    }
};

int main() {
    Dict o1;
    list<string> slowa_jezyk;
    list<Word> slowa_znaczenia;


    o1.addWord("krzeslo","pl");
    o1.addWord("jajko","pl");
    o1.addWord("ptak","pl");
    o1.addWord("egg","eng");
    o1.addWord("bird","eng");
    o1.addWord("ptaszor","rus");

    o1.addMeaning("jajko","pl","egg","eng");
    o1.addMeaning("ptak","pl","bird","eng");
    o1.addMeaning("ptak","pl","ptaszor","rus");

    o1.removeWord("jajko","pl");

    slowa_jezyk=o1.getAllWordsInLang("pl");

    for(list<string>::iterator it=slowa_jezyk.begin();it!=slowa_jezyk.end();it++)
    {
        cout << *it << endl;
    }

    slowa_znaczenia = o1.getAllMeaningsInLang("ptak","pl");


    for(list<Word>::iterator it=slowa_znaczenia.begin();it!=slowa_znaczenia.end();it++)
    {
        cout << it->text << " " << it->lang << endl;
    }
    cout << "asdas";
    return 0;
}