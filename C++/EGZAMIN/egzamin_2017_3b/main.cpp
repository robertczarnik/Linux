#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int m,n,x;
    cin >> m;
    cin >> n;

    vector<int> l1,l2;

    for(int i=0;i<m;i++)
    {
        cin >> x;
        l1.push_back(x);
    }

    for(int i=0;i<n;i++)
    {
        cin >> x;
        l2.push_back(x);
    }

    sort(l1.begin(),l1.end());

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(l1[i]==l2[j])
                cout << l1[i] << " ";
        }
    }

}