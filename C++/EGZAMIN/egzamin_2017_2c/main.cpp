#include <iostream>
using  namespace std;

class PointGPS{
public:
    double x;
    double y;
    double time;
};

class GPSTrace{
public:
    PointGPS *tab;
    int size;
    int num;

    GPSTrace() {
        tab = nullptr;
        size = 0;
        num = 0;
    }

    ~GPSTrace() {
        if(tab != nullptr) {
            delete[] tab;
            tab = nullptr;
        }
    }

    bool add(double x, double y, double time)
    {
        if(size==0) {
            tab = new PointGPS[1];
            size = 1;

            tab[num].x=x;
            tab[num].y=y;
            tab[num].time=time;
            num++;
            return true;
        }

        if(tab[num-1].time>time)
            return false;

        if(size==num) {
            PointGPS *new_tab = new PointGPS[size*2];
            size=size*2;

            for(int i=0;i<size;i++) {
                new_tab[i]=tab[i];
            }

            delete [] tab;
            tab = new_tab;
        }

        tab[num].x=x;
        tab[num].y=y;
        tab[num].time=time;
        num++;

        return true;
    }

    GPSTrace(const GPSTrace &o1) {
        tab = nullptr;
        *this=o1;
    }

    GPSTrace &operator=(const GPSTrace &o1) {
        if(this==&o1) {
            return *this;
        }

        (*this).~GPSTrace();

        tab = new PointGPS[o1.size];
        size=o1.size;
        num=o1.num;
        for(int i=0;i<size;i++) {
            tab[i].x=o1.tab[i].x;
            tab[i].y=o1.tab[i].y;
            tab[i].time=o1.tab[i].time;
        }
    }

    void show() {
        for(int i=0;i<num;i++) {
            cout << tab[i].x << " " << tab[i].y << " " << tab[i].time << endl;
        }
    }
};

int main() {
    GPSTrace o1;
    o1.add(1,1,0);
    o1.add(1,1,1);
    o1.add(1,1,2);
    o1.add(1,1,1);
    o1.add(1,7,12);

    GPSTrace o2(o1);
    o2.show();
    cout << endl;

    o2.add(1,1.1,7);
    o2.add(1,5,14);
    o2.add(1.12,23.2,16.8);

    o1=o2;

    o1.show();
}