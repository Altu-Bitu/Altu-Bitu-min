// 숨바꼭질 https://www.acmicpc.net/problem/1697

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_POINT = 100000;

void moveNextPoint(vector<int> &time, queue<int> &points, int next_p, int next_t)
{
    if (next_p >= 0 && next_p <= MAX_POINT && !time[next_p])
    {
        points.push(next_p);
        time[next_p] = next_t;
    }
}

int hideAndSeek(int n, int k)
{
    vector<int> time(MAX_POINT + 1, 0);
    queue<int> points;
    points.push(n);

    while (!points.empty())
    {
        int p = points.front();
        int t = time[p];
        points.pop();

        if (p == k)
            break;

        moveNextPoint(time, points, p + 1, ++t);
        moveNextPoint(time, points, p - 1, t);
        moveNextPoint(time, points, 2 * p, t);
    }
    return time[k];
}

int main()
{
    int n, k;

    // 입력
    cin >> n >> k;

    // 연산 및 출력
    cout << hideAndSeek(n, k);
    return 0;
}