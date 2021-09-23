// 골드바흐의 추측 https://www.acmicpc.net/problem/6588

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int MAX_N = 1000000;
vector<bool> is_prime;

// n까지의 소수를 구하는 함수
vector<bool> findPrimes(int n)
{
    vector<bool> is_prime(n + 1, true); // n 까지의 소수

    // 소수 판별
    for (int i = 2; i * i <= n; i++)
    {
        if (is_prime[i])
        {
            for (int j = i + i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return is_prime;
}

// 짝수를 두 홀수 소수의 합으로 바꾸는 함수
pair<int, int> evenToPrimeSum(int even)
{
    pair<int, int> prime_sum(0, 0); // 두 홀수 소수

    // 소수의 합 구하기
    for (int i = 3; i <= even; i += 2)
    {
        if (is_prime[i] && is_prime[even - i])
        {
            prime_sum.first = i;
            prime_sum.second = even - i;
            break;
        }
    }
    return prime_sum;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    // 1,000,000 (최대 n)까지의 소수 구하기
    is_prime = findPrimes(MAX_N);

    int n;
    while (true)
    {
        cin >> n;
        if (n == 0)
            return 0;

        // 계산 및 출력
        pair<int, int> sum = evenToPrimeSum(n);
        if (sum.first == 0)
            cout << "Goldbach's conjecture is wrong.\n";
        else
            cout << n << " = " << sum.first << " + " << sum.second << '\n';
    }
}