// 리그 오브 레게노 https://www.acmicpc.net/problem/23059

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

// 아이템 구매 순서를 구하는 함수
vector<string> drawItemTree(map<string, vector<string>> &graph, map<string, int> &indegree)
{
    vector<string> item_tree;                                                   // 아이템 구매 순서
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq; // <구매 순서, 아이템 이름>

    // 초기화
    for (auto it = indegree.begin(); it != indegree.end(); it++)
        if (!(it->second))           // 진입 차수가 0인 아이템 큐에 삽입
            pq.push({0, it->first}); // 순서는 0으로 초기화

    while (!pq.empty())
    {
        int order = pq.top().first;    // 구매 순서
        string item = pq.top().second; // 아이템 이름
        pq.pop();

        item_tree.push_back(item);
        vector<string> next_items = graph[item]; // 해당 아이템과 연결된 다음 아이템들
        for (string next_item : next_items)
            if (--indegree[next_item] == 0)      // 연결된 다음 아이템들의 진입 차수 1씩 감소
                pq.push({order + 1, next_item}); // 진입 차수가 0이라면 큐에 삽입
    }
    return item_tree;
}

int main()
{
    // 입력
    int n;
    map<string, vector<string>> graph; // 아이템 구매 순서를 나타내는 방향 그래프
    map<string, int> indegree;         // 아이템의 진입 차수
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string item1, item2;
        cin >> item1 >> item2;
        graph[item1].push_back(item2); // 그래프에 관계 저장 (item1 -> item2)
        if (indegree.count(item1) == 0)
            indegree[item1] = 0; // item1이 진입 차수가 0이어도 맵에 저장
        indegree[item2]++;       // item2의 진입 차수 증가
    }

    // 연산
    vector<string> item_tree = drawItemTree(graph, indegree); // 아이템 구매 순서

    // 모든 아이템을 구매할 수 없는 경우
    if (item_tree.size() != indegree.size())
    {
        cout << -1;
        return 0;
    }
    // 출력
    for (string item : item_tree)
        cout << item << '\n';
}