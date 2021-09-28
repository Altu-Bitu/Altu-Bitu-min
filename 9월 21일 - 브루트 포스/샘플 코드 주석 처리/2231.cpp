// 분해합 https://www.acmicpc.net/problem/2231

#include <iostream>

using namespace std;

// N의 가장 작은 생성자를 구하는 함수
int constructor(int n)
{
    // n까지 분해합 모두 구해보며 분해합이 n인 경우 찾음
    for (int i = 1; i < n; i++)
    {
        int k = i;   // i는 가공하면 안되므로 k에 저장
        int sum = k; // 분해합 -> 해당 수
        // 분해합 -> 각 자리수의 합
        while (k > 0)
        {                    
            sum += (k % 10); // 뒤에서부터 k의 각 자리수를 sum에 더함
            k /= 10;         // sum에 더한 자리수는 k에서 제거
        }
        if (sum == n) // 분해합이 n이라면
            return i; // i(n의 가장 작은 생성자) 리턴
    }
    return 0; // 생성자가 없는 경우 0 리턴
}

int main()
{
    // 입력 받을 자연수
    int n;

    // 입력
    cin >> n;

    // 연산 + 출력
    cout << constructor(n) << '\n';

    return 0;
}