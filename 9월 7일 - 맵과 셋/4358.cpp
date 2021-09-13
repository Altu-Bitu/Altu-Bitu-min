// 생태학 https://www.acmicpc.net/problem/4358

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    map<string, int> trees; // <나무 종, 나무 개수>
    string tree;            // 나무 종 이름
    int n = 0;              // 전체 나무 개수

    // 파일 끝까지 입력 받음
    while (!cin.eof())
    {
        getline(cin, tree);
        if (!tree.empty())
        {
            trees[tree]++;
            n++;
        }
    }

    // 출력
    for (auto it = trees.begin(); it != trees.end(); it++)
    {
        double rate = ((double)it->second / n) * 100;

        // 소수점 4째자리까지만 출력
        cout << fixed;
        cout.precision(4);
        cout << it->first << ' ' << rate << '\n';
    }
}
