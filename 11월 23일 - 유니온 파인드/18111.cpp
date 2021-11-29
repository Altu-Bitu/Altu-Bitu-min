// 마인크래프트 https://www.acmicpc.net/problem/18111

#include <iostream>
#include <vector>

using namespace std;

const int MAX_HEIGHT = 256, MAX_TIME = INT32_MAX;

// h 높이로 땅을 고를 때 걸리는 시간을 계산하는 함수
int calcTime(int h, vector<vector<int>> &ground, int b)
{
    int time = 0;
    int n = ground.size(), m = ground[0].size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int gap = ground[i][j] - h;
            // 해당 칸의 높이가 h보다 높은 경우
            if (gap > 0)
            {
                // 블록 제거 (2초씩 증가)
                time += gap * 2;
                b += gap;
            }
            // 해당 칸의 높이가 h보다 낮은 경우
            if (gap < 0)
            {
                // 블록 쌓기 (1초씩 증가)
                time -= gap;
                b += gap;
            }
        }

    // 가지고 있는 블록 개수로는 땅을 고르지 못하면 최댓값 리턴
    if (b < 0)
        return MAX_TIME;
    return time;
}

int main()
{
    int n, m, b;

    // 입력
    cin >> n >> m >> b;
    vector<vector<int>> ground(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> ground[i][j];

    // 연산
    int ans_height, ans_time = MAX_TIME;
    // 가능한 모든 높이에 대해 땅고르기가 가능한지 검사
    for (int h = MAX_HEIGHT; h >= 0; h--)
    {
        int time = calcTime(h, ground, b);
        if (ans_time > time)
        {
            ans_time = time;
            ans_height = h;
        }
    }

    // 출력
    cout << ans_time << ' ' << ans_height;
    return 0;
}