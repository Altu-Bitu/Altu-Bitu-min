// 별 찍기 - 10 https://www.acmicpc.net/problem/2447

#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> board;

// 재귀적인 패턴으로 board에 별을 찍는 함수
// (row, col): 시작 좌표(왼쪽 맨위 좌표), size: 출력할 별의 크기
void star(int row, int col, int size)
{
    //Conquer : size의 크기가 1
    if (size == 1)
    {                          // 별의 크기가 1이면
        board[row][col] = '*'; // (row, col)에 별을 찍고 그대로 리턴
        return;
    }

    //Divide : 9등분 하는데, 가운데 부분에 대해선 함수 호출하지 않음
    int next_size = size / 3;                           // 한 변의 크기를 1/3로 나눔
    for (int i = 0; i <= next_size * 2; i += next_size) // i만큼 다음 시작 좌표 행(row) 증가
    {
        for (int j = 0; j <= next_size * 2; j += next_size) // j만큼 다음 시작 좌표 열(col) 증가
        {
            if (i == next_size && j == next_size) // 가운데 부분(공백 부분)이면
                continue;                         // 별 찍는 함수를 호출하지 않고 비워둠
            star(row + i, col + j, next_size);    // 나머지 부분은 별 찍는 함수 호출
        }
    }
}

/**
 * ***   (0, 0) (0, 1) (0, 2)
 * * *   (1, 0) (1, 1) (1, 2)
 * ***   (2, 0) (2, 1) (2, 2)
 *
 * 1. 가운데 부분에 대해서만 함수를 호출하지 않으면 됨
 * 2. 왼쪽 맨위 좌표를 (r, c)라 하고, 배열의 크기를 size라고 할 때, 
 *    가운데 부분은 (r+(size/3), c+(size/3))
 * 3. size가 1이될 때까지 나누기
 */
int main()
{
    int n; // 출력할 별의 크기 (n*n)

    cin >> n;                              // 별 크기 입력
    board.assign(n, vector<char>(n, ' ')); // 벡터에 n*n크기를 할당

    // 연산(별 찍기)
    star(0, 0, n);

    // 출력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << board[i][j]; // board에 찍힌 별을 순서대로 출력
        cout << '\n';
    }
}