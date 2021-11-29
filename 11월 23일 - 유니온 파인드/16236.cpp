// 아기 상어 https://www.acmicpc.net/problem/16236

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef vector<vector<int>> matrix;
typedef pair<int, int> ci;

/*
1. BFS로 먹을 수 있는 크기의 물고기 중 가장 가까운 거리를 계산한다.
2. 물고기를 먹었다면, 해당 위치로부터 다시 1번을 수행한다.
3. 더 이상 먹을 수 있는 물고기가 없다면 종료한다.
*/

// 우선순위 재정의
// 가장 가까운 거리인 것 > 가장 위쪽 좌표인 것 > 가장 왼쪽 좌표인 것 순으로 정렬
struct cmp
{
    bool operator()(const pair<int, ci> &a, const pair<int, ci> &b)
    {
        int dist = a.first - b.first;
        int dx = a.second.first - b.second.first;
        int dy = a.second.second - b.second.second;
        if (!dist)
            return dist;
        if (!dx)
            return dx;
        return dy;
    }
};

// 아기 상어가 지나갈 수 있는지 판별하는 함수
bool canPass(matrix &s, int n, int size, int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n && s[x][y] <= size;
}

// 먹을 수 있는 물고기 중 가장 가까운 물고기까지의 거리를 계산하는 함수
int calcShortestDist(matrix &s, int n, ci &shark, int size)
{
    vector<int> dx = {-1, 0, 0, 1};
    vector<int> dy = {0, -1, 1, 0};
    vector<vector<bool>> visited(n, vector<bool>(n, false));     // 방문 체크
    priority_queue<pair<int, ci>, vector<pair<int, ci>>, cmp> q; // <이동한 거리, <x, y>>

    // 초기화
    q.push(make_pair(0, shark));
    visited[shark.first][shark.second] = true;

    // BFS
    while (!q.empty())
    {
        int dist = q.top().first;
        int x = q.top().second.first;
        int y = q.top().second.second;
        q.pop();

        // 먹을 수 있는 물고기까지 도착했다면
        if (s[x][y] > 0 && s[x][y] < size)
        {
            // 공간의 상태 및 상어 위치 갱신
            s[x][y] = 0;
            shark = make_pair(x, y);
            return dist;
        }

        for (int i = 0; i < 4; i++)
        {
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if (canPass(s, n, size, next_x, next_y) && !visited[next_x][next_y])
            {
                q.push({dist + 1, {next_x, next_y}});
                visited[next_x][next_y] = true;
            }
        }
    }
    return 0; // 먹을 수 있는 물고기가 없는 경우
}

int main()
{
    // 입력
    int n;
    cin >> n;
    matrix s(n, vector<int>(n, 0)); // 공간의 상태
    ci shark;                       // 아기 상어의 위치
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == 9)
            {
                s[i][j] = 0; // 나중에 지나갈 수 있도록 0으로 바꿔줌
                shark = make_pair(i, j);
            }
        }

    // 연산
    int answer = 0, size = 2;
    for (int i = 0;; i++)
    {
        // 필요한 개수만큼 물고기를 먹엇다면 아기 상어의 크기 증가
        if (i == size)
        {
            size++;
            i = 0;
        }
        // 가장 가까운 먹을 수 있는 물고기까지의 거리
        int dist = calcShortestDist(s, n, shark, size);
        // 먹을 수 있는 물고기가 없으면 종료
        if (!dist)
            break;
        answer += dist;
    }

    // 출력
    cout << answer;
    return 0;
}