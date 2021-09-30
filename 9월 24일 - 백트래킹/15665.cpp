// N과 M (11) https://www.acmicpc.net/problem/15665

#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<int> numbers;     // 입력 받은 수
vector<int> sequence; // 출력할 수열

void backtracking(int m, int cnt)
{
    // 기저조건: m개의 수를 뽑았으면 리턴
    if (cnt == m)
    {
        for (int i = 0; i < m; i++)
            cout << sequence[i] << ' ';
        cout << '\n';
        return;
    }
    // 중복을 허용해서 하나씩 수를 뽑아 수열에 저장
    for (auto it = numbers.begin(); it != numbers.end(); it++)
    {
        sequence[cnt] = *it;
        backtracking(m, cnt + 1);
    }
}

int main()
{
    int n, m;

    // 입력
    cin >> n >> m;
    while (n--)
    {
        int num;
        cin >> num;
        numbers.insert(num);
    }
    sequence.assign(m, 0);

    // 연산 및 출력
    backtracking(m, 0);

    return 0;
}