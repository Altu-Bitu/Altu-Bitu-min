// 시리얼 번호 https://www.acmicpc.net/problem/1431

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int toDigit(string str)
{
    int sum = 0;
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (isdigit(ch))
            sum += ch - '0';
    }
    return sum;
}

bool compSerials(string a, string b)
{
    if (a.length() != b.length())
        return a.length() < b.length();
    int sumA = toDigit(a), sumB = toDigit(b);
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
