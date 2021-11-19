// 감시 https://www.acmicpc.net/problem/15683
// 샘플 코드 출처: https://github.com/Altu-Bitu/Notice/blob/main/11%EC%9B%94%2009%EC%9D%BC%20-%20%EB%8F%99%EC%A0%81%20%EA%B3%84%ED%9A%8D%EB%B2%95%EA%B3%BC%20%EC%B5%9C%EB%8B%A8%20%EA%B1%B0%EB%A6%AC%20%EC%97%AD%EC%B6%94%EC%A0%81/%EA%B3%BC%EC%A0%9C/15683.cpp

#include <iostream>
#include <vector>

using namespace std;

int n, m, ans = 65;        // 사무실의 크기 (n * m), 사각지대의 최솟값
vector<vector<int>> board; // 사무실의 정보

// cctv 범위 표시
void ray(int row, int col, int dir)
{
    // 상 우 하 좌
    int dr[4] = {-1, 0, 1, 0}; // 방향에 따른 row 증가량
    int dc[4] = {0, 1, 0, -1}; // 방향에 따른 col 증가량

    while (row >= 0 && row < n && col >= 0 && col < m && board[row][col] != 6)
    {                             // dir 방향으로 뻗어나가며 cctv 표시
        if (board[row][col] == 0) // 다른 cctv를 지우지 않기 위해 빈 공간일 때만 표시
            board[row][col] = 7;  // CCTV 범위 표시
        row += dr[dir];           // 다음 방향으로 이동
        col += dc[dir];           // 다음 방향으로 이동
    }
}

// cctv 방향 지정
void install(int cctv, int row, int col, int dir)
{
    if (cctv >= 1)                    // 1, 2, 3, 4, 5번 cctv
        ray(row, col, dir);           // cctv 범위 한 방향 표시
    if (cctv >= 2 && cctv != 3)       // 2, 4, 5번 cctv
        ray(row, col, (dir + 2) % 4); // 반대 방향 표시
    if (cctv >= 3)                    // 3, 4, 5번 cctv
        ray(row, col, (dir + 1) % 4); // 직각 방향 표시
    if (cctv == 5)                    // 5번 cctv
        ray(row, col, (dir + 3) % 4); // 나머지 방향 표시
}

// 사각지대 계산
int blindSpot()
{
    int cnt = 0; // 사각지대 칸 수
    for (int i = 0; i < n; i++)
    { // 사무실의 모든 칸을 돌며
        for (int j = 0; j < m; j++)
        {
            if (!board[i][j]) // CCTV 범위에 포함되지 않는 곳이 있다면
                cnt++;        // 사각지대 수 증가
        }
    }
    return cnt; // 계산한 값 리턴
}

// 사무실의 모든 칸에 CCTV를 설치해보며 사각지대의 최솟값을 갱신하는 함수
void backtracking(int idx)
{
    if (idx == n * m)
    {                                // 기저 조건 : 사무실의 모든 위치 확인
        ans = min(ans, blindSpot()); // 사각지대 계산 후 최솟값 갱신
        return;                      // 검사 종료
    }

    int row = idx / m;                    // 현재 사무실 칸의 행 인덱스
    int col = idx % m;                    // 현재 사무실 칸의 열 인덱스
    int cur = board[row][col];            // 현재 사무실 칸의 정보
    if (cur == 0 || cur == 6 || cur == 7) // cctv가 없는 곳이면
        return backtracking(idx + 1);     // 다음 칸 검사로 넘어감

    vector<vector<int>> save = board; // unvisited 처리용 board 상태 저장
    for (int i = 0; i < 4; i++)
    {                              // 4개의 방향에 대해 cctv 설치
        install(cur, row, col, i); // 현재 CCTV(cur)를 (row, col) 위치에 i번째 방향으로 설치
        backtracking(idx + 1);     // 현재 칸에 CCTV를 설치한 채 다음 칸 검사
        board = save;              // 다른 방향으로 CCTV를 설치하기 위해 다시 unvisited 처리

        // 2번 cctv의 방향 종류는 2개, 5번 cctv의 방향 종류는 1개
        if ((cur == 2 && i == 1) || (cur == 5 && i == 0))
            break; // 따라서 각각 2번, 1번씩 설치한 후에 더이상 설치하지 않음
    }
}

/**
 * cctv가 설치될 수 있는 모든 경우를 고려하는 완전탐색 문제
 *
 * 1. 각 cctv에 대해 가능한 모든 방향을 고려하여 설치
 *    1, 3, 4번 cctv : 4방향
 *    2번 cctv : 2방향
 *    5번 cctv : 1방향
 * 2. install 함수에서 각 cctv의 빛이 뻗어나갈 방향을 잡음
 * 3. ray 함수에서 cctv의 감시 가능 범위 표시
 * 4. 모든 위치를 확인했으면 blindSpot 함수를 통해 사각지대 계산
 *
 * 풀이 : https://myunji.tistory.com/411
 * 해당 코드는 위 링크의 코드를 리팩토링한 코드입니다.
 * 말로는 풀이를 설명하기 어려우니 링크를 꼭 확인해주세요!
 */
int main()
{
    // 입력
    cin >> n >> m;
    // 입력에 따라 사무실 크기 할당
    board.assign(n, vector<int>(m));
    // 사무실 정보 입력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> board[i][j]; // (i, j) 위치의 사무실 칸
    }

    // 연산
    backtracking(0);

    // 출력
    cout << ans;
}