// DSLR https://www.acmicpc.net/problem/9019

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 9999;

vector<char> AtoB(const int a, const int b)
{
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

        // D 연산 수행
        int d_num = (num * 2) % (MAX_N + 1);
        // D 연산 후 숫자가 아직 방문하지 않은 숫자라면
        if (path[d_num].first == -1)
        {
            // 경로 배열에 정보 입력 후 큐에 삽입
            path[d_num] = make_pair(num, 'D');
            q.push(d_num);
        }
        // S 연산 수행
        int s_num = (num == 0) ? MAX_N : num - 1;
        if (path[s_num].first == -1)
        {
            path[s_num] = make_pair(num, 'S');
            q.push(s_num);
        }
        // L 연산 수행
        int d1 = num / 1000;
        int l_num = (num % 1000) * 10 + d1;
        if (path[l_num].first == -1)
        {
            path[l_num] = make_pair(num, 'L');
            q.push(l_num);
        }
        // R 연산 수행
        int d4 = num % 10;
        int r_num = (d4 * 1000) + (num / 10);
        if (path[r_num].first == -1)
        {
            path[r_num] = make_pair(num, 'R');
            q.push(r_num);
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
        // 연산
        vector<char> answer = AtoB(a, b);
        // 연산 과정을 역추적했기 때문에 뒤에서부터 출력
        for (int i = answer.size() - 1; i >= 0; i--)
            cout << answer[i];
        cout << '\n';
    }
    return 0;
}