#include <iostream>
#include <vector>
#include <algorithm>
using  namespace std;

int main() {
    int n;
    double zm;
    vector<double> x;
    vector<double> y;
    vector<double> time;
    cin >> n;

    for(int i=0; i<n;i++)
    {
        cin >> zm;
        x.push_back(zm);

        cin >> zm;
        y.push_back(zm);

        cin >> zm;
        time.push_back(zm);
    }

    double droga = sqrt((x[n-1]-x[0])*(x[n-1]-x[0]) + (y[n-1]-y[0])*(y[n-1]-y[0]));
    double predkosc = droga/(time[n-1]-time[0]);

    cout << droga << " " << predkosc << endl;
}