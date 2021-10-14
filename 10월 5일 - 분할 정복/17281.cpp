// ⚾ https://www.acmicpc.net/problem/17281

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> innings;   // innings[i][j] : i번째 이닝에서 j번 선수의 결과
vector<int> order(10, 0);      // 타순
vector<bool> check(10, false); // i번 선수의 타순이 정해졌는지 여부
int n;                         // 이닝 수
int ans;                       // 최대 득점

// 현재 타순에 따라 점수를 계산하는 함수
int calcScore()
{
    int score = 0; // 총 점수
    int idx = 1;   // 타자 순서

    // 모든 이닝의 점수를 계산함 (i: 이닝)
    for (int i = 0; i < n; i++)
    {
        vector<bool> baseman(4, 0); // 각 루수마다 선수가 있는지 여부
        int out = 0;                // 아웃 선수 카운트

        // 3번 아웃되기 전까지 이닝이 계속됨
        while (out < 3)
        {
            int state = innings[i][order[idx++]]; // i 이닝에서 idx번 타자의 공격 결과

            // 9번 타자까지 순서가 끝났다면
            if (idx == 10)
                idx = 1; // 다시 1번 타자로 순서가 돌아감

            // 현재 타자의 공격 결과에 따라 점수 계산
            switch (state)
            {
            case 0:    // 아웃인 경우
                out++; // 아웃 카운트 증가
                break;
            case 1:                  // 안타인 경우
                score += baseman[3]; // 3루에 선수가 있다면 홈 도착, 점수 증가
                for (int i = 3; i > 0; i--)
                    baseman[i] = baseman[i - 1]; // 1, 2루에 있는 선수 한 루씩 진루
                baseman[1] = 1;                  // 새로운 선수 1루에 도착
                break;
            case 2:                               // 2루타인 경우
                score += baseman[3] + baseman[2]; // 3루, 2루에 선수가 있다면 홈 도착, 점수 증가
                baseman[3] = baseman[1];          // 1루 -> 3루 이동
                baseman[2] = 1;                   // 새로운 선수 2루에 도착
                baseman[1] = 0;                   // 1루 초기화
                break;
            case 3: // 3루타인 경우
                for (int i = 3; i > 0; i--)
                {
                    score += baseman[i]; // 3루, 2루, 1루에 선수가 있다면 홈 도착, 점수 증가
                    baseman[i] = 0;      // 3,2,1루 초기화
                }
                baseman[3] = 1; // 새로운 선수 3루에 도착
                break;
            case 4: // 홈런인 경우
                for (int i = 3; i > 0; i--)
                {
                    score += baseman[i]; // 3루, 2루, 1루에 선수가 있다면 홈 도착, 점수 증가
                    baseman[i] = 0;      // 3,2,1루 초기화
                }
                score++; // 새로운 선수도 홈 바로 도착, 점수 증가
                break;
            }
        }
    }

    return score; // 계산한 점수를 리턴
}

// 가능한 타순을 모두 구하는 함수
// cnt: 타자 순서
void array(int cnt)
{
    // 4번 타자는 이미 정해져 있으므로
    if (cnt == 4)
    {
        array(cnt + 1); // 다음 순서로 넘어감
        return;
    }
    // 1~9 타순이 모두 정해졌다면 (기저 조건)
    if (cnt == 10)
    {
        int score = calcScore(); // 정해진 타순에 따라 점수를 계산함
        ans = max(ans, score);   // 최대 점수를 갱신함
        return;
    }
    // cnt번 타자가 될 선수를 결정함
    // i: 선수 번호
    for (int i = 2; i <= 9; i++)
    {
        // i번 선수의 타순이 아직 정해지지 않았다면
        if (!check[i])
        {
            order[cnt] = i;   // cnt번 타자를 i번 선수로 설정함
            check[i] = true;  // i번 선수 순서 정해짐
            array(cnt + 1);   // 다음 순서로 넘어감
            check[i] = false; // i번 선수의 순서를 다시 정하기 위해 false로 바꿈
        }
    }
}

/**
 * 구현 + 브루트 포스, 백트래킹
 * 1. 우선 가능한 타순을 모두 구한다. (이때, 4번 타자는 항상 1번 선수여야 함) (브루트 포스, 백트래킹)
 * 2. 구한 타순에 대한 각각의 점수를 구하며 최대 점수를 갱신한다. (구현)
 */

int main()
{
    //입력
    cin >> n;                              // 이닝 수를 입력 받음
    innings.assign(n, vector<int>(10, 0)); // 각 이닝의 결과를 저장할 이차원 벡터를 초기화함
    for (int i = 0; i < n; i++)            // i: i번째 이닝
    {
        for (int j = 1; j < 10; j++) // j: j번 선수
        {
            cin >> innings[i][j]; // i번째 이닝에서 j번 선수의 결과를 입력 받음
        }
    }

    //연산
    order[4] = 1;    // 4번 타자는 1번 선수
    check[1] = true; // 1번 선수는 타순이 확정됨
    array(1);        // 가장 많은 득점을 하는 타순을 찾고 그 때의 득점을 계산함

    //출력
    cout << ans << '\n';

    return 0;
}