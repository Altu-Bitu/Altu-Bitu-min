// MST 게임 https://www.acmicpc.net/problem/16202

#include <iostream>
#include <vector>

using namespace std;

// 파인드 연산
int findParent(vector<int> &parent, int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

// 유니온 연산
bool unionInput(vector<int> &parent, int x, int y)
{
    int xp = findParent(parent, x);
    int yp = findParent(parent, y);

    if (xp == yp)
        return false;

    if (parent[xp] < parent[yp])
    {
        parent[xp] += parent[yp];
        parent[yp] = xp;
    }
    else
    {
        parent[yp] += parent[xp];
        parent[xp] = yp;
    }
    return true;
}

// MST를 만들고 그 비용을 계산하는 함수
int calcMSTCost(int n, int m, vector<pair<int, int>> &edges, int turn)
{
    vector<int> parent(n + 1, -1); // 각 노드가 속한 트리의 부모 노드를 저장하는 배열
    int cost = 0;                  // MST의 비용
    int cnt = 0;                   // MST의 간선 개수

    // turn번째 턴에서 turn-1개의 가중치가 최소인 간선을 제거해야 하므로
    // turn번째 간선부터 MST 연산 시작
    for (int i = turn; i <= m && cnt < n - 1; i++)
    {
        if (unionInput(parent, edges[i].first, edges[i].second))
        {
            cnt++;
            cost += i;
        }
    }
    // MST를 만들 수 없다면 0 리턴
    return (cnt < n - 1) ? 0 : cost;
}

int main()
{
    int n, m, k;

    // 입력
    cin >> n >> m >> k;
    vector<pair<int, int>> edges(m + 1, {0, 0}); // 간선 정보
    for (int i = 1; i <= m; i++)
        cin >> edges[i].first >> edges[i].second;

    // 연산 및 출력
    for (int i = 1; i <= k; i++)
    {
        int cost = calcMSTCost(n, m, edges, i);
        cout << cost << ' ';

        // MST를 만들 수 없다면
        if (!cost)
        {
            // 남은 턴 모두 0 출력
            for (int j = i + 1; j <= k; j++)
                cout << 0 << ' ';
            break;
        }
    }
    return 0;
}