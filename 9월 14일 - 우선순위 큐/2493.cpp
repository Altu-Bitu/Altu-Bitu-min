// 탑 https://www.acmicpc.net/problem/2493

#include <iostream>
#include <stack>
#include <utility>

using namespace std;

/*
    0. cur: 현재 탑 높이
    0. towers: 현재 탑의 왼쪽에 있는 탑들을 저장(스택), 가장 큰 높이의 탑보다 왼쪽의 탑들은 저장 X
    1. towers.empty => '0' 출력(수신 가능한 탑이 없음), towers.push(cur)
    2. towers.top < cur => towers.pop(), 1번부터 다시 확인
    3. towers.top == cur => top의 인덱스 출력, towers.pop(), push(cur)
    4. towers.top > cur => top의 인덱스 출력, push(cur)
*/
int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;                        // 탑의 수
    pair<int, int> tower;         // 탑: <탑 높이, 탑 번호>
    stack<pair<int, int>> towers; // 왼쪽에 있는 탑들을 저장

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> tower.first;
        tower.second = i;

        while (true)
        {
            if (towers.empty())
            {
                cout << 0 << ' ';
                towers.push(tower);
                break;
            }
            if (towers.top().first < tower.first)
            {
                towers.pop();
                continue;
            }

            cout << towers.top().second << ' ';
            if (towers.top().first == tower.first)
                towers.pop();
            towers.push(tower);
            break;
        }
    }

    return 0;
}