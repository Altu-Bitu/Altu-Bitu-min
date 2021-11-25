// 가장 큰 정사각형 찾기 https://programmers.co.kr/learn/courses/30/lessons/12905

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1로 이루어진 가장 큰 정사각형의 넓이를 찾는 함수
int solution(vector<vector<int>> board)
{
    int answer = 0;
    int n = board.size(), m = board[0].size();

    // 행 또는 열의 크기가 1인 경우
    if (n == 1 || m == 1)
        // 값이 1인 칸이 존재한다면, 최대 정사각형 넓이는 1
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (board[i][j])
                    return 1;

    // board를 dp 배열처럼 사용해 최댓값 갱신
    // board[i][j]: 현재 칸을 오른쪽 아래로 해서 만들 수 있는 정사각형의 최대 크기
    // board[i][j] = min(board[i-1][j-1], board[i][j-1], board[i-1][j]) + 1
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
        {
            if (board[i][j])
            {
                int area = min(board[i - 1][j - 1], board[i - 1][j]);
                area = min(area, board[i][j - 1]);
                board[i][j] = area + 1;
                answer = max(board[i][j], answer);
            }
        }
    return answer * answer;
}

int main()
{
    vector<vector<int>> board = {
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 0},
    };
    cout << solution(board);
    return 0;
}