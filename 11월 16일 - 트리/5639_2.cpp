// 이진 검색 트리 https://www.acmicpc.net/problem/5639
// 풀이 2 트리 구성 풀이
// https://github.com/Altu-Bitu/Notice/blob/main/11%EC%9B%94%2016%EC%9D%BC%20-%20%ED%8A%B8%EB%A6%AC/%EA%B3%BC%EC%A0%9C/5639_1.cpp

#include <iostream>

using namespace std;

// 노드 구조체 정의
struct node_info
{
    int data;         // 노드의 값
    node_info *left;  // 노드의 왼쪽 자식
    node_info *right; // 노드의 오른쪽 자식
};

// 트리를 구성하는 함수
node_info *makeTree(node_info *node, int data)
{
    // 현재 노드가 NULL이면
    if (node == NULL)
    {
        // 현재 위치에 새 노드가 들어감
        node = new node_info();          // 새 노드 동적 할당
        node->data = data;               // 새 노드에 입력 받은 값 저장
        node->left = node->right = NULL; // 새 노드의 양쪽 자식을 NULL로 초기화
    }
    // 현재 노드보다 새 노드 값이 작다면
    else if (node->data > data)
    {
        // 왼쪽 서브트리로 이동
        node->left = makeTree(node->left, data);
    }
    // 현재 노드보다 새 노드 값이 크다면
    else if (node->data < data)
    {
        //오른쪽 서브트리로 이동
        node->right = makeTree(node->right, data);
    }
    // 트리의 root node가 리턴됨
    return node;
}

// 후위 순회 함수
void postorder(node_info *node)
{
    // 기저 조건
    if (node == NULL)
        return; // 비어 있는 노드에 도착했으면 리턴

    postorder(node->left);      // 왼쪽 서브 트리 순회
    postorder(node->right);     // 오른쪽 서브 트리 순회
    cout << node->data << '\n'; // 현재 노드 출력
}

/**
 * 맵과 셋 PPT 중 BST 노드 삽입 과정 참고
 *
 * 트리 구성 풀이
 * 1. 포인터로 왼쪽, 오른쪽 서브트리를 가리키는 구조체 선언
 * 2. NULL 만날 때까지 조건에 따라 왼쪽 또는 오른쪽으로 이동
 * 3. 노드가 들어갈 위치를 찾으면 동적할당 후 노드 만들기
 * 4. 완성한 트리를 후위 순회
 */
int main()
{
    // 입력 받은 노드의 값
    int input;

    // 입력 & 연산
    node_info *root = NULL;
    // eof 까지 입력 받음
    while (cin >> input)
        // 입력 받은 값을 BST에 삽입
        root = makeTree(root, input);

    // 출럭
    postorder(root);
}