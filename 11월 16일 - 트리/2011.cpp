// 암호코드 https://www.acmicpc.net/problem/2011

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000;

// 암호를 해독할 수 있는 경우의 수를 계산하는 함수
int calcNumOfDecode(string code)
{
    // 첫 숫자가 0이면 암호를 해독할 수 없음
    if (code[0] == '0')
        return 0;

    int len = code.length();
    // dp[i]: i번째 숫자까지의 암호를 해독할 수 있는 경우의 수
    vector<int> dp(len + 1, 0);
    // 1번째 숫자의 해독 가능 경우의 수는 1 (0번째는 점화식 계산을 위한 초기화)
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= len; i++)
    {
        int prev = code[i - 2] - '0';
        int cur = code[i - 1] - '0';

        // 이전 숫자와 함께 하나의 글자로 변환 가능한 경우
        if (prev == 1 || (prev == 2 && cur <= 6))
            // 단, 현재 숫자가 0이면 무조건 이전 숫자와 함께 변환해야 함
            if (cur == 0)
                dp[i] = dp[i - 2] % MOD;
            else
                dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
        // 단독으로만 변환하는 경우
        else if (cur > 0)
            dp[i] = dp[i - 1] % MOD;
        // 해독할 수 없는 경우
        else
            return 0;
    }
    return dp[len];
}

int main()
{
    string code;
    cin >> code;
    cout << calcNumOfDecode(code);
    return 0;
}