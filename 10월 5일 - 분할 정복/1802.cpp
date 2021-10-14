// 종이 접기 https://www.acmicpc.net/problem/1802

#include <iostream>
#include <string>

using namespace std;

bool canFolding(const string paper)
{
    // Conquer: 문자열의 길이가 1
    if (paper.length() == 1)
        return true;

    // Combine: mid를 기준으로 접을 수 있는지 확인
    int mid = paper.length() / 2;
    for (int i = 1; i <= mid; i++)
        if (paper[mid - i] == paper[mid + i])
            return false;

    // Divide: 문자열을 절반으로 나누기
    // 이미 mid를 기준으로 좌우가 반대임을 확인했기 때문에 한 쪽만 확인하면 됨
    return canFolding(paper.substr(0, mid));
}

int main()
{
    int t; // 테스트 케이스 개수

    // 입력
    cin >> t;
    while (t--)
    {
        string paper;
        cin >> paper;

        if (canFolding(paper))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}