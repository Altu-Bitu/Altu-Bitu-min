// 기타 레슨 https://www.acmicpc.net/problem/2343

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1. 강의를 번호 순으로 정렬 (입력 그대로)
    2. left, right 정하기
        - left(블루레이의 최소 길이): 1
        - right(블루레이의 최대 길이): 모든 강의 시간의 합 (한 블루레이에 모두 녹화함)
    3. mid 길이의 블루레이 M개에 모든 강의를 나눠담을 수 있는지 확인
        - 모든 강의가 M개의 블루레이에 나눠담김
            -> 길이 줄이기 (더 작은 길이도 확인)
        - 모든 강의를 M개의 블루레이에 나눠담을 수 없음
            -> 길이 늘리기
*/

// 블루레이의 최소 길이를 계산하는 함수
int calcMinBlurayLength(vector<int> lectures, int sum, int m)
{
    int left = 1;
    int right = sum;
    int ans = 0;

    while (left <= right)
    {
        int mid = (left + right) / 2; // 블루레이 길이
        bool can_record = true; // 블루레이 길이가 mid일 때 강의들을 나눠 담을 수 있는지 여부
        int lectures_sum = 0;   // 한 블루레이에 담길 강의들의 길이 합
        int bluray_num = 1;     // 강의들을 mid 길이 블루레이에 나눠담을 때 만들어지는 블루레이 개수
        for (int i = 0; i < lectures.size(); i++)
        {
            if (lectures_sum + lectures[i] > mid)
            {
                bluray_num++;
                lectures_sum = 0;
            }
            lectures_sum += lectures[i];
            if (lectures[i] > mid || bluray_num > m)
            {
                can_record = false;
                break;
            }
        }
        if (can_record)
        {
            ans = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    return ans;
}

int main()
{
    int n; // 강의 수
    int m; // 블루레이 수

    // 입력
    cin >> n >> m;
    vector<int> lectures(n, 0);
    int sum = 0; // 모든 강의 시간의 합
    for (int i = 0; i < n; i++)
    {
        cin >> lectures[i];
        sum += lectures[i];
    }

    // 연산 및 출력
    if (n != m)
        cout << calcMinBlurayLength(lectures, sum, m);
    else
    {
        sort(lectures.begin(), lectures.end(), greater<>());
        cout << lectures[0];
    }
    return 0;
}