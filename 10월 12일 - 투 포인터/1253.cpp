// 좋다 https://www.acmicpc.net/problem/1253

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 좋은 수의 개수를 구하는 함수
int calcNumOfGoodNumbers(vector<int> &numbers)
{
    int ans = 0;                       // 좋은 수의 개수
    int last_idx = numbers.size() - 1; // numbers의 맨 끝 인덱스

    for (int i = 0; i <= last_idx; i++)
    {
        int num = numbers[i];                                  // 검사하려는 수
        int left = (i == 0) ? 1 : 0;                           // 검사하려는 수를 제외하고, 맨 왼쪽 수의 인덱스
        int right = (i == last_idx) ? last_idx - 1 : last_idx; // 검사하려는 수를 제외하고, 맨 오른쪽 수의 인덱스

        // num가 좋은 수인지 검사
        while (left < right)
        {
            int sum = numbers[left] + numbers[right];
            if (sum > num)
                right = (right - 1 == i) ? right - 2 : right - 1; // right가 num을 가리키면 하나 더 감소
            else if (sum < num)
                left = (left + 1 == i) ? left + 2 : left + 1; // left가 num을 가리키면 하나 더 증가
            else
            {
                ans++;
                break;
            }
        }
    }
    return ans;
}

int main()
{
    int n;

    // 입력
    cin >> n;
    vector<int> numbers(n, 0);
    for (int i = 0; i < n; i++)
        cin >> numbers[i];

    // N개의 수 오름차순 정렬
    sort(numbers.begin(), numbers.end());

    // 연산 및 출력
    cout << calcNumOfGoodNumbers(numbers);
    return 0;
}