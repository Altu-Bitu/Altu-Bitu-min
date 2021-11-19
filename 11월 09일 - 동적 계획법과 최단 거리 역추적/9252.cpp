// LCS 2 https://www.acmicpc.net/problem/9252

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

// 더 나은 풀이 
// 샘플 코드 참고: https://github.com/Altu-Bitu/Notice/blob/main/11%EC%9B%94%2009%EC%9D%BC%20-%20%EB%8F%99%EC%A0%81%20%EA%B3%84%ED%9A%8D%EB%B2%95%EA%B3%BC%20%EC%B5%9C%EB%8B%A8%20%EA%B1%B0%EB%A6%AC%20%EC%97%AD%EC%B6%94%EC%A0%81/%EA%B3%BC%EC%A0%9C/9252.cpp)

typedef vector<vector<int>> matrix;

int n, m;
vector<int> dr = {-1, 0, -1};
vector<int> dc = {0, -1, -1};

string backtrack(string s1, matrix &path)
{
    string answer;
    int r = n, c = m;
    int dir = path[r][c];
    while (dir != -1)
    {
        if (dir == 2)
            answer += s1[r - 1];
        r += dr[dir];
        c += dc[dir];
        dir = path[r][c];
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

int calcLCSLength(string s1, string s2, matrix &path)
{
    matrix dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = 2;
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = 0;
                if (dp[i][j - 1] > dp[i - 1][j])
                {
                    dp[i][j] = dp[i][j-1];
                    path[i][j] = 1;
                }
            }
        }
    return dp[n][m];
}

int main()
{
    string s1, s2;

    // 입력
    cin >> s1 >> s2;

    n = s1.length();
    m = s2.length();
    matrix path(n + 1, vector<int>(m + 1, -1));

    // 연산 및 출력
    /*
    lcs answer = findLCS(s1, s2);
    cout << answer.first << '\n';
    if (answer.first != 0)
        cout << answer.second;
    */
    int len = calcLCSLength(s1, s2, path);
    cout << len << '\n';
    if (!len)
        return 0;
    string str = backtrack(s1, path);
    cout << str;
}