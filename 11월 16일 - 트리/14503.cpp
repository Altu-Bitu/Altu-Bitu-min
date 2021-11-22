// 로봇 청소기 https://www.acmicpc.net/problem/14503

#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<int>> matrix;

const int EMPTY = 0, WALL = 1, CLEAN = 2;

// 북, 동, 남, 서 방향에 따른 좌표 증가량
const vector<int> dr = {-1, 0, 1, 0};
const vector<int> dc = {0, 1, 0, -1};

matrix room;
int n, m, answer = 0;

void cleanRoom(int r, int c, int d)
{
    // 현재 방을 처음 방문하는 경우에만 청소
    if (room[r][c] == EMPTY)
    {
        room[r][c] = CLEAN;
        answer++;
    }

    // 왼쪽 방향에 청소하지 않은 공간이 존재하는지 확인
    int left_d = (d + 3) % 4;
    int next_r = r + dr[left_d], next_c = c + dc[left_d];
    int cnt = 0;
    for (; cnt < 4; cnt++)
    {
        if (room[next_r][next_c] == EMPTY)
            break;

        left_d = (left_d + 3) % 4;
        next_r = r + dr[left_d];
        next_c = c + dc[left_d];
    }

    // 네 방향 모두 청소할 공간이 없다면
    if (cnt == 4)
    {
        next_r = r - dr[d];
        next_c = c - dc[d];
        // 후진할 곳이 벽이라면 작동 중지
        if (room[next_r][next_c] == WALL)
            return;
        // 방향을 유지한 채 후진으로 이동
        cleanRoom(next_r, next_c, d);
    }
    // 왼쪽 방향에 청소할 공간이 있다면
    else
        // 왼쪽 방향으로 회전한 후 해당 방향으로 이동
        cleanRoom(next_r, next_c, left_d);
}

int main()
{
    // 입력
    int r, c, d;
    cin >> n >> m >> r >> c >> d;
    room.assign(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> room[i][j];

    // 연산 및 출력
    cleanRoom(r, c, d);
    cout << answer;
    return 0;
}