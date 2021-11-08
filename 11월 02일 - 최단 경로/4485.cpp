// 녹색 옷 입은 애가 젤다지? https://www.acmicpc.net/problem/4485

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

typedef vector<vector<int>> matrix;
typedef tuple<int, int, int> ti;

const int MAX_LOST = 250 * 10;

// 동굴 출구에 도착할 때까지 링크가 잃을 수밖에 없는 최소 금액을 구하는 함수
int calcLostRupee(matrix &cave, int n)
{
    // 하, 상, 좌, 우 이동을 위한 벡터
    vector<int> dx = {0, 0, -1, 1};
    vector<int> dy = {-1, 1, 0, 0};

    matrix lost_rupees(n, vector<int>(n, MAX_LOST)); // 해당 정점에 도착할 때까지 총 잃은 루피 수
    priority_queue<ti, vector<ti>, greater<ti>> pq;  // <해당 정점까지 잃은 루피 수, x좌표, y좌표>

    // 시작점(0, 0) 초기화
    lost_rupees[0][0] = cave[0][0];
    pq.push(make_tuple(cave[0][0], 0, 0));

    while (!pq.empty())
    {
        ti v = pq.top(); // 현재 정점
        int weight = get<0>(v);
        int x = get<1>(v);
        int y = get<2>(v);
        pq.pop();

        // 이미 확인한 정점이라면 생략
        if (weight > lost_rupees[x][y])
            continue;

        // 현재 정점에서 상하좌우로 한 칸씩 이동
        for (int i = 0; i < 4; i++)
        {
            // 다음으로 이동할 정점의 좌표
            int next_x = x + dx[i];
            int next_y = y + dy[i];

            // 좌표가 범위를 초과한다면 넘김
            if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= n)
                continue;

            // 기존 정점까지의 가중치보다 새로 계산된 가중치의 값이 적다면
            int new_losts = lost_rupees[x][y] + cave[next_x][next_y];
            if (lost_rupees[next_x][next_y] > new_losts)
            {
                // 가중치 값 갱신 및 큐에 정점 삽입
                lost_rupees[next_x][next_y] = new_losts;
                pq.push(make_tuple(new_losts, next_x, next_y));
            }
        }
    }
    return lost_rupees[n - 1][n - 1];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t = 1; // 테스트 케이스 번호
    while (true)
    {
        int n; // 동굴의 크기
        cin >> n;

        // 0이 입력되면 종료
        if (n == 0)
            return 0;

        // 입력
        matrix cave(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> cave[i][j];

        // 연산 및 출력
        int lost_rupee = calcLostRupee(cave, n);
        cout << "Problem " << t++ << ": " << lost_rupee << '\n';
    }
}