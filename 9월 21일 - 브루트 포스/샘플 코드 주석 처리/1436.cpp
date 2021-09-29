// 영화감독 숌 https://www.acmicpc.net/problem/1436

#include <iostream>

using namespace std;

// n번째 종말의 숫자를 리턴하는 함수
int endNumber(int n)
{
    int cnt = 0; // cnt번째 종말의 숫자

    // 666(1번째 종말의 숫자)부터 차례로 모두 검사해보기
    // 무조건 리턴값(n번째 종말의 숫자)을 찾게 되므로 무한 루프지만 break가 없어도 됨
    for (int i = 666;; i++)
    {
        string s = to_string(i);     // 숫자 i를 문자열로 치환
        if (s.find("666") != s.npos) // i가 666을 포함한다면
            cnt++;                   // cnt 증가
        if (cnt == n)                // n번째 종말의 숫자까지 검사했다면
            return i;                // i(n번째 종말의 숫자) 리턴
    }
}

int main()
{
    int n; // n번째 종말의 숫자

    //입력
    cin >> n;

    //연산+출력
    cout << endNumber(n) << '\n';

    return 0;
}