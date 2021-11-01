// 거리두기 확인하기 https://programmers.co.kr/learn/courses/30/lessons/81302#fn1

/*
풀이
P이면 -> DFS 시작
DFS에서는? 맨해튼 거리 2 이하인 주변을 검사함
O이면 -> 방문 체크
X이면 -> 패스
P이면 -> false 리턴
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int SIZE = 5;

// 상, 우, 하, 좌, 대각선 좌표
vector<int> dr = {0, 1, 0, -1};
vector<int> dc = {-1, 0, 1, 0};

struct point
{
    int x;
    int y;
    int dist;
};

// (row, col) 주변의 맨해튼 거리 2 이하인 좌표들을 검사하는 함수
// P가 있다면 false 리턴
bool bfs(vector<string> &place, int row, int col)
{
    queue<point> q;
    vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));
    q.push({row, col, 0});
    visited[row][col] = true;

    while (!q.empty())
    {
        point p = q.front();
        q.pop();
        visited[p.x][p.y] = true;
        int cdist = p.dist + 1;

        for (int i = 0; i < 4; i++)
        {
            int cx = p.x + dr[i];
            int cy = p.y + dc[i];

            if (cx < 0 || cx >= SIZE || cy < 0 || cy >= SIZE)
                continue;

            if (place[cx][cy] == 'P' && !visited[cx][cy])
                return false;

            if (place[cx][cy] == 'O' && !visited[cx][cy] && cdist < 2)
            {
                q.push({cx, cy, cdist});
                visited[cx][cy] = true;
            }
        }
    }

    return true;
}

bool isDistancing(vector<string> &place)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (place[i][j] == 'P' && !bfs(place, i, j))
                return 0;
    return 1;
}

vector<int> solution(vector<vector<string>> places)
{
    vector<int> answer(SIZE, 0);
    for (int i = 0; i < SIZE; i++)
        answer[i] = isDistancing(places[i]);
    return answer;
}

int main()
{
    vector<vector<string>> places = {{"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},
                                     {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
                                     {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
                                     {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
                                     {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}};

    vector<int> answer = solution(places);
    for (int i = 0; i < SIZE; i++)
        cout << answer[i] << ' ';
    return 0;
}