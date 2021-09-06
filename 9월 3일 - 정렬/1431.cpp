// 시리얼 번호 https://www.acmicpc.net/problem/1431

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

bool compSerials(string a, string b)
{
    if (a.length() != b.length())
        return a.length() < b.length();
    int sumA = 0, sumB = 0;
    for (int i = 0; i < a.length(); i++)
    {
        if (isdigit(a[i]))
            sumA += (a[i] - '0');
        if (isdigit(b[i]))
            sumB += (b[i] - '0');
    }
    if (sumA != sumB)
        return sumA < sumB;
    return a < b;
}

int main()
{
    int n;
    vector<string> serials;

    cin >> n;
    serials.assign(n, "");
    for (int i = 0; i < n; i++)
        cin >> serials[i];

    sort(serials.begin(), serials.end(), compSerials);

    for (int i = 0; i < n; i++)
        cout << serials[i] << endl;
    
    return 0;
}
