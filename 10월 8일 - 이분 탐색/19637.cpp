// IF문 좀 대신 써줘 https://www.acmicpc.net/problem/19637

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct title
{
    int upperbound; // 현재 칭호의 최대 전투력(상한값)
    string name;    // 칭호의 이름
};

// 전투력(power)에 맞는 칭호를 리턴하는 함수
string setTitle(vector<title> &titles, int power)
{
    string ans = "";
    int left = 0;
    int right = titles.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2; // 현재 칭호를 가리키는 인덱스
        // power가 현재 칭호의 전투력 구간 혹은 더 작은 구간에 속한다면
        if (power <= titles[mid].upperbound)
        {
            // 칭호 갱신
            ans = titles[mid].name;
            // power가 전투력 상한값이 더 작은 구간에 속할 수 있으므로 상한값이 작은 칭호들 재탐색
            right = mid - 1;
        }
        // power가 현재 칭호의 전투력 상한값을 넘어간다면
        else
            // 현재 칭호보다 상한값이 큰 칭호들 재탐색(mid 기준 오른쪽 절반 탐색)
            left = mid + 1;
    }
    return ans;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; // 칭호 개수
    int m; // 캐릭터 개수
    vector<title> titles;

    // 입력
    cin >> n >> m;
    int idx = 0;
    while (n--)
    {
        title t;
        cin >> t.name >> t.upperbound;

        // 이전에 입력된 칭호와 상한값이 같다면 현재 입력 무시
        if (idx > 0 && titles[idx - 1].upperbound == t.upperbound)
            continue;

        titles.push_back(t);
        idx++;
    }

    while (m--)
    {
        int power; // 전투력
        cin >> power;
        // 연산 및 출력
        cout << setTitle(titles, power) << '\n';
    }
    return 0;
}