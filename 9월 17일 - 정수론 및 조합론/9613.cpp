// GCD 합 https://www.acmicpc.net/problem/9613

#include <iostream>
#include <vector>

using namespace std;

// GCD를 구하는 함수
int findGCD(int a, int b)
{
    if (b == 0)
        return a;
    else if (a > b)
        return findGCD(b, a % b);
    else
        return findGCD(a, b % a);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;               // 테스트 케이스 개수
    int n;               // 정수 개수
    vector<int> numbers; // 입력된 수들

    // 입력
    cin >> t;
    while (t--)
    {
        cin >> n;
        numbers.assign(n, 0);
        for (int i = 0; i < n; i++)
            cin >> numbers[i];

        // 모든 쌍의 GCD의 합 구하기
        long long gcdSum = 0;
        for (int i = 0; i < n - 1; i++) // GCD를 구할 첫번째 수
        {
            for (int j = i + 1; j < n; j++) // GCD를 구할 두번째 수
                gcdSum += findGCD(numbers[i], numbers[j]);
        }

        // GCD의 합 출력
        cout << gcdSum << '\n';
    }
}