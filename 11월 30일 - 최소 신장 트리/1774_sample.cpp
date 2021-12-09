// 우주신과의 교감 https://www.acmicpc.net/problem/1774

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;
typedef pair<double, double> ci;
typedef tuple<double, int, int> tp;

vector<int> parent; // 각 노드가 속한 트리의 부모 노드를 가리키는 배열

// Find 연산
int findParent(int node)
{
    if (parent[node] < 0)                           // 값이 음수면
        return node;                                // node는 루트 정점
    return parent[node] = findParent(parent[node]); // 그래프 압축하며 루트 정점 찾기
}

// Union 연산
bool unionInput(int x, int y)
{
    int xp = findParent(x); // x의 부모 노드
    int yp = findParent(y); // y의 부모 노드

    // x, y의 부모 노드가 같은 집합에 있다면
    if (xp == yp)
        return false; // 유니온 실패

    // xp의 자식 노드 개수가 더 많다면
    if (parent[xp] < parent[yp])
    {
        parent[xp] += parent[yp]; // yp의 트리가 xp의 서브 트리가 됨
        parent[yp] = xp;          // 새로운 루트 xp
    }
    // yp의 자식 노드 개수가 더 많다면
    else
    {
        parent[yp] += parent[xp]; // xp의 트리가 yp의 서브 트리가 됨
        parent[xp] = yp;          // 새로운 루트 yp
    }
    return true; // 유니온 성공
}

// 만들어야 할 최소 통로 길이(MST의 모든 간선의 가중치 합)를 계산하는 함수
double kruskal(int v, priority_queue<tp, vector<tp>, greater<>> &pq)
{
    int cnt = 0;    // 사용된 간선 개수
    double sum = 0; // 간선의 가중치 합

    // 사용한 간선의 수가 v-1보다 적을 동안
    while (cnt < v - 1)
    {
        double cost = get<0>(pq.top()); // 간선의 가중치 (통로의 거리)
        int x = get<1>(pq.top());       // 연결된 우주신 1
        int y = get<2>(pq.top());       // 연결된 우주신 2
        pq.pop();                       // 사용한 원소(간선) 목록에서 제거

        // 유니온 했다면
        if (unionInput(x, y))
        {
            cnt++;       // 사용된 간선 증가
            sum += cost; // 간선의 가중치 합에 더해줌
        }
    }
    return sum; // 모든 간선의 가중치 합 리턴
}

/**
 * 4386번 : 별자리 만들기의 응용 문제
 * 이미 연결된 정점들이 존재한다는 것을 제외하고는 4386번과 동일
 *
 * 1. 임의의 두 별에 대한 거리(간선) 모두 구하기
 * 2. 이미 존재하는 통로들 표시
 *    !주의! 통로의 개수가 m개라면 v-m-1개의 간선만 더 추가하면 될까?
 *          이미 연결된 통로들도 사이클을 이룰 수 있기 때문에 유니온 연산을 하며 사이클 없이 연결된 간선만 세기
 * 3. 이미 연결된 통로의 수를 k개라고 하면 v-k-1개의 간선을 추가로 선택
 */
int main()
{
    int n, m, a, b, v = 0;
    // 거리가 짧은 순으로 만들 수 있는 통로들을 저장
    priority_queue<tp, vector<tp>, greater<>> pq; // <거리, 우주신 1, 우주신 2>

    // 입력
    cin >> n >> m;
    parent.assign(n + 1, -1); // 자기 자신을 루트 정점으로 초기화
    vector<ci> stars(n + 1);  // 우주신들의 위치
    // 우주신들의 위치 입력
    for (int i = 1; i <= n; i++)                  // i: 우주신의 번호
        cin >> stars[i].first >> stars[i].second; // 우주신 i의 행, 열 위치

    // 연산
    // 임의의 두 우주신에 대한 거리(간선의 가중치) 모두 구하기
    for (int i = 1; i <= n - 1; i++) // i: 첫 번째 우주신 번호
    {
        for (int j = i + 1; j <= n; j++) // j: 두 번째 우주신 번호
        {
            double xd = stars[i].first - stars[j].first;   // x 좌표축에서의 거리
            double yd = stars[i].second - stars[j].second; // y 좌표축에서의 거리
            pq.push({sqrt(xd * xd + yd * yd), i, j});      // 통로 정보 저장
        }
    }
    // 이미 연결된 통로들 입력
    while (m--)
    {
        cin >> a >> b;        // 연결된 두 우주신
        if (unionInput(a, b)) // 이미 연결된 통로
            v++;              // 만들어진 통로의 개수 증가
    }

    //연산 & 출력
    cout << fixed;              // 출력 설정
    cout.precision(2);          // 소수점 둘째자리까지
    cout << kruskal(n - v, pq); // 만들어야 할 최소 통로 길이 출력
}