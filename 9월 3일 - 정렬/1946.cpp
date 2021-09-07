// 신입 사원 https://www.acmicpc.net/problem/1946

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calcPass(vector<pair<int, int>> applicants)
{
    int result = 1;
    int minScore = applicants[0].second;
    for (int i = 1; i < applicants.size(); i++)
    {
        if (applicants[i].second < minScore)
        {
            minScore = applicants[i].second;
            result++;
        }
    }
    return result;
}

int main()
{
    int test, number, result;
    vector<pair<int, int>> applicants;
    pair<int, int> score;

    cin >> test;
    for (int t = 0; t < test; t++)
    {
        cin >> number;
        applicants.assign(number, {});
        for (int n = 0; n < number; n++)
        {
            cin >> score.first >> score.second;
            applicants[n] = score;
        }
        sort(applicants.begin(), applicants.end());
        cout << calcPass(applicants) << "\n";
    }

    return 0;
}