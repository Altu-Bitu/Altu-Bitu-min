// 카드 합체 놀이 https://www.acmicpc.net/problem/15903

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n, m, card;
    priority_queue<long long, vector<long long>, greater<>> cards;

    // 입력
    cin >> n >> m;
    while (n--)
    {
        cin >> card;
        cards.push(card);
    }

    // 제일 작은 카드 2개를 더하고 덮어씀
    while (m--)
    {
        long long x = cards.top();
        cards.pop();
        long long y = cards.top();
        cards.pop();
        cards.push(x + y);
        cards.push(x + y);
    }

    // 모든 카드의 총합 계산
    long long sum = 0;
    while (!cards.empty())
    {
        sum += cards.top();
        cards.pop();
    }

    // 출력
    cout << sum;
    return 0;
}