// 보물 https://www.acmicpc.net/problem/1026

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, result = 0;
    vector<int> a, b;

    cin >> n;
    a.assign(n, 0);
    b.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());

    for (int i = 0; i < n; i++)
        result += (a[i] * b[i]);
    cout << result << endl;
}