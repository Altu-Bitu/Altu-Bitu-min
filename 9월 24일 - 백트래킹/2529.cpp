// 부등호 https://www.acmicpc.net/problem/2529

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<bool> check(10, false); // 숫자 선택 여부
vector<int> choose;            // 선택된 숫자들
string max_num = "0123456789"; // 최댓값
string min_num = "9876543210"; // 최솟값

// 숫자들을 선택하고 최솟값과 최댓값을 갱신하는 함수
// cnt: cnt번째로 선택될 숫자를 검사함
void findMinMax(vector<char> brackets, int cnt)
{
    // 괄호의 개수 + 1 개 만큼 숫자를 선택했으면 최댓값, 최솟값 갱신 후 함수 종료
    if (cnt > brackets.size())
    {
        string num = "";
        for (int i = 0; i < choose.size(); i++)
            num += to_string(choose[i]);
        max_num = max(max_num, num);
        min_num = min(min_num, num);
        return;
    }
    // 0부터 9까지 숫자가 선택될 수 있는지 검사
    for (int i = 0; i < 10; i++)
    {
        // i가 아직 선택되지 않은 숫자이면
        if (!check[i])
        {
            // i 선택
            check[i] = true;
            choose.push_back(i);

            // i가 첫 숫자면 바로 다음 숫자 검사로 넘어감
            if (cnt == 0)
                findMinMax(brackets, cnt + 1);
            // 이전 숫자와 부등호에 따른 대소관계가 맞을 경우 다음 숫자 검사로 넘어감
            else if (brackets[cnt - 1] == '<' && choose[choose.size() - 2] < i)
                findMinMax(brackets, cnt + 1);
            else if (brackets[cnt - 1] == '>' && choose[choose.size() - 2] > i)
                findMinMax(brackets, cnt + 1);
            check[i] = false;
            choose.pop_back();
        }
    }
}

int main()
{
    int k;

    // 입력
    cin >> k;
    vector<char> brackets(k, '<');
    for (int i = 0; i < k; i++)
        cin >> brackets[i];

    // 최솟값, 최댓값 초기화
    min_num = min_num.substr(0, k + 1);
    max_num = max_num.substr(0, k + 1);

    // 연산 및 출력
    findMinMax(brackets, 0);
    cout << max_num << '\n'
         << min_num;

    return 0;
}