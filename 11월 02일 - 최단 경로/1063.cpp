// 킹 https://www.acmicpc.net/problem/1063

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const int BOARD_SIZE = 8;
typedef pair<int, int> ci;

// 체스판 좌표를 숫자 좌표로 변환하는 함수
ci toCoord(string chess)
{
    return make_pair((chess[1] - '0') - 1, chess[0] - 'A');
}

// 숫자 좌표를 체스판 좌표로 변환하는 함수
string toChessCoord(ci coord)
{
    string ans;
    ans += coord.second + 'A';
    ans += ++coord.first + '0';
    return ans;
}

// 좌표가 체스판의 범위를 벗어나는지 판별하는 함수
bool isOnBoard(ci coord)
{
    if (coord.first < 0 || coord.first >= BOARD_SIZE || coord.second < 0 || coord.second >= BOARD_SIZE)
        return false;
    return true;
}

// 킹을 움직이는 함수
void moveKing(string move, ci &king, ci &stone)
{
    // 명령어에 따라 움직일 칸 수
    int dr = 0, dc = 0;

    if (move == "R")
        dc++;
    else if (move == "L")
        dc--;
    else if (move == "B")
        dr--;
    else if (move == "T")
        dr++;
    else if (move == "RT")
    {
        dc++;
        dr++;
    }
    else if (move == "LT")
    {
        dc--;
        dr++;
    }
    else if (move == "RB")
    {
        dc++;
        dr--;
    }
    else
    {
        dc--;
        dr--;
    }

    // 킹을 명령어를 따라 움직임
    king.first += dr;
    king.second += dc;

    // 킹 위치가 돌의 위치와 같아진다면
    if (king.first == stone.first && king.second == stone.second)
    {
        // 돌을 같은 방향으로 움직임
        stone.first += dr;
        stone.second += dc;

        // 돌이 체스판을 벗어난다면
        if (!isOnBoard(stone))
        {
            // 킹과 돌을 이전 위치로 되돌림
            king.first -= dr;
            king.second -= dc;
            stone.first -= dr;
            stone.second -= dc;
        }
    }

    // 킹이 체스판을 벗어난다면
    if (!isOnBoard(king))
    {
        // 킹을 이전 위치로 되돌림
        king.first -= dr;
        king.second -= dc;
    }
}

int main()
{
    string king_chess, stone_chess; // 킹과 돌의 체스판 좌표
    ci king, stone; // 킹과 돌의 숫자 좌표
    int n;  // 명령어 개수

    // 입력
    cin >> king_chess >> stone_chess >> n;

    // 체스판 좌표를 계산하기 쉽게 숫자 좌표로 변환
    king = toCoord(king_chess);
    stone = toCoord(stone_chess);

    // 연산 (명령어에 따라 킹을 움직임)
    while (n--)
    {
        string move;
        cin >> move;
        moveKing(move, king, stone);
    }

    // 연산 결과를 출력 형태에 맞게 변환 (숫자 좌표 -> 체스판 좌표)
    king_chess = toChessCoord(king);
    stone_chess = toChessCoord(stone);

    // 출력
    cout << king_chess << '\n'
         << stone_chess;
    return 0;
}