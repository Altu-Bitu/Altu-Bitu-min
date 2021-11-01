// 겹치는 건 싫어 https://www.acmicpc.net/problem/20922

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 같은 정수가 K개 이하인 최장 연속 부분 수열의 길이를 계산하는 함수
int calcMaxLength(vector<int> seq, int k)
{
    int ans = 1;             // 최대 길이
    int left = 0, right = 1; // 부분 수열의 왼쪽, 오른쪽 포인터
    map<int, int> num_count; // <정수, 부분 수열 내 정수의 개수>
    num_count[seq[left]]++;  // 수열의 첫 원소가 부분 수열 내에 있으므로 개수 증가

    int size = seq.size();
    while (right < size)
    {
        // 새로 부분 수열에 추가된 정수의 개수 증가
        int num = seq[right++];
        num_count[num]++;

        // 새로 추가된 정수의 개수가 K개를 초과한다면
        while (num_count[num] > k)
        {
            // K개 이하가 될 때까지 구간을 줄임
            int sub_num = seq[left++];
            num_count[sub_num]--;
        }

        // 부분 수열의 길이의 최댓값 갱신
        int len = right - left;
        ans = (ans >= len) ? ans : len;
    }
    return ans;
}

int main()
{
    int n, k;

    // 입력
    cin >> n >> k;
    vector<int> seq(n, 0);
    for (int i = 0; i < n; i++)
        cin >> seq[i];

    // 연산 및 출력
    cout << calcMaxLength(seq, k);
    return 0;
}