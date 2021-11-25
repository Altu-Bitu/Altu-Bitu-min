// 트리의 높이와 너비 https://www.acmicpc.net/problem/2250
// 샘플 코드 https://github.com/Altu-Bitu/Notice/blob/main/11%EC%9B%94%2016%EC%9D%BC%20-%20%ED%8A%B8%EB%A6%AC/%EA%B3%BC%EC%A0%9C/2250.cpp

#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int INF = 1e4 + 1;

map<int, pair<int, int>> tree;       // 이진 트리
vector<int> level_left, level_right; // 레벨 i에서의 가장 왼쪽/오른쪽 노드의 열 번호 저장
int width;                           // 열 번호

// 너비가 가장 넓은 레벨 구하는 함수
pair<int, int> findMaxWidth(int level)
{
    int ans_width = 1, ans_level = 1; // 가장 넓은 너비와 해당 레벨
    // 다음 레벨이 존재하지 않으면 종료
    while (level_right[++level] != 0)
    {
        // 해당 레벨의 너비 계산
        int level_width = level_right[level] - level_left[level] + 1;
        // 현재까지의 최대 너비보다 해당 레벨의 너비가 더 크다면
        if (ans_width < level_width)
        {
            ans_width = level_width; // 최대 너비 갱신
            ans_level = level;       // 레벨 갱신
        }
    }
    // 너비가 가장 넓은 레벨과 너비 리턴
    return {ans_level, ans_width};
}

// 중위 순회를 하며 열 번호 구하는 함수
void inorder(int node, int level)
{
    // 기저 조건
    if (node == -1) // 비어 있는 노드에 도착하면 리턴
        return;

    inorder(tree[node].first, level + 1);                  // 왼쪽 서브 트리 순회
    level_left[level] = min(level_left[level], width);     // 해당 레벨의 가장 왼쪽 노드 열 번호 갱신
    level_right[level] = max(level_right[level], width++); // 해당 레벨의 가장 오른쪽 노드 열 번호 갱신 및 열 번호 증가
    inorder(tree[node].second, level + 1);                 // 오른쪽 서브 트리 순회
}

// 루트 노드 찾는 함수
int findRoot(int n, vector<int> &node_cnt)
{
    // 1번 노드부터 n번 노드까지
    for (int i = 1; i <= n; i++)
        // 카운트가 1이면 root 노드
        if (node_cnt[i] == 1)
            return i; // root 노드의 번호 리턴
}

/**
 * tree: key 값을 부모 노드로 해서 value에 왼쪽, 오른쪽 자식노드를 저장
 * level_left: 레벨을 인덱스로 해당 레벨의 가장 왼쪽 노드의 열 번호 저장
 * level_right: 레벨을 인덱스로 해당 레벨의 가장 오른쪽 노드의 열 번호 저장
 *
 * 루트 노드가 1이 아닐 수 있으므로 루트 노드를 찾아주고 시작해야 함 -> 부모 노드가 없으면 루트 노드 -> 입력으로 한 번 주어진 경우 루트 노드
 * 각 노드의 열 번호는 중위 순회를 했을 때, 출력 순서와 같음 -> 이를 이용해서 중위 순회를 하며 가장 작은 열 번호와 큰 열 번호를 구함
 */

int main()
{
    // 노드의 개수, 노드 번호, 왼쪽 자식 노드 번호, 오른쪽 자식 노드 번호
    int n, p, l, r;

    // 노드의 개수 입력
    cin >> n;
    level_left.assign(n + 1, INF);  // 레벨은 최대 n개이므로 벡터 n+1 크기 할당
    level_right.assign(n + 1, 0);   // 최대 레벨 개수에 맞게 벡터 크기 할당
    vector<int> node_cnt(n + 1, 0); // 루트 노드 찾기 위해서 카운트 저장
    for (int i = 0; i < n; i++)
    {
        // 노드 정보 입력
        cin >> p >> l >> r;
        node_cnt[p]++; // 해당 번호를 가진 노드의 카운트 증가

        if (l != -1)       // 왼쪽 자식 노드가 존재한다면
            node_cnt[l]++; // 왼쪽 자식 노드의 카운트 증가

        if (r != -1)       // 오른쪽 자식 노드가 존재한다면
            node_cnt[r]++; // 오른쪽 자식 노드의 카운트 증가

        // 트리에 노드 삽입
        tree[p] = make_pair(l, r);
    }

    // 연산
    int root = findRoot(n, node_cnt);     // 루트 노드의 번호
    inorder(root, 1);                     // 중위 순회하며 열 번호 계산
    pair<int, int> ans = findMaxWidth(0); // 너비가 가장 넓은 레벨과 너비 계산

    //출력
    cout << ans.first << ' ' << ans.second << '\n';
    return 0;
}