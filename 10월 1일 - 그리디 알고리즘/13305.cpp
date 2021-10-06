// 주유소 https://www.acmicpc.net/problem/13305

#include <iostream>
#include <vector>

using namespace std;

/*
    1. 현재 주유소의 리터당 가격 < 다음 주유소의 리터당 가격 
        => 다음 도로를 건너는 양까지 현재 도시에서 주유
    2. 현재 주유소의 리터당 가격 >= i번째 주유소의 리터당 가격, 일 때까지 1번 반복
        => i번째 도시로 이동
    3. 마지막 도시에 도착하면 끝
*/

long long calcMinCost(vector<long long> &price, vector<int> &road_length)
{
    long long cost = 0; // 최소 비용
    int cur = 0;        // 현재 도시의 인덱스
    int next = 1;       // 다음 도시의 인덱스
    while (cur < price.size() - 1)
    {
        // 현재 도로(cur번째 마을과 cur+1번째 마을 사이 도로)를 건널 기름 주유
        cost += road_length[cur] * price[cur];

        // 현재 주유소의 리터당 가격 < 다음 주유소의 리터당 가격
        while (next < price.size() - 1 && price[cur] < price[next])
            // 다음 도로를 건너는 양까지 현재 도시에서 주유
            cost += road_length[next++] * price[cur];

        // 주유한 만큼 이동
        cur = next++;
    }
    return cost;
}

int main()
{
    int n;                   // 도시의 개수
    vector<long long> price; // 주유소의 리터당 가격
    vector<int> road_length; // 도로의 길이 (i번째 도로: i번째 도시와 i+1번째 도시를 잇는 도로)

    // 입력
    cin >> n;
    price.assign(n, 0);
    road_length.assign(n - 1, 0);
    for (int i = 0; i < n - 1; i++)
        cin >> road_length[i];
    for (int i = 0; i < n; i++)
        cin >> price[i];

    // 연산 및 출력
    cout << calcMinCost(price, road_length);
    return 0;
}