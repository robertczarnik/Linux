#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n,x;
    vector<int> liczby;
    cin >> n;

    for(int i=0;i<n;i++) {
        cin >> x;
        liczby.push_back(x);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            for(int k=j+1;k<n;k++)
            {
                cout << liczby[i] << " " << liczby[j] << " " << liczby[k] << endl;
            }
        }
    }
}