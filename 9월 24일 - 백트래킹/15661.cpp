// 링크와 스타트 https://www.acmicpc.net/problem/15661

#include <iostream>
#include <vector>

using namespace std;

const int MAX_GAP = 2000; // 최대 능력치 합 차이

int n;                 // 총 사람 수
vector<vector<int>> s; // s[i][j]: i와 j가 같은 팀일 때 능력치
vector<bool> team;     // team[i]: i번째 사람이 속한 팀 (true: 스타트 팀, false: 링크 팀)
int result = MAX_GAP;  // 답: 팀 간의 능력치 합 차이의 최솟값

// 팀 간의 능력치 합 차이의 최솟값을 구하는 함수
// cnt: 현재까지 cnt명 뽑음 (스타트 팀으로 선택함)
// idx: idx번 이후의 사람들만 고려하여 조합을 뽑음 (중복이 없어야 하므로)
void calcMinTeamGap(int cnt, int idx)
{
    if (cnt == n / 2)
    {
        int start_sum = 0, link_sum = 0;

        // 각 팀의 능력치 합 구하기
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && team[i] && team[j])
                    start_sum += s[i][j];
                else if (i != j && !team[i] && !team[j])
                    link_sum += s[i][j];
            }
        }

        // 최솟값 갱신
        result = min(result, abs(start_sum - link_sum));
        return;
    }

    // 팀원 선택
    for (int i = idx; i < n; i++)
    {
        if (!team[i])
        {
            team[i] = true;
            calcMinTeamGap(cnt + 1, i + 1);
            team[i] = false;
        }
    }
}

int main()
{
    // 입력
    cin >> n;
    s.assign(n, vector<int>(n, 0));
    team.assign(n, false);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> s[i][j];

    // 연산 및 출력
    calcMinTeamGap(0, 0);
    cout << result;

    return 0;
}