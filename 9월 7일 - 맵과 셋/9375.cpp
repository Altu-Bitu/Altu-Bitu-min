// 패션왕 신해빈 https://www.acmicpc.net/problem/9375

#include <iostream>
#include <utility>
#include <map>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, result = 1;
        map<string, int> closet; // <의상의 종류, 해당 종류 의상 개수>
        pair<string, string> clothes;

        // 각 테스트 케이스 입력
        cin >> n;
        while (n--)
        {
            cin >> clothes.first >> clothes.second;
            // 종류 별로 의상 개수 증가
            closet[clothes.second]++;
        }

        // 가진 옷들의 조합의 수 계산
        for (auto it = closet.begin(); it != closet.end(); it++)
            result *= (it->second + 1);

        // 알몸인 경우 제외하고 출력
        cout << result - 1 << '\n';
    }
}