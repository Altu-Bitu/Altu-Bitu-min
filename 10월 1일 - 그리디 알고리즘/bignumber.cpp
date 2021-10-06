// 큰 수 만들기 https://programmers.co.kr/learn/courses/30/lessons/42883?language=cpp

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    1. 하나씩 검사하면서 가장 큰 수를 찾음 (k번째 까지만 검사)
    2. 가장 큰 수보다 이후에 등장하는 다음으로 큰 수를 찾음
    3. 가장 큰 수가 여러 개라면
        => 먼저 등장한 숫자 선택
*/

// number에서 k개의 수를 제거했을 때, 찾을 수 있는 가장 큰 숫자를 구하는 함수
// start번째 숫자부터 검사 시작
string findBigNumber(string number, int start, int k)
{
    int len = number.length() - start; // 남은(검사할) 숫자 개수
    int pick = number.length() - k;    // 뽑을 숫자 개수

    // 뽑을 숫자 개수가 0이면 빈 문자열 리턴
    if (pick == 0)
        return "";

    // 남은 숫자 개수와 뽑을 숫자 개수가 같다면 남은 숫자들을 그대로 리턴
    if (len == pick)
        return number.substr(start, pick);

    int big_idx = start; // 가장 큰 숫자의 인덱스

    // 가장 큰 수 찾기
    for (int i = start + 1; i <= k; i++)
        if (number[big_idx] < number[i])
            big_idx = i;

    return number[big_idx] + findBigNumber(number, big_idx + 1, k + 1);
}

string solution(string number, int k)
{
    string answer;
    int start = 0; // 검사를 시작할 인덱스
    int len;       // 남은(검사할) 숫자 개수
    int pick;      // 뽑을 숫자 개수
    while (k < number.length())
    {
        len = number.length() - start;
        pick = number.length() - k;

        // 남은 숫자 개수와 뽑을 숫자 개수가 같다면 남은 숫자들을 그대로 추가
        if (len == pick)
        {
            answer += number.substr(start, pick);
            break;
        }

        int big_idx = start; // 가장 큰 숫자의 인덱스

        // 가장 큰 수 찾기
        for (int i = start + 1; i <= k; i++)
            if (number[big_idx] < number[i])
                big_idx = i;

        // 가장 큰 수 추가
        answer += number[big_idx];
        // 추가한 수 다음 인덱스부터 다시 검사 반복
        start = big_idx + 1;
        k++;
    }
    return answer;
}

// 프로그래머스 메인 함수
int main()
{
    string number = "1924";
    int k = 2;
    cout << solution(number, k);
    return 0;
}