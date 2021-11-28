// 여행 가자 https://www.acmicpc.net/problem/1976

#include <iostream>
#include <vector>

using namespace std;

vector<int> parent; // 부모 노드를 가리키는 배열

// Find 연산
int findParent(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findParent(parent[x]);
}

// Union 연산
void unionInput(int a, int b)
{
    int ap = findParent(a);
    int bp = findParent(b);

    if (ap == bp)
        return;

    if (parent[ap] <= parent[bp])
    {
        parent[ap] += parent[bp];
        parent[bp] = ap;
    }
    else
    {
        parent[bp] += parent[ap];
        parent[ap] = bp;
    }
}

int main()
{
    int n, m; // 총 도시의 수, 여행 계획에 속한 도시의 수
    cin >> n >> m;
    parent.assign(n + 1, -1); // parent 배열 초기화

    // 도시 연결 정보 입력 및 Union 연산
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int is_connected;
            cin >> is_connected;
            // 두 도시가 무방향 연결되어 있기 때문에 한쪽 방향만 검사 (i < j 일 때)
            if (i < j && is_connected)
                unionInput(i, j); // 두 도시가 연결되어있다면 Union
        }

    // 여행 가능 여부 판단
    bool can_travel = true;
    int city; // 계획에 속한 도시
    cin >> city;
    int root = findParent(city); // 해당 도시와 연결된 도시들의 집합의 root
    while (--m && can_travel)
    {
        cin >> city;
        // 이전 도시와 같은 집합에 속하지 않는다면
        if (root != findParent(city))
            can_travel = false; // 연결된 길이 없다는 뜻이므로 여행 불가능
    }

    // 출력
    cout << (can_travel ? "YES" : "NO");
    return 0;
}