// 킹 https://www.acmicpc.net/problem/1063

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

using namespace std;
typedef pair<int, int> point;

const int BOARD_SIZE = 8;
map<string, int> directions = {
    {"R", 0},
    {"L", 1},
    {"B", 2},
    {"T", 3},
    {"RT", 4},
    {"LT", 5},
    {"RB", 6},
    {"LB", 7}
};

// 체스판 좌표를 숫자 좌표로 변환하는 함수
point stringToPoint(string str)
{
    return make_pair(str[1] - '1', str[0] - 'A');
}

// 숫자 좌표를 체스판 좌표로 변환하는 함수
string pointToString(point p)
{
    string ans;
    ans += p.second + 'A';
    ans += p.first + '1';
    return ans;
}

// 좌표가 체스판의 범위를 벗어나는지 판별하는 함수
bool isOnBoard(point p)
{
    if (p.first < 0 || p.first >= BOARD_SIZE || p.second < 0 || p.second >= BOARD_SIZE)
        return false;
    return true;
}

// 킹을 움직이는 함수
void moveKing(string move, point &king, point &stone)
{
    // 방향에 따른 좌표 변화를 나타내는 배열
    // R, L, B, T, RT, LT, RB, LB
    vector<int> dr = {0, 0, -1, 1, 1, 1, -1, -1};
    vector<int> dc = {1, -1, 0, 0, 1, -1, 1, -1};
    int idx = directions[move];    // 방향을 가리키는 인덱스

    // 킹을 명령어를 따라 움직임
    king.first += dr[idx];
    king.second += dc[idx];

    // 킹 위치가 돌의 위치와 같아진다면
    if (king.first == stone.first && king.second == stone.second)
    {
        // 돌을 같은 방향으로 움직임
        stone.first += dr[idx];
        stone.second += dc[idx];

        // 돌이 체스판을 벗어난다면
        if (!isOnBoard(stone))
        {
            // 킹과 돌을 이전 위치로 되돌림
            king.first -= dr[idx];
            king.second -= dc[idx];
            stone.first -= dr[idx];
            stone.second -= dc[idx];
        }
    }

    // 킹이 체스판을 벗어난다면
    if (!isOnBoard(king))
    {
        // 킹을 이전 위치로 되돌림
        king.first -= dr[idx];
        king.second -= dc[idx];
    }
}

int main()
{
    string king_str, stone_str; // 킹과 돌의 체스판 좌표
    point king_p, stone_p;                 // 킹과 돌의 숫자 좌표
    int n;                          // 명령어 개수

    // 입력
    cin >> king_str >> stone_str >> n;

    // 체스판 좌표를 계산하기 쉽게 숫자 좌표로 변환
    king_p = stringToPoint(king_str);
    stone_p = stringToPoint(stone_str);

    // 연산 (명령어에 따라 킹을 움직임)
    while (n--)
    {
        string move;
        cin >> move;
        moveKing(move, king_p, stone_p);
    }

    // 연산 결과를 출력 형태에 맞게 변환 (숫자 좌표 -> 체스판 좌표)
    king_str = pointToString(king_p);
    stone_str = pointToString(stone_p);

    // 출력
    cout << king_str << '\n'
         << stone_str;
    return 0;
}