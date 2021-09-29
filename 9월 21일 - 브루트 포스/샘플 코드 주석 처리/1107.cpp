// 리모컨 https://www.acmicpc.net/problem/1107

#include <iostream>
#include <vector>

using namespace std;
const int MAX_CHANNEL = 1000000; // 최대 채널

vector<bool> broken(11); // 버튼별 고장 여부

// 리모컨의 버튼들로 이 채널을 누를 수 있는지 검사. 만약 누를 수 있다면 누르는 횟수 리턴
int canPress(int channel)
{
    int cnt = 0; // 버튼을 누르는 횟수

    if (channel == 0)      // 0번 채널이라면
        return !broken[0]; // '0' 버튼의 고장 여부와 반대로 리턴

    // 채널의 각 자리수를 모두 검사할 때까지 반복
    while (channel != 0)
    {
        if (broken[channel % 10]) // 해당 자리수의 버튼이 고장났다면
            return 0;             // 리모컨의 버튼들로 해당 채널을 누를 수 없으므로 0 리턴
        channel /= 10;            // 검사한 자리수는 제거
        cnt++;                    // 버튼을 누르는 횟수 증가
    }
    return cnt; // 버튼을 누르는 횟수 리턴
}

/**
 * 0번 채널부터 MAX_CHANNEL까지 모든 채널에 대해 이동 가능 여부를 체크
 * 1,000,000까지만 계산하면 되기 때문에 무식하게 풀어도 시간안에 풀 수 있음
 */
int main()
{
    int n;      // 이동하려는 채널
    int m;      // 고장난 버튼 수
    int button; // 고장난 버튼

    // 입력
    cin >> n >> m;
    // 고장난 버튼 수만큼 반복
    for (int i = 0; i < m; i++)
    {
        cin >> button;         // 고장난 버튼 입력 받음
        broken[button] = true; // 해당 버튼의 고장 여부 표시
    }

    // 연산
    // 최솟값 초기화: +/- 버튼으로만 n까지 이동할 때의 클릭 수
    int min_click = abs(n - 100); // 버튼을 누르는 최솟값

    // 고장난 버튼이 10개라면
    if (m == 10)
    {
        // 누를 수 있는 숫자 버튼이 없으므로 min_click(+/- 버튼만 사용)을 출력
        cout << min_click;
        return 0; // 프로그램 종료
    }

    // 0번 채널부터 최대 채널까지 반복
    for (int i = 0; i < MAX_CHANNEL; i++)
    {                                                           // i번 채널에 대해
        int press_cnt = canPress(i);                            // i번 채널에 가기 위해 버튼을 눌러야 하는 횟수 (숫자 버튼만 사용)
        if (press_cnt != 0)                                     // 0이 아니라면 i번 채널로 이동할 수 있음
            min_click = min(min_click, abs(n - i) + press_cnt); // (i번 채널로 이동 후, i번에서 n번까지 +/- 버튼 누른 값)과 (현재까지의 최솟값) 비교, 갱신
    }

    //출력
    cout << min_click;
}