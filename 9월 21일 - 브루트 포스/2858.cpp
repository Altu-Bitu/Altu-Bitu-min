// 기숙사 바닥 https://www.acmicpc.net/problem/2858

#include <iostream>
#include <utility>

using namespace std;

// 총 타일 수와 둘레 길이를 입력 받고 가로, 세로 길이를 계산 함수
pair<int, int> calcWidthHeight(const int total_tile, int round)
{
    round = round / 2 + 2;
    pair<int, int> len(round - 1, 1);  // <가로 길이, 세로 길이>
    int area = len.first * len.second; // 방 넓이

    // 가로 * 세로가 총 타일 수와 같다면 리턴
    while (area != total_tile)
    {
        len.first--;
        len.second++;
        area = len.first * len.second;
    }
    return len;
}

int main()
{
    int r, b;

    // 입력
    cin >> r >> b;

    // 계산 및 출력
    pair<int, int> result = calcWidthHeight(r + b, r);
    cout << result.first << ' ' << result.second;
    return 0;
}