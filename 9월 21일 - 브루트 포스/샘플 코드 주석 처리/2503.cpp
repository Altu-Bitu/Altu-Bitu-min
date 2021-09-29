// 숫자 야구 https://www.acmicpc.net/problem/2503

#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> ci; // <스트라이크 개수, 볼 개수>

// 한 줄에 입력되는 질문과 답
struct baseball
{
    string num; // 질문: 서로 다른 세 자리 수
    int strike; // 답: 스트라이크 개수
    int ball;   // 답: 볼 개수
};

// 두 수의 스트라이크와 볼 개수를 계산하는 함수
ci cntStrikeBall(string &s1, string &s2)
{
    int strike_cnt = 0; // s1과 s2사이의 strike 개수
    int ball_cnt = 0;   // s1과 s2사이의 ball 개수

    // 각 자리수 비교(3자리)
    for (int i = 0; i < 3; i++)
    {
        if (s1[i] == s2[i])                 // 위치와 수가 정확히 일치한다면
            strike_cnt++;                   // 스트라이크 개수 증가
        else if (s1.find(s2[i]) != s1.npos) // 위치는 다르지만 수가 존재한다면
            ball_cnt++;                     // 볼 개수 증가
    }

    return ci(strike_cnt, ball_cnt); // <스트라이크 개수, 볼 개수> 리턴
}

// 가능한 답의 총 개수를 리턴하는 함수
int game(int n, vector<baseball> &question)
{
    int ans = 0; // 정답 개수

    // 정답은 서로 다른 세자리 수이므로 123부터 987까지 검사
    for (int i = 123; i <= 987; i++)
    {
        bool check = true;        // 가능한 답인지 체크
        string s1 = to_string(i); // i(정답인지 확인할 수)를 문자열로 변환

        if (s1[0] == '0' || s1[1] == '0' || s1[2] == '0')       // 세자리 중 0이 하나라도 있다면
            continue;                                           // 답이 될 수 없으므로 다음 검사로 넘어감
        if (s1[0] == s1[1] || s1[0] == s1[2] || s1[1] == s1[2]) // 세자리 중 서로 같은 수가 하나라도 있다면
            continue;                                           // 답이 될 수 없으므로 다음 검사로 넘어감

        // i(정답인지 확인할 수)와 질문으로 들어온 모든 수를 비교
        for (int j = 0; j < n; j++)
        {
            string s2 = question[j].num;    // 질문으로 들어온 수를 문자열로 변환
            ci cnt = cntStrikeBall(s1, s2); // s1과 s2사이의 스트라이크와 볼 개수

            // 질문(question[j])의 답과 s1과 s2를 비교한 스트라이크, 볼 개수가 하나라도 다르면
            if (cnt.first != question[j].strike || cnt.second != question[j].ball)
            {
                check = false; // 해당 수는 답이 아님
                break;         // 질문과의 비교 중지
            }
        }

        // 해당 수가 답이라면
        if (check)
            ans++; // 정답 개수 증가
    }

    // 정답 개수 리턴
    return ans;
}

/**
 * [숫자 야구]
 * 서로 다른 세 자리 수에서 위치+수 같으면 스트라이크, 위치는 다르고 수가 존재하면 볼
 * n개의 질문으로 수와 스트라이크와 볼 개수가 주어질 때, 이를 모두 만족하는 서로 다른 세 자리 정답 수의 개수
 *
 * [풀이]
 * 서로 다른 세 자리수는 123 ~ 987이 가능하다. 이는 총 865가지
 * 질문 n의 범위는 최대 100
 * 따라서 123부터 하나씩 증가시키며 정답이 되는지 검사해도 865 * 100 * 3(자릿수)으로 접근 충분히 가능!
 */

int main()
{
    int n; // 질문의 개수

    //입력
    cin >> n;

    vector<baseball> question(n); // 입력 받은 질문과 그에 대한 답을 저장
    // n개의 질문을 받음
    for (int i = 0; i < n; i++)
        cin >> question[i].num >> question[i].strike >> question[i].ball; // 질문, 스트라이크 개수, 볼 개수를 순서대로 입력 받음

    //연산 + 출력
    cout << game(n, question);

    return 0;
}