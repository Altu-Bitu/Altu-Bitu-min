// 물대기 https://www.acmicpc.net/problem/1368

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int INF = 1e5 + 1;

// 모든 논에 물을 대는데 필요한 최소비용(MST 간선 가중치 총합)을 계산하는 함수
int prim(int size, int start, vector<vector<int>> &graph)
{
    int sum = 0;                                                          // 모든 논에 물을 대는데 필요한 최소 비용
    vector<int> dist(size, INF);                                          // 각 논까지의 비용
    vector<bool> visited(size, false);                                    // 논 방문 여부
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // <가중치, 정점> 가중치가 적은 순으로 저장

    dist[start] = 0;     // 시작점(수원)까지의 거리는 0으로 초기화
    pq.push({0, start}); // 우선순위 큐에 시작점 삽입

    // 우선순위 큐에 원소가 있는 동안 반복
    while (!pq.empty())
    {
        int cost = pq.top().first; // 간선 가중치
        int cur = pq.top().second; // 현재 논
        pq.pop();                  // 사용한 원소 큐에서 제거

        // 이미 확인했던 정점이라면
        if (visited[cur])
            continue; // 다음 정점으로 넘어감

        sum += cost;         // MST 간선 가중치 합에 더해줌
        visited[cur] = true; // 현재 정점 방문 처리

        for (int i = 0; i < size; i++) // i: 현재 논과 연결할 다른 논의 번호
        {
            // 미방문 정점이면서 더 적은 비용으로 연결할 수 있다면
            if (!visited[i] && graph[cur][i] < dist[i])
            {
                dist[i] = graph[cur][i]; // 논 i까지의 비용 갱신
                pq.push({dist[i], i});   // 다음 정점으로 삽입
            }
        }
    }
    return sum; // MST 간선 가중치 총합 리턴
}

/**
 * 각 논들 사이의 간선도 고려하고, 우물을 파는 경우도 고려? -> 복잡
 * 논에 추가로 모든 우물과 연결되는 수원이 있다고 가정!
 * ->직접 논에 우물을 파는 경우는 수원과 각 논 사이의 간선 가중치라고 할 수 있음
 *
 * 0 2 2 2 5
 * 2 0 3 3 4
 * 2 3 0 4 4
 * 2 3 4 0 3
 * 5 4 4 3 0
 *
 * 인덱스 0 ~ n-1은 논, 인덱스 n은 수원
 * 1개 이상의 논은 반드시 직접 우물을 파야 하므로 수원(n)에서 시작하는 프림 알고리즘
 */
int main()
{
    int n, w; // 논의 수, 비용

    // 논의 수 입력
    cin >> n;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0)); // 논과 논을 연결하는 비용

    for (int i = 0; i < n; i++) // i: 논의 번호
    {
        cin >> w;                      // 수원으로부터 물을 끌어오는 비용 (== 우물 파는 비용) 입력
        graph[i][n] = graph[n][i] = w; // 수원(n)과 논(i)을 연결하는 비용
    }

    for (int i = 0; i < n; i++) // i: 첫 번째 논의 번호
    {
        for (int j = 0; j < n; j++) // j: 두 번째 논의 번호
            cin >> graph[i][j];     // 두 논 사이에서 물을 끌어오는 비용 입력
    }

    cout << prim(n + 1, n, graph); // 수원에서 시작하는 프림 알고리즘
}