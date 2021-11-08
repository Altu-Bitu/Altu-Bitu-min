// 드래곤 커브 https://www.acmicpc.net/problem/15685

#include <iostream>
#include <vector>

using namespace std;

// 격자 보드의 크기
const int SIZE = 101;

// 드래곤 커브가 그려질 격자 보드
// 좌표가 드래곤 커브의 일부인지 체크
vector<vector<bool>> board(SIZE, vector<bool>(SIZE, false));

// 방향에 따른 x, y 증가량 (인덱스가 방향 번호와 같음)
vector<int> dx = {1, 0, -1, 0};
vector<int> dy = {0, -1, 0, 1};

// 드래곤 커브를 그리는 함수
void drawDragonCurve(int x, int y, int d, int g)
{
    // 0세대 그리기
    int cur_x = x + dx[d], cur_y = y + dy[d];
    board[y][x] = true;
    board[cur_y][cur_x] = true;

    // 0세대까지만 드래곤 커브를 그리면 될 경우 바로 리턴
    if (g < 1)
        return;

    vector<int> prev_directions; // 이전 세대에서의 선분 방향

    // 1세대 그리기
    // 현재 방향은 이전 방향에서 시계 반대 방향으로 90도 회전한 것과 같음
    int cur_d = (d + 1) % 4;
    prev_directions.push_back(cur_d);
    cur_x += dx[cur_d];
    cur_y += dy[cur_d];
    board[cur_y][cur_x] = true;

    // 2세대 이후 그리기
    for (int i = 2; i <= g; i++)
    {
        vector<int> cur_directions; // 현재 세대에서의 선분 방향

        // 현재 세대의 드래곤 커브를 그리기 위한 선분 방향 구하기
        // 1. 이전 세대에서의 방향들을 뒤에서부터 순서대로 시계 반대 방향으로 90도 회전함
        for (int i = prev_directions.size() - 1; i >= 0; i--)
        {
            cur_d = (prev_directions[i] + 1) % 4;
            cur_directions.push_back(cur_d);
        }
        // 2. 이전 세대에서의 방향들을 그대로 이어붙임
        cur_directions.insert(cur_directions.end(), prev_directions.begin(), prev_directions.end());

        // 방향에 따라 선분 그리기 (선분에 포함된 좌표를 true 체크)
        for (int i : cur_directions)
        {
            cur_x += dx[i];
            cur_y += dy[i];
            board[cur_y][cur_x] = true;
        }

        // 세대 교체
        prev_directions = cur_directions;
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    int answer = 0;

    // 입력
    cin >> n;
    while (n--)
    {
        int x, y, d, g;
        cin >> x >> y >> d >> g;

        // 드래곤 커브를 격자 위에 그림
        drawDragonCurve(x, y, d, g);
    }

    // 네 꼭짓점이 모두 드래곤 커브의 일부인 정사각형의 개수를 찾음
    for (int i = 0; i < SIZE - 1; i++)
        for (int j = 0; j < SIZE - 1; j++)
            if (board[i][j] && board[i + 1][j] && board[i][j + 1] && board[i + 1][j + 1])
                answer++;

    // 출력
    cout << answer;
    return 0;
}