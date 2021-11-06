// 회전 초밥 https://www.acmicpc.net/problem/2531

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 먹을 수 있는 초밥 가짓수의 최댓값을 구하는 함수
int calcMaxSushi(vector<int> &belt, int n, int k, int c)
{
    int ans = 0;           // 먹을 수 있는 초밥 가짓수의 최댓값
    map<int, int> can_eat; // 먹을 수 있는 초밥의 종류, 개수
    int off_idx = 0;       // 빼야하는 초밥의 인덱스 (먹을 수 있는 초밥 리스트에서)
    int on_idx = k - 1;    // 추가해야하는 초밥의 인덱스

    // 첫 구간에 있는 초밥의 가짓수 계산
    for (int i = off_idx; i <= on_idx; i++)
        can_eat[belt[i]]++;

    // 구간에 무료 쿠폰 초밥이 없다면 가짓수 + 1
    ans = (can_eat.count(c)) ? can_eat.size() : can_eat.size() + 1;

    while (off_idx < n - 1)
    {
        // 초밥 추가하기
        // 초밥이 컨테이너 벨트 위에 있기 때문에 모듈러 연산으로 인덱스 증가
        on_idx = (on_idx + 1) % n;
        can_eat[belt[on_idx]]++;

        // 초밥 빼기
        int off_sushi = belt[off_idx++];
        can_eat[off_sushi]--;
        // 구간 내에 해당 초밥이 더이상 없다면, 가짓수에서 제거
        if (can_eat[off_sushi] == 0)
            can_eat.erase(off_sushi);

        // 최댓값 갱신
        int size = (can_eat.count(c)) ? can_eat.size() : can_eat.size() + 1;
        ans = (ans >= size) ? ans : size;
    }
    return ans;
}

int main()
{
    int n, d, k, c;

    // 입력
    cin >> n >> d >> k >> c;
    vector<int> belt(n, 0);
    for (int i = 0; i < n; i++)
        cin >> belt[i];

    // 연산 및 출력
    cout << calcMaxSushi(belt, n, k, c);
    return 0;
}