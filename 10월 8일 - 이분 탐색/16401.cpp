// 과자 나눠주기 https://www.acmicpc.net/problem/16401

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1. 과자들을 내림차순으로 정렬
    2. left, right 정하기
        - 조카의 수 M > 과자의 수 N
            -> left: 1, right: 가장 큰 과자 길이
        - 조카의 수 M <= 과자의 수 N
            -> left: 가장 작은 과자 길이, right: 가장 큰 과자 길이
    4. mid 길이로 과자 자르기
        - mid 길이로 과자들을 잘랐을 때 만들어지는 과자의 수 >= M
            -> 더 큰 길이로 과자를 자를 수 있음 (left = mid + 1)
        - mid 길이로 과자들을 잘랐을 때 만들어지는 과자의 수 < M
            -> 길이를 줄여야함 (right = mid - 1)
*/

// 나눠줄 수 있는 최대 과자 길이를 구하는 함수
int calcMaxSnackLen(vector<int> snacks, int m, int n)
{
    int max_len = 0;          // 최대 과자 길이
    int size = snacks.size(); // 총 과자 개수
    int left = (m > n) ? 1 : snacks[size - 1];  // 최소 길이
    int right = snacks[0];  // 최대 길이
    while (left <= right)
    {
        int mid = (left + right) / 2; // 검사할 과자 길이
        int num = 0;                  // mid 길이로 잘라서 만들어진 과자 개수
        
        // mid 길이로 과자 자르기
        for (int i = 0; i < size; i++)
        {
            num += (snacks[i] / mid);   
            if (num >= m)
            {
                max_len = mid;
                left = mid + 1;
                break;
            }
        }
        if (num < m)
            right = mid - 1;
    }
    return max_len;
}

int main()
{
    int m, n;
    vector<int> snacks;

    // 입력
    cin >> m >> n;
    snacks.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> snacks[i];

    // 연산 및 출력
    sort(snacks.begin(), snacks.end(), greater<>());
    cout << calcMaxSnackLen(snacks, m, n);

    return 0;
}