#include <iostream>
#include <algorithm>
using namespace std;
int max(int n1, int n2, int n3)
{
    int m = n1;
    if (m < n2)
        m = n2;
    if (m < n3)
        m = n3;
    return m;
}

int main()
{
    cout <<""<< endl;
    return 0;
}