// 시리얼 번호 https://www.acmicpc.net/problem/1431

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int toDigit(char ch)
{
    if (isdigit(ch))
        return ch - '0';
    return 0;
}

bool compSerials(string a, string b)
{
    if (a.length() != b.length())
        return a.length() < b.length();
    int sumA = 0, sumB = 0;
    for (int i = 0; i < a.length(); i++)
    {
        sumA += toDigit(a[i]);
        sumB += toDigit(b[i]);
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
        cout << serials[i] << "\n";

    return 0;
}
