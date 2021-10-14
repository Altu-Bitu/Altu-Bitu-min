// 스위치 켜고 끄기 https://www.acmicpc.net/problem/1244

#include <iostream>
#include <vector>

using namespace std;

struct student
{
    int gender; // 1: 남학생, 2: 여학생
    int number; // 학생이 받은 수
};

// 남학생의 스위치 조작
void turnSwitchesByMale(vector<bool> &switches, int number)
{
    int idx = number;
    while (idx < switches.size())
    {
        switches[idx] = !switches[idx];
        idx += number;
    }
}

// 여학생의 스위치 조작
void turnSwitchesByFemale(vector<bool> &switches, int number)
{
    switches[number] = !switches[number];
    int left = number - 1;
    int right = number + 1;
    while (left > 0 && right < switches.size() && switches[left] == switches[right])
    {
        switches[left] = !switches[left];
        switches[right] = !switches[right];
        left--;
        right++;
    }
}

void turnSwitches(vector<bool> &switches, vector<student> &students)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].gender == 1)
            turnSwitchesByMale(switches, students[i].number);
        else
            turnSwitchesByFemale(switches, students[i].number);
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;                    // 스위치 개수
    vector<bool> switches;    // 스위치 상태
    int m;                    // 학생 수
    vector<student> students; // 학생들

    // 입력
    cin >> n;
    switches.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        int s;
        cin >> s;
        switches[i] = s;
    }
    cin >> m;
    students.assign(m, {});
    for (int i = 0; i < m; i++)
        cin >> students[i].gender >> students[i].number;

    // 연산 및 출력
    turnSwitches(switches, students);
    for (int i = 1; i <= n; i++)
    {
        cout << switches[i] << ' ';
        if (i % 20 == 0)
            cout << '\n';
    }

    return 0;
}