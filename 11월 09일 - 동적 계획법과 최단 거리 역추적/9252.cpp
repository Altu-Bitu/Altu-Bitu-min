// LCS 2 https://www.acmicpc.net/problem/9252

#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef pair<int, string> lcs; // <LCS의 길이, LCS의 문자열>

// 두 문자열의 LCS를 찾는 함수
// 리턴: <LCS의 길이, LCS>
lcs findLCS(string s1, string s2)
{
    int size1 = s1.length(), size2 = s2.length();
    // matrix[i][j]: s1의 0~i번째 부분과 s2의 0~j번째 부분의 LCS 길이와 문자열
    vector<vector<lcs>> matrix(size1 + 1, vector<lcs>(size2 + 1, {0, ""}));

    for (int i = 1; i <= size1; i++)
    {
        for (int j = 1; j <= size2; j++)
        {
            // 두 문자열의 특정 문자가 같다면
            if (s1[i - 1] == s2[j - 1])
            {
                // 해당 문자를 LCS에 추가
                int len = matrix[i - 1][j - 1].first + 1;
                string str = matrix[i - 1][j - 1].second + s1[i - 1];
                matrix[i][j] = make_pair(len, str);
            }
            // 두 문자가 다르다면
            else
            {
                // 이전까지의 LCS 중 최장 길이인 것을 선택
                lcs max_lcs = (matrix[i - 1][j].first > matrix[i][j - 1].first) ? matrix[i - 1][j] : matrix[i][j - 1];
                matrix[i][j] = max_lcs;
            }
        }
    }
    return matrix[size1][size2];
}

int main()
{
    string s1, s2;

    // 입력
    cin >> s1 >> s2;

    // 연산 및 출력
    lcs answer = findLCS(s1, s2);
    cout << answer.first << '\n';
    if (answer.first != 0)
        cout << answer.second;
    return 0;
}