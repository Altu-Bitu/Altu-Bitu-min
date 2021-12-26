// 사탕 게임 https://www.acmicpc.net/problem/3085

#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<char>> matrix;

// 우 하 좌 상
vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

// (x, y) 좌표가 범위 내의 좌표인지 검사하는 함수
bool isValid(int n, int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

// 시작점(x, y)을 포함한 가장 긴 연속 부분의 길이를 구하는 함수
int findLongestLen(int n, matrix &candy, int x, int y)
{
    int len_v = 1; // 세로 방향 최장 길이
    int len_h = 1; // 가로 방향 최장 길이

    for (int i = 0; i < 4; i++)
    {
        // 현재 검사하는 방향에 따른 최장 길이 변수 종류
        int *len = (i % 2 == 0) ? &len_v : &len_h;

        int next_x = x + dx[i];
        int next_y = y + dy[i];

        // 다음 칸의 사탕이 같은 색이라면
        while (isValid(n, next_x, next_y) && candy[x][y] == candy[next_x][next_y])
        {
            // 최장 길이 증가
            (*len)++;
            next_x += dx[i];
            next_y += dy[i];
        }
    }
    // 세로, 가로 방향 중 더 큰 길이 리턴
    return max(len_v, len_h);
}

// 먹을 수 있는 사탕의 개수를 구하는 함수
int findEatableCandy(int n, matrix &candy)
{
    int eatable_num = 0; // 먹을 수 있는 최대 사탕의 개수
    for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
        {
            // 현재 칸에서, 사탕의 위치를 바꾸지 않고 먹을 수 있는 최대 사탕 개수를 구함
            eatable_num = max(eatable_num, findLongestLen(n, candy, x, y));

            // 우, 하 방향만 검사
            for (int i = 0; i < 2; i++)
            {
                int next_x = x + dx[i];
                int next_y = y + dy[i];

                // 다음 칸의 사탕이 다른 색이라면
                if (isValid(n, next_x, next_y) && candy[x][y] != candy[next_x][next_y])
                {
                    // 현재 칸과 다음 칸 사탕 교환
                    swap(candy[x][y], candy[next_x][next_y]);
                    // 사탕이 교환된 현재 칸에서, 최대 사탕 개수를 구함
                    eatable_num = max(eatable_num, findLongestLen(n, candy, x, y));
                    // 사탕이 교환된 다음 칸에서, 최대 사탕 개수를 구함
                    eatable_num = max(eatable_num, findLongestLen(n, candy, next_x, next_y));
                    // 위치 교환 원상 복구
                    swap(candy[x][y], candy[next_x][next_y]);
                }
            }
        }
    return eatable_num;
}

int main()
{
    int n;

    // 입력
    cin >> n;
    matrix candy(n, vector<char>(n, ' '));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> candy[i][j];

    // 연산 및 출력
    cout << findEatableCandy(n, candy);
    return 0;
}