// 오목 https://www.acmicpc.net/problem/2615

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
typedef tuple<int, int, int> ti;

const int SIZE = 20, EMPTY = 0;

// 방향에 따른 좌표 증가량
// 맨 왼쪽 위 돌을 기준으로 검사하기 때문에 오른쪽/아래쪽으로 향하는 방향만 정의
const vector<int> dx = {-1, 0, 1, 1};
const vector<int> dy = {1, 1, 1, 0};

// 좌표가 범위를 초과하는지 판별하는 함수
bool checkOutOfBounds(int x, int y)
{
    return (x > 0 && x < SIZE && y > 0 && y < SIZE);
}

// 해당 좌표(x, y)부터 연속적으로 5알이 놓이는지 확인하는 함수
bool checkWin(vector<vector<int>> &board, int x, int y)
{
    int color = board[x][y];    // 기준 색

    // 4 방향에 대해 검사
    for (int idx = 0; idx < 4; idx++)
    {
        int next_x = x + dx[idx], next_y = y + dy[idx];

        // 해당 방향에 같은 색 돌이 놓여있다면
        if (checkOutOfBounds(next_x, next_y) && board[next_x][next_y] == color)
        {
            // 같은 방향에서 그 이전에도 같은 색 돌이 있었다면 패스 (-> 여섯 알 이상 놓일 수 있음)
            int prev_x = x - dx[idx], prev_y = y - dy[idx];
            if (checkOutOfBounds(prev_x, prev_y) && board[prev_x][prev_y] == color)
                continue;

            int cnt = 0;    // 같은 방향에 놓인 같은 색 돌의 수
            while (cnt < 4)
            {
                next_x += dx[idx];
                next_y += dy[idx];

                // 범위를 초과하거나 같은 색 돌이 없으면 break
                if (!checkOutOfBounds(next_x, next_y) || board[next_x][next_y] != color)
                    break;
                cnt++;
            }
            // 3개의 같은 색 돌이 더 놓여야 오목이 완성됨
            if (cnt == 3)
                return true;
        }
    }
    // 완성된 오목이 없음
    return false;
}

// 승리한 색과 가장 왼쪽 위 돌의 좌표를 찾는 함수
// 리턴: (승리한 색, x 좌표, y 좌표)
ti findWinner(vector<vector<int>> &board)
{
    // 맨 왼쪽 위 돌을 기준으로 하기 위해 1열부터 행을 증가하며 검사
    for (int y = 1; y < SIZE; y++)
        for (int x = 1; x < SIZE; x++)
        {
            if (board[x][y] == EMPTY)
                continue;

            // 해당 좌표부터 연속적으로 5알이 놓인다면, 정답 리턴
            if (checkWin(board, x, y))
                return make_tuple(board[x][y], x, y);
        }
    // 아직 승부가 결정나지 않은 경우 0 리턴
    return make_tuple(0, 0, 0);
}

int main()
{
    // 입력
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));  // 바둑판
    for (int i = 1; i < SIZE; i++)
        for (int j = 1; j < SIZE; j++)
            cin >> board[i][j];

    // 연산 및 출력
    ti answer = findWinner(board);
    cout << get<0>(answer) << '\n';
    if (get<0>(answer) != 0)
    {
        cout << get<1>(answer) << ' ' << get<2>(answer);
    }
    return 0;
}