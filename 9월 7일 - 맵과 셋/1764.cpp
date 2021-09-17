// 듣보잡 https://www.acmicpc.net/problem/1764

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    int n, m;
    string name;
    set<string> list;   // 듣도 못한 사람 명단
    set<string> result; // 듣도 보도 못한 사람 명단

    // 듣도 못한 사람 명단 입력
    cin >> n >> m;
    while (n--)
    {
        cin >> name;
        list.insert(name);
    }

    // 보도 못한 사람이 듣도 못한 사람 명단에 있는지 확인
    while (m--)
    {
        cin >> name;
        if (list.count(name) != 0)
            result.insert(name);
    }

    // 듣도 보도 못한 사람 명단 출력
    cout << result.size() << '\n';
    for (string str: result)
        cout << str << '\n';
}