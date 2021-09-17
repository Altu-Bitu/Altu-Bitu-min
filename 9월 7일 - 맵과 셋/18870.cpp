// 좌표 압축 https://www.acmicpc.net/problem/18870

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    vector<int> points; // 입력된 좌표를 그대로 저장
    map<int, int> m;    // <좌표, 압축된 좌표>

    // 입력
    cin >> n;
    points.assign(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i];
        m[points[i]] = 0;
    }

    // 좌표 압축 (제일 작은 좌표부터 0으로 압축)
    int idx = 0;
    for (auto it=m.begin(); it!=m.end(); it++)
        it->second = idx++;

    // 출력
    for (int i = 0; i < points.size(); i++)
        cout << m[points[i]] << ' ';
}