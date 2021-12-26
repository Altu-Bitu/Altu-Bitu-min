// 음악프로그램 https://www.acmicpc.net/problem/2623

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 가수들의 전체 출연 순서를 정하는 함수
vector<int> setArtistOrder(int n, vector<vector<int>> &graph, vector<int> &indegree)
{
    vector<int> order; // 출연 순서
    queue<int> q;

    // 큐 초기화
    for (int i = 1; i <= n; i++)
        if (!indegree[i]) // 진입 차수가 0인 가수(정점)만
            q.push(i);    // 큐에 삽입

    while (!q.empty())
    {
        int artist = q.front();
        q.pop();

        order.push_back(artist);
        vector<int> next_artists = graph[artist]; // 해당 가수와 순서가 연결된 다음 가수들
        for (int next_artist : next_artists)
            if (--indegree[next_artist] == 0) // 다음 가수의 진입 차수 감소
                q.push(next_artist);          // 진입 차수가 0이면 큐에 삽입
    }
    return order;
}

int main()
{
    // 입력
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(0)); // 출연 순서를 나타내는 방향 그래프
    vector<int> indegree(n + 1, 0);                   // 각 정점(가수)들의 진입 차수
    // 출연 순서 입력
    while (m--)
    {
        int artist, num1, num2;
        cin >> artist >> num1;
        while (--artist)
        {
            cin >> num2;
            graph[num1].push_back(num2); // 그래프에 관계 저장 (num1 -> num2)
            indegree[num2]++;            // num2번 가수의 진입 차수 증가
            num1 = num2;
        }
    }

    // 연산
    vector<int> order = setArtistOrder(n, graph, indegree); // 가수들의 전체 출연 순서

    // 순서를 정하지 못하는 경우
    if (order.size() != n)
    {
        cout << 0;
        return 0;
    }
    // 출력
    for (int num : order)
        cout << num << '\n';
}