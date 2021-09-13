// 요요 시뮬레이션 https://www.acmicpc.net/problem/19636

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    int weight;   // 다이어트 전 체중
    int base;     // 일일 기초대사량
    int t;        // 기초대사량 변화 역치
    int period;   // 다이어트 기간
    int intake;   // 일일 섭취량
    int activity; // 일일 활동대사량

    // 입력
    cin >> weight >> base >> t >> period >> intake >> activity;
    int before_intake = base; // 다이어트 전 일일 섭취량

    // 기초대사량 변화 고려 X 몸무게 출력
    int result = weight + (intake - (base + activity)) * period;
    if (result <= 0)
        cout << "Danger Diet\n";
    else
        cout << result << " " << base << '\n';

    // 기초대사량 변화 고려 O 몸무게 출력
    while (period--)
    {
        // 일일 변화량
        int change = intake - (base + activity);

        // 기초대사량과 몸무게 변화
        if (abs(change) > t)
            base += (change - 1) / 2;
        weight += change;

        if (weight <= 0 || base <= 0)
        {
            cout << "Danger Diet\n";
            return 0;
        }
    }
    cout << weight << ' ' << base << ' ';
    // 요요 계산
    cout << ((before_intake > base) ? "YOYO" : "NO");
}
