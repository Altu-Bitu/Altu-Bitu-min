// 좌표 정렬하기 2 https://www.acmicpc.net/problem/11651

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

bool compPoints(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.second == b.second)
        return (a.first < b.first);
    return (a.second < b.second);
}

int main()
{
    int n;
    vector<pair<int, int>> points;

    scanf("%d", &n);
    points.assign(n, {});
    for (int i = 0; i < n; i++)
    {
        pair<int, int> p;
        scanf("%d %d", &p.first, &p.second);
        points[i] = p;
    }

    sort(points.begin(), points.end(), compPoints);

    for (int i = 0; i < n; i++)
        printf("%d %d\n", points[i].first, points[i].second);

    return 0;
}