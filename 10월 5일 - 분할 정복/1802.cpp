// 종이 접기 https://www.acmicpc.net/problem/1802

#include <iostream>
#include <string>

using namespace std;

bool canFolding(const string paper)
{
    int mid = paper.length() / 2;
    if (paper.length() <= 3)
    {
        if (paper.length() == 3 && paper[mid - 1] == paper[mid + 1])
            return false;
        return true;
    }

    if (canFolding(paper.substr(0, mid)) && canFolding(paper.substr(mid + 1)))
        return true;
    return false;
}

int main()
{
    int t; // 테스트 케이스 개수

    // 입력
    cin >> t;
    cin.ignore();
    while (t--)
    {
        string paper;
        getline(cin, paper);

        if (canFolding(paper))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}