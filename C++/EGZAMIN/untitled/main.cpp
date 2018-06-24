#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> k;
    k.resize(10,1);
    for(int i=0;i<k.size();i++){
        printf("k[%d]=%d (%p)\n",i,k[i],&k[i]);
    }

}