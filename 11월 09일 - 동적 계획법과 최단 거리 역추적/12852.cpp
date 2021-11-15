// 1로 만들기 2 https://www.acmicpc.net/problem/12852

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// path를 추적해서 result에 담아내는 함수
vector<int> tracePath(vector<int> &path)
{
    vector<int> result;
    result.push_back(1);
    int n = path[1];
    while (n != 0)
    {
        result.push_back(n);
        n = path[n];
    }
    return result;
}

// N을 1로 만들 때까지 사용된 연산 횟수의 최솟값을 구하는 함수
int NtoOne(int n, vector<int> &path)
{
    vector<int> time(n + 1, 0); // time[i]: N이 i가 될 때까지 사용된 연산 횟수
    queue<int> q;               // BFS를 위한 큐
    q.push(n);

    while (true)
    {
        int x = q.front();
        q.pop();

        // N이 1이 되면 종료
        if (x == 1)
            break;

        int new_x;
        // 3으로 나누는 연산
        if (x % 3 == 0)
        {
            new_x = x / 3;
            // new_x가 아직 도착하지 않은 수라면
            if (!path[new_x])
            {
                path[new_x] = x;           // new_x의 직전 노드(연산 이전 수) 기록
                time[new_x] = time[x] + 1; // new_x까지의 연산 횟수 기록
                q.push(new_x);
            }
        }
        // 2로 나누는 연산
        if (x % 2 == 0)
        {
            new_x = x / 2;
            if (!path[new_x])
            {
                path[new_x] = x;
                time[new_x] = time[x] + 1;
                q.push(new_x);
            }
        }
        // 1을 빼는 연산
        new_x = x - 1;
        if (new_x > 0 && !path[new_x])
        {
            path[new_x] = x;
            time[new_x] = time[x] + 1;
            q.push(new_x);
        }
    }
    return time[1];
}

int main()
{
    int n;

    // 입력
    cin >> n;
    vector<int> path(n + 1, 0); // 역추적을 위해 해당 노드의 직전 노드를 저장하는 벡터

    // 연산
    int num = NtoOne(n, path);            // N을 1로 만들 때까지 사용된 연산 횟수의 최솟값
    vector<int> result = tracePath(path); // path를 역추적한 결과를 저장하는 벡터

    // 출력
    cout << num << '\n';
    for (int i = result.size() - 1; i >= 0; i--)
        cout << result[i] << ' ';
    return 0;
}