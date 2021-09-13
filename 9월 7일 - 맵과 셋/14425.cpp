// 문자열 집합 https://www.acmicpc.net/problem/14425

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    int n, m, result = 0;
    set<string> s;
    string str;

    // 입력
    cin >> n >> m;
    while (n--)
    {
        cin >> str;
        s.insert(str);
    }

    // 집합 s에 문자열이 존재하는지 확인
    while (m--)
    {
        cin >> str;
        if (s.count(str) != 0)
            result++;
    }

    cout << result;
}