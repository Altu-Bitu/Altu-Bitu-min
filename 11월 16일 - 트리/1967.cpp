// 트리의 지름 https://www.acmicpc.net/problem/1967
// 샘플 코드 https://github.com/Altu-Bitu/Notice/blob/main/11%EC%9B%94%2016%EC%9D%BC%20-%20%ED%8A%B8%EB%A6%AC/%EA%B3%BC%EC%A0%9C/1967.cpp

#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> ci;

// 지름을 구성하는 노드와 그 노드까지의 거리를 찾는 함수
ci dfs(int node, int parent, vector<vector<ci>> &graph)
{
    int pos = node, len = 0; // 지름을 구성하는 노드 중 하나, 그 노드까지의 거리
    for (int i = 0; i < graph[node].size(); i++)
    {
        // 현재 노드와 연결된 다음 노드
        int next_node = graph[node][i].first;
        // 다음 노드가 부모 노드와 같으면 건너뜀
        if (next_node == parent)
            continue;

        ci dfs_search = dfs(next_node, node, graph); // 자식 노드에 대해 dfs 탐색
        // 기존 거리보다 길다면
        if (graph[node][i].second + dfs_search.first > len)
        {
            // 길이와 노드 번호를 갱신
            len = graph[node][i].second + dfs_search.first;
            pos = dfs_search.second;
        }
    }
    // 최장 거리와 해당 노드 번호 리턴
    return {len, pos};
}

/**
 * 1. 지름을 이루는 두 점은 모두 리프 노드
 * 2. 임의의 한 노드에서 가장 멀리 있는 노드(리프 노드)는 지름을 이루는 노드 중 하나
 * 3. 지름을 이루는 노드에서 가장 멀리 있는 노드는 지름을 이루는 다른 노드
 *
 * 부모->자식의 방향만 저장하면 리프 노드에서 다른 리프 노드로 탐색할 수 없으므로 무방향 그래프로 저장
 */
int main()
{
    // 노드의 개수, 부모 노드 번호, 자식 노드 번호, 간선의 가중치
    int n, p, c, w;

    // 노드의 개수 입력
    cin >> n;
    vector<vector<ci>> graph(n + 1, vector<ci>(0)); // 그래프(트리) 초기화
    // 무방향 그래프로 만들기
    for (int i = 1; i < n; i++)
    {
        // 노드와 간선 정보 입력
        cin >> p >> c >> w;
        // 그래프에 입력 받은 노드 삽입
        // 무방향이므로 c -> p와 p -> c 모두 삽입
        graph[p].emplace_back(c, w);
        graph[c].emplace_back(p, w);
    }

    // 연산
    ci first_node = dfs(1, -1, graph);                  // 지름을 구성하는 노드 하나 찾기
    ci second_node = dfs(first_node.second, -1, graph); // 지름을 구성하는 다른 노드 찾기

    // 출력
    cout << second_node.first;
}