// 이진 검색 트리 https://www.acmicpc.net/problem/5639
// 풀이 1 분할 정복 풀이
// https://github.com/Altu-Bitu/Notice/blob/main/11%EC%9B%94%2016%EC%9D%BC%20-%20%ED%8A%B8%EB%A6%AC/%EA%B3%BC%EC%A0%9C/5639_1.cpp

#include <iostream>
#include <vector>

using namespace std;

// 후위 순회 함수
void postorder(int left, int right, vector<int> &nodes)
{
    if (left > right) // 기저 조건 : 왼쪽 경계가 오른쪽 경계 너머에 있음
        return;

    // 처음으로 root 노드보다 값이 커지는 위치
    // 오른쪽 서브 트리의 루트 노드의 인덱스
    int idx = right + 1;
    for (int i = left; i <= right; i++)
    {
        // root 보다 i 번째 노드의 값이 크다면
        if (nodes[i] > nodes[left])
        {
            // 오른쪽 서브 트리의 루트 노드 인덱스 갱신
            idx = i;
            break;
        }
    }
    postorder(left + 1, idx - 1, nodes); // 왼쪽 서브 트리 순회
    postorder(idx, right, nodes);        // 오른쪽 서브 트리 순회
    cout << nodes[left] << '\n';         // 현재 노드 출력
}

/**
 * 분할 정복 - 4256번 참고
 *
 * 분할 정복 풀이
 * 1. 전위 순회는 root 노드의 위치는 알 수 있지만 왼쪽, 오른쪽 서브트리의 경계는 알 수 없음
 * 2. BST의 성질 : 왼쪽 서브트리의 모든 노드 값 < 루트 노드 값 < 오른쪽 서브트리의 모든 노드 값
 *    -> 처음으로 root 보다 값이 커진다면, 그 위치가 왼쪽, 오른쪽 서브트리의 경계
 * 3. 재귀함수 호출로 분할 반복하며 출력
 */
int main()
{
    int input;         // 입력 받은 노드의 값
    vector<int> nodes; // 전위 순회 결과

    // eof 까지 입력 받음
    while (cin >> input)
        // 입력
        nodes.push_back(input);

    // 연산 및 출력
    postorder(0, nodes.size() - 1, nodes);
}