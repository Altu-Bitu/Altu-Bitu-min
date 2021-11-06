// 섬의 개수 https://www.acmicpc.net/problem/4963

#include <iostream>
#include <vector>

using namespace std;

const int ISLAND = 1, VISITED = 2;

// 하나의 섬으로 연결된 사각형들을 모두 방문 처리하는 함수
void checkVisited(vector<vector<int>> &map, int x, int y)
{
    // 주변 가로, 세로, 대각선 위치의 모든 사각형을 검사
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int cur_x = x + i, cur_y = y + j;

            // 인덱스가 범위를 초과하면 검사하지 않음
            if (cur_x < 0 || cur_x >= map.size() || cur_y < 0 || cur_y >= map[0].size())
                continue;

            // 연결된 사각형이 섬(1)이면
            if (map[cur_x][cur_y] == ISLAND)
            {
                // 해당 사각형 방문(2) 체크
                map[cur_x][cur_y] = VISITED;
                // 해당 사각형을 기준으로 인근 사각형들을 다시 검사
                checkVisited(map, cur_x, cur_y);
            }
        }
    }
}

// 지도 위 섬의 개수를 계산하는 함수
int calcNumOfIsland(vector<vector<int>> &map, int w, int h)
{
    int island = 0; // 섬의 개수

    // 지도의 모든 사각형을 검사
    for (int x = 0; x < h; x++)
    {
        for (int y = 0; y < w; y++)
        {
            // 해당 사각형이 섬(1)이면
            if (map[x][y] == ISLAND)
            {
                // 연결된 사각형들을 하나의 섬으로 처리
                checkVisited(map, x, y);
                island++;
            }
        }
    }
    return island;
}

int main()
{
    int w, h;
    while (true)
    {
        // 입력
        cin >> w >> h;

        // 입력값이 0 0 이면 프로그램 종료
        if (w == 0 && h == 0)
            return 0;

        vector<vector<int>> map(h, vector<int>(w, 0));
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> map[i][j];

        // 연산 및 출력
        cout << calcNumOfIsland(map, w, h) << '\n';
    }
}