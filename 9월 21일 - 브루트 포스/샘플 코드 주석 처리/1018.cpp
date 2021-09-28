// 체스판 다시 칠하기 https://www.acmicpc.net/problem/1018

#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 64; //체스판 칸 개수

// 리턴: 첫번째 칸의 인덱스가 (row, col)인 8*8 체스판을 만드는 데 드는 최소 카운트
// B로 시작하는 체스판을 기준으로 계산, W로 시작하는 체스판의 경우 8*8에서 앞의 카운트를 빼서 계산
int chessChange(int row, int col, vector<vector<char>> &board)
{
    int b_cnt = 0; // B로 시작하는 체스판 만들기 위한 카운트

    // i: 체스판의 행 인덱스 (행 변화값)
    for (int i = 0; i < 8; i++)
    {
        // j: 체스판의 열 인덱스 (열 변화값)
        for (int j = 0; j < 8; j++)
        {
            // i + j가 짝수면 시작색(B)과 동일해야 함
            if ((i + j) % 2 == 0 && board[row + i][col + j] != 'B')
                b_cnt++; // 시작색과 동일하지 않다면 카운트 증가
            // i + j가 홀수라면 시작색과 반대색(W) 이어야 함
            else if ((i + j) % 2 && board[row + i][col + j] != 'W')
                b_cnt++; // 반대색이 아니라면 카운트 증가
        }
    }

    //최솟값 리턴
    if (b_cnt > SIZE / 2)    // B로 시작하는 체스판을 기준으로 계산한 값이 32가 넘는다면
        return SIZE - b_cnt; // 자동으로 W로 시작하는 체스판을 기준으로 계산한 값이 최솟값
    return b_cnt;            // 넘지 않는다면 계산한 값이 그대로 최솟값
}

int main()
{
    int n;              // 보드의 행 개수
    int m;              // 보드의 열 개수
    int ans = SIZE + 1; // 정답은 체스판 칸 개수 + 1 로 초기화

    // 입력
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m)); // 행: n, 열: m
    for (int i = 0; i < n; i++)                     // i: 보드의 행 인덱스
        for (int j = 0; j < m; j++)                 // j: 보드의 열 인덱스
            cin >> board[i][j];                     // 각 보드 칸의 색 입력

    // 연산
    // 체스판의 크기가 8*8이므로 행 인덱스 i는 n - 8까지만 반복함
    for (int i = 0; i <= n - 8; i++)
    {
        // 행과 마찬가지로 열 인덱스 j도 m - 8까지만 반복함
        for (int j = 0; j <= m - 8; j++)
        {
            int cnt = chessChange(i, j, board); // 첫 번째 칸의 (i,j)인 체스판 만드는 최솟값
            ans = min(ans, cnt);                // 최솟값 갱신
        }
    }

    // 출력
    cout << ans << '\n';

    return 0;
}