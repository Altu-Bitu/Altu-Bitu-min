// ATM https://www.acmicpc.net/problem/11399

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, result = 0;
    vector<int> p;

    cin >> n;
    p.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> p[i];

    sort(p.begin(), p.end());
    for (int i = 0; i < n; i++)
        result += ((n - i) * p[i]);

    cout << result << endl;
    return 0;
}