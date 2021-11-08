// 합승 택시 요금 https://programmers.co.kr/learn/courses/30/lessons/72413

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 100000 * 200;   // 최대 가중치는 최대 요금 * 최대 정점 수로 설정함

// 입력 받은 택시 요금을 인접 행렬로 변환하는 함수
vector<vector<int>> toAdjacentArray(int n, vector<vector<int>> &fares)
{
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));  // 인접 행렬

    // 자기 자신과의 거리는 0으로 초기화
    for (int i = 1; i <= n; i++)
        graph[i][i] = 0;

    // 인접 행렬에 가중치(택시 요금) 저장
    for (auto fare : fares)
    {
        int c = fare[0], d = fare[1], f = fare[2];
        graph[c][d] = graph[d][c] = f;
    }
    return graph;
}

// 플로이드 워셜을 이용해 ASP를 찾는 함수
void floydWarshall(int n, vector<vector<int>> &graph)
{
    for (int v = 1; v <= n; v++)         // 기준 정점 (중간 정점)
        for (int i = 1; i <= n; i++)     // 출발 정점
            for (int j = 1; j <= n; j++) // 도착 정점
            {
                int w = graph[i][v] + graph[v][j];
                graph[i][j] = min(graph[i][j], w);
            }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares)
{
    int answer = INF;   // 최저 예상 택시 요금

    // 입력 받은 택시 요금을 인접 행렬 형태로 변환
    vector<vector<int>> graph = toAdjacentArray(n, fares);
    // ASP 계산
    floydWarshall(n, graph);

    // v: 출발점에서부터 합승해 온 A와 B가 헤어지는 지점
    for (int v=1; v<=n; v++)
    {
        // 합승 요금 + 헤어진 지점부터 계산된 각자의 택시 요금
        int fare = graph[s][v] + graph[v][a] + graph[v][b];
        // 최저 예상 택시 요금 갱신
        answer = min(answer, fare);
    }
    return answer;
}

int main()
{
    int n = 6;
    int s = 4;
    int a = 6;
    int b = 2;
    vector<vector<int>> fares = {
        {4, 1, 10},
        {3, 5, 24},
        {5, 6, 2},
        {3, 1, 41},
        {5, 1, 24},
        {4, 6, 50},
        {2, 4, 66},
        {2, 3, 22},
        {1, 6, 25}};
    cout << solution(n, s, a, b, fares);
    return 0;
}