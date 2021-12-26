// 프로젝트 스케줄링 https://www.acmicpc.net/problem/14907

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int SIZE = 26; // 최대 작업 개수

// 모든 작업이 완료되는 데 걸리는 최종 시간을 계산하는 함수
int calcTotalTime(vector<vector<int>> &graph, vector<int> &indegree, vector<int> &required_time)
{
    int total_time = 0;      // 모든 작업이 완료되는 데 걸리는 최종 시간
    vector<int> dp(SIZE, 0); // dp[i]: 처음부터 작업 i까지 완료하는 데 걸린 시간
    queue<int> q;

    // 큐 및 소요 시간 초기화
    for (int i = 0; i < SIZE; i++)
    {
        if (!indegree[i]) // 진입 차수가 0인 작업만
        {
            q.push(i);
            dp[i] = required_time[i];
        }
    }

    while (!q.empty())
    {
        int work = q.front();
        q.pop();
        total_time = max(total_time, dp[work]); // 최종 시간 갱신

        vector<int> next_works = graph[work]; // 현재 작업과 이어지는 다음 작업들
        for (int next_work : next_works)
        {
            // 다음 작업까지 걸린 시간 갱신
            dp[next_work] = max(dp[next_work], dp[work] + required_time[next_work]);
            if (--indegree[next_work] == 0) // 다음 작업의 진입 차수 감소
                q.push(next_work);          // 진입 차수가 0이면 큐에 삽입
        }
    }
    return total_time;
}

int main()
{
    vector<vector<int>> graph(SIZE, vector<int>(0)); // 작업 순서에 따른 방향 그래프
    // 각 정점(작업)들의 진입 차수
    vector<int> indegree(SIZE, -1);     // 존재하지 않는 작업의 진입 차수를 -1로 표현
    vector<int> required_time(SIZE, 0); // 각 작업의 완료까지 필요한 시간

    // 입력
    while (true)
    {
        char ch;  // 작업명
        int time; // 완료까지 필요한 시간
        cin >> ch >> time;

        // 입력이 모두 끝난 경우
        if (cin.eof())
            break;

        int work = ch - 'A'; // 작업명을 정수형으로 변환
        required_time[work] = time;
        // 작업의 진입 차수를 0으로 초기화
        if (indegree[work] < 0)
            indegree[work] = 0;

        ch = cin.get();
        // 현재 줄에 입력이 더 존재한다면 (선행 작업이 존재한다면)
        while (ch != '\n')
        {
            ch = cin.get();
            if (ch == '\n') // 현재 줄의 입력이 모두 끝난 경우
                break;
            graph[ch - 'A'].push_back(work); // 그래프에 선후 관계 저장
            indegree[work]++;                // 진입 차수 증가
        }
    }

    // 연산 및 출력
    cout << calcTotalTime(graph, indegree, required_time);
    return 0;
}