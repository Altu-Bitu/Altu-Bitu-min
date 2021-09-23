// 이항 계수 1 https://www.acmicpc.net/problem/11050

#include <iostream>

using namespace std;

int main()
{
    float n, k;

    // 입력
    cin >> n >> k;

    // 이항계수 계산
    float result = 1;
    for (int i = 0; i < k; i++)
        result *= ((n - i) / (k - i));

    // 출력
    cout << result << '\n';
}