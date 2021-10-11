// 삼각형 만들기 https://www.acmicpc.net/problem/1448

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1. 가장 큰 빨대부터 3개 선택
    2. 선택된 빨대 중, 2번째 큰 빨대 길이 + 3번째 큰 빨대 길이 <= 1번째 큰 빨대 길이
        => 1번째 큰 빨대를 제외하고 다시 선택(1번으로)
    3. 끝까지 삼각형을 만들 수 없다면
        => -1 출력
*/

// 삼각형의 세 변의 길이의 최대 합을 구하는 함수
int calcMaxTriangle(vector<int> length)
{
    for (int i = 0; i < length.size() - 2; i++)
    {
        // 삼각형이 된다면 세 변의 합 리턴
        if (length[i] < length[i + 1] + length[i + 2])
            return length[i] + length[i + 1] + length[i + 2];
    }
    return -1;
}

int main()
{
    int n;              // 빨대 개수
    vector<int> length; // 빨대 길이

    // 입력
    cin >> n;
    length.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> length[i];

    // 연산 및 출력
    sort(length.begin(), length.end(), greater<int>());
    cout << calcMaxTriangle(length);
    return 0;
}