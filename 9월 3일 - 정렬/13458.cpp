// 시험 감독 https://www.acmicpc.net/problem/13458

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, b, c;
    vector<int> a;
    long long result = 0;

    cin >> n;
    a.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> b >> c;

    for (int i = 0; i < n; i++)
    {
        result++;
        int rest = a[i] - b;
        if (rest > 0)
        {
            result += rest / c;
            if (rest % c > 0)
                result++;
        }
    }
    cout << result << endl;
}