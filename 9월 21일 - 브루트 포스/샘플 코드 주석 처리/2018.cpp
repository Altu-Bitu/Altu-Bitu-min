// 통계학 https://www.acmicpc.net/problem/2108

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int SIZE = 4000; // 양수의 최댓값

// 최빈값을 리턴하는 함수
int calcMode(vector<int> &frequency)
{
    int max_value = 0; // 최빈값의 빈도수

    // 최빈값의 빈도수 구하기
    // 0부터 8000까지 모든 수를 검사 (정확히는 i - 4000을 검사하는 것)
    for (int i = 0; i <= SIZE * 2; i++)
    {
        // 현재까지의 최대 빈도수보다 i의 등장 빈도가 더 크다면
        if (frequency[i] > max_value)
            max_value = frequency[i]; // 최대 빈도수 갱신
    }

    int cnt = 0;  // 최빈값 개수
    int mode = 0; // 최빈값

    // 두 번째로 작은 최빈값 구하기
    // 0부터 8000까지 모든 수를 검사 (정확히는 i - 4000을 검사하는 것)
    for (int i = 0; i <= SIZE * 2; i++)
    {
        // i가 최빈값이라면
        if (frequency[i] == max_value)
        {
            mode = i - SIZE; // i는 SIZE를 더한 값이므로 실제 최빈값은 SIZE를 빼주어야 함
            cnt++;           // 최빈값 개수 증가
            if (cnt == 2)    // 두 번째로 작은 최빈값이면
                break;       // 검사 중지
        }
    }

    // 최빈값 리턴
    return mode;
}

/**
 * 1. 산술평균 계산 시 실수 자료형으로 맞춰준 후 반올림하는거 주의
 * 2. n은 홀수이므로 중앙값은 항상 (n / 2)번째 인덱스
 * 3. 최빈값은 동일한 빈도수 내에서 두 번째로 '작은' 값임
 * 4. 최빈값이 유일하게 하나만 있는 경우 고려
 */

int main()
{
    int n; // n은 홀수

    //입력
    cin >> n;

    vector<int> num(n); // 입력 받은 정수들 저장
    // 인덱스: 입력 수 + 4000 (0 ~ 8000). 저장 값: 인덱스에 해당하는 숫자가 입력된 빈도
    vector<int> frequency(SIZE * 2 + 1, 0);

    double sum = 0; // 평균 구하기 위한 합 변수
    // n개 만큼 반복
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];              // 정수를 입력 받음
        sum += (double)num[i];      // 정수를 실수형으로 변환한 후 sum에 더함
        frequency[num[i] + SIZE]++; // 입력 받은 수의 빈도 증가
    }

    //연산
    sort(num.begin(), num.end()); // 정수들 오름차순으로 정렬

    //출력
    cout << round(sum / n) << '\n';               // 산술평균
    cout << num[n / 2] << '\n';                   // 중앙값
    cout << calcMode(frequency) << '\n';          // 최빈값
    cout << num[num.size() - 1] - num[0] << '\n'; // 범위

    return 0;
}