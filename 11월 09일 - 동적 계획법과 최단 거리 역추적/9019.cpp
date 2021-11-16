// DSLR https://www.acmicpc.net/problem/9019

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 9999;

vector<char> AtoB(const int a, const int b)
{
    vector<int> commands = {'D', 'S', 'L', 'R'};
    vector<pair<int, char>> path(MAX_N + 1, {-1, ' '}); // <직전 숫자, 현재 숫자로 방문할 때 사용한 연산>
    queue<int> q;
    q.push(a);
    int num;

    while (!q.empty())
    {
        num = q.front();
        q.pop();

        // B에 도착하면 종료
        if (num == b)
            break;

        vector<int> nexts = {
            (num * 2) % (MAX_N + 1),
            (num == 0) ? MAX_N : num - 1,
            (num % 1000 * 10) + (num / 1000),
            (num % 10 * 1000) + (num / 10)};

        for (int i = 0; i < 4; i++)
        {
            if (path[nexts[i]].first == -1)
            {
                path[nexts[i]] = make_pair(num, commands[i]);
                q.push(nexts[i]);
            }
        }
    }

    // A에서 B에 도착할 때까지 사용된 명령어 역추적
    vector<char> answer;
    while (num != a)
    {
        answer.push_back(path[num].second);
        num = path[num].first;
    }
    return answer;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        // 입력
        int a, b;
        cin >> a >> b;
        // 연산 및 출력
        vector<char> answer = AtoB(a, b);
        for (int i = answer.size() - 1; i >= 0; i--)
            cout << answer[i];
        cout << '\n';
    }
    return 0;
}