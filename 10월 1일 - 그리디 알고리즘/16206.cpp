// 롤케이크 https://www.acmicpc.net/problem/16206

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1. 길이가 10인 롤케이크부터 자른다
    2. 길이가 10의 배수인 롤케이크부터 자른다
    3. 롤케이크를 길이가 10 미만이 될 때까지 자른다
    4. 만들어진 길이가 10인 롤케이크 개수를 구한다
*/

bool cmp(const int a, const int b)
{
    // 10의 배수를 먼저 나열
    // 둘다 10의 배수인 경우, 그 중 작은 쪽을 먼저 나열
    if (a % 10 == 0 && b % 10 == 0)
        return a < b;
    return (a % 10 == 0);
}

int calcMaxNumOfCake(vector<int> &cakes, int m)
{
    int num_of_cake = 0;

    for (int i = 0; i < cakes.size(); i++)
    {
        // 롤케이크를 길이가 10 이하가 될 때까지 자름
        while (cakes[i] > 10)
        {
            cakes[i] -= 10;
            num_of_cake++;

            // 자를 수 있는 최대 횟수를 다 사용하면 결과 리턴
            if (--m == 0)
                // 마지막으로 잘랐을 때 롤케이크가 10:10으로 나뉘면 결과에 1추가
                return (cakes[i] == 10) ? num_of_cake + 1 : num_of_cake;
        }
        // 롤케이크 길이가 10이면 자르는 횟수 차감 없이 개수만 증가
        if (cakes[i] == 10)
            num_of_cake++;
    }
    return num_of_cake;
}

int main()
{
    int n;             // 롤케이크 개수
    int m;             // 자를 수 있는 최대 횟수
    vector<int> cakes; // 롤케이크 길이

    // 입력
    cin >> n >> m;
    cakes.assign(n, 0);
    for (int i = 0; i < n; i++)
        cin >> cakes[i];

    // 연산 및 출력
    sort(cakes.begin(), cakes.end(), cmp);
    cout << calcMaxNumOfCake(cakes, m);
    return 0;
}