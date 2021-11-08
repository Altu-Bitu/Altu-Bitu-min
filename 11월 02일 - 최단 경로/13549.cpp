// 숨바꼭질 3 https://www.acmicpc.net/problem/13549

// 0-1 BFS 알고리즘 참고 https://justicehui.github.io/medium-algorithm/2018/08/30/01BFS/

#include <iostream>
#include <vector>
#include <deque>
#include <utility>

using namespace std;

const int INF = 100001;

// 다음 정점을 덱에 삽입하고, 해당 정점까지의 소요 시간을 갱신하는 함수
void movePoint(deque<int> &d, vector<int> &time, int p, int next_p)
{
    // 다음 정점이 범위를 벗어나면 리턴
    if (next_p >= INF || next_p < 0)
        return;

    // 다음 정점 == (현재 정점 * 2) 이면, 순간이동한 것이므로 가중치(이동 소요 시간)를 0으로 설정
    int next_t = (p * 2 == next_p) ? 0 : 1;

    // 첫 방문이라면, 가중치 갱신 
    if (time[next_p] == INF)
    {
        time[next_p] = time[p] + next_t;

        // 가중치가 0인 정점은 우선하기 위해 front에 삽입
        if (next_t == 0)
            d.push_front(next_p);
        // 가중치가 0이 아니라면, back에 삽입
        else
            d.push_back(next_p);
    }
}

// 동생을 찾는 최소 시간을 계산하는 함수
int hideAndSeek(int n, int k)
{
    vector<int> time(INF, INF); // 각 정점까지의 소요 시간
    deque<int> d; 

    // 시작 정점 초기화
    time[n] = 0;
    d.push_back(n);

    while (!d.empty())
    {
        // 현재 정점
        int p = d.front();
        d.pop_front();

        // 목표 정점(k)에 도착하면 종료
        if (p == k)
            break;

        // 이동이 가능한 정점들로 이동
        movePoint(d, time, p, 2 * p);
        movePoint(d, time, p, p + 1);
        movePoint(d, time, p, p - 1);
    }
    // 목표 정점까지의 소요 시간 리턴
    return time[k];
}

int main()
{
    int n, k;

    // 입력
    cin >> n >> k;

    // 연산 및 출력
    cout << hideAndSeek(n, k);
    return 0;
}