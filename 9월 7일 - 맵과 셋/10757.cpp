// 큰 수 A+B https://www.acmicpc.net/problem/10757

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> add(string a, string b)
{
    vector<char> result;                                    // a + b 결과
    int count = 0;                                          // 올라가는 수
    int a_index = a.length() - 1, b_index = b.length() - 1; // 지금 더하려는 숫자의 인덱스

    // a, b를 뒤에서부터 한자리씩 더함
    while (a_index >= 0 || b_index >= 0)
    {
        // 올라가는 수 + a의 한자리 숫자 + b의 한자리 숫자
        int added_num = count;
        if (a_index >= 0)
            added_num += a[a_index--] - '0';
        if (b_index >= 0)
            added_num += b[b_index--] - '0';

        // 올라가는 수 계산
        if (added_num < 10)
            count = 0;
        else
        {
            count = 1;
            added_num %= 10;
        }
        result.insert(result.begin(), added_num + '0');
    }

    // 올라가는 수가 존재하면 맨 앞에 추가
    if (count == 1)
        result.insert(result.begin(), '1');

    return result;
}

int main()
{
    // 입력
    string a, b;
    cin >> a >> b;

    // 계산 및 출력
    vector<char> result = add(a, b);
    for (int i = 0; i < result.size(); i++)
        cout << result[i];
}