// 거짓말 https://www.acmicpc.net/problem/1043

#include <iostream>
#include <vector>

using namespace std;

vector<bool> truth; // 진실을 아는지 여부를 저장하는 배열
vector<int> parent; // 부모 노드를 가리키는 배열
vector<int> party;  // 각 파티의 첫 번째 참가자를 저장하는 배열

// find 연산
int findParent(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findParent(parent[x]);
}

// union 연산
void unionInput(int x, int y)
{
    int xp = findParent(x);
    int yp = findParent(y);

    // 한 쪽이라도 진실을 아는 집합에 속해있다면
    if (truth[xp] || truth[yp])
        truth[xp] = truth[yp] = true; // 다른 쪽 집합도 진실을 알게 됨

    if (xp == yp)
        return;
    if (parent[xp] <= parent[yp])
    {
        parent[xp] += parent[yp];
        parent[yp] = xp;
    }
    else
    {
        parent[yp] += parent[xp];
        parent[xp] = yp;
    }
}

// 거짓말을 할 수 있는 파티의 개수를 계산하는 함수
int countLies()
{
    int lies = 0;
    for (int idx = 0; idx < party.size(); idx++)
    {
        // idx번째 파티의 참가자가 속한 집합의 root
        int p = findParent(party[idx]);
        // root가 진실을 모른다면 카운트
        if (!truth[p])
            lies++;
    }
    return lies;
}

int main()
{
    // 사람 및 파티 개수 입력
    int n, m, num;
    cin >> n >> m;
    truth.assign(n + 1, false);
    parent.assign(n + 1, -1);
    party.assign(m, 0);

    // 진실을 아는 사람 정보 입력
    cin >> n;
    while (n--)
    {
        cin >> num;
        truth[num] = true;
    }

    // 각 파티 정보 입력
    for (int idx = 0; idx < m; idx++)
    {
        int first; // 첫 번째 파티 참가자
        cin >> n >> first;
        while (--n)
        {
            int p;
            cin >> p;
            // 파티 참가자들을 하나의 집합으로 union
            unionInput(first, p);
        }
        // 해당 파티의 참가자 1명을 저장
        party[idx] = first;
    }

    // 연산 및 출력
    cout << countLies();
    return 0;
}