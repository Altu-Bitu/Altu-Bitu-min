// 민겸 수 https://www.acmicpc.net/problem/21314

#include <iostream>

using namespace std;

// 민겸 수를 십진수로 변환하였을 때, 가장 큰 값을 리턴하는 함수
string maxNum(string s)
{
    string ans = "";  // 십진수로 변환했을 때, 가장 큰 값
    string temp = ""; // 문자열 s에 존재하는 하나의 민겸 수를 십진수로 변환한 값
    // 문자열을 한 글자씩 읽음 (i: s의 i번째 글자)
    for (int i = 0; i < s.length(); i++)
    {
        temp += '0'; // M의 개수만큼 십진수에는 10이 곱해지므로 temp의 맨 뒤에 0을 추가
        if (s[i] == 'K')
        {                  // K가 등장하면, 지금까지 읽은 M들과 K를 하나의 민겸 수로 처리
            temp[0] = '5'; // K로 끝나므로 5*10^N 형식으로 변환(temp의 맨 앞을 5로 변경)
            ans += temp;   // 변환된 십진수를 ans에 이어붙임
            temp = "";     // 다음 민경 수를 변환하기 위해 temp 초기화
        }
    }
    if (temp.length() >= 1)
    { // K로 끝나지 않았다면 모든 M을 하나의 민경 수로 처리
        for (int i = 0; i < temp.length(); i++)
            temp[i] = '1'; // 모든 M을 1로 변환
        ans += temp;       // 변환된 십진수를 ans에 이어붙임
    }
    return ans; // 가장 큰 십진수 변환 값 리턴
}

// 민겸 수를 십진수로 변환하였을 때, 가장 작은 값을 리턴하는 함수
string minNum(string s)
{
    string ans = "";  // 십진수로 변환했을 때, 가장 작은 값
    string temp = ""; // 문자열 s에 존재하는 하나의 민겸 수를 십진수로 변환한 값
    char first = '1'; // K를 무조건 단독 변환하므로 temp의 첫글자는 무조건 1임
    // 문자열을 한 글자씩 읽음 (i: s의 i번째 글자)
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'M')
        {                  // i번째 글자가 M이라면
            temp += first; // temp에 first(0 또는 1)를 이어붙임
            first = '0';   // 다음 글자도 M이라면 first는 0이고, 0을 이어붙임
        }
        else
        {                      // i번째 글자가 K라면
            ans += temp + '5'; // 지금까지의 M들을 한번에 변환(temp)하고, K는 단독 변환
            temp = "";         // 다음 민경 수를 변환하기 위해 temp 초기화
            first = '1';       // 다음 글자가 M이라면 첫글자는 1이됨
        }
    }
    // K로 끝나지 않았다면
    if (temp.length() >= 1)
        ans += temp; // 지금까지의 M들을 한번에 변환 후 이어붙임
    return ans;      // 가장 작은 십진수 변환 값 리턴
}

/**
 * [가장 큰 값]
 * 민겸수에서 마지막이 K일 때, K까지 포함하여 십진수로 변환한다
 * K로 끝나지 않는다면 각 M을 모두 하나로 처리한다 (ex. MMM -> 111)
 *
 * [가장 작은 값]
 * K는 무조건 단독으로 변환한다
 * 나머지 M묶음들은 같이 변환한다
 * ex. MMKMM -> 10510
 */

int main()
{
    string s; // 민겸 수

    //입력
    cin >> s;

    //출력
    cout << maxNum(s) << '\n'
         << minNum(s) << '\n';

    return 0;
}