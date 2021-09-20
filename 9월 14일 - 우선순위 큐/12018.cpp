// Yonsei TOTO https://www.acmicpc.net/problem/12018

#include <iostream>
#include <queue>

using namespace std;

int calcNumOfSubject(priority_queue<int, vector<int>, greater<int>> mileage_list, int max_mileage)
{
    int result = 0;
    while (true)
    {
        max_mileage -= mileage_list.top();

        // 주어진 마일리지를 모두 쓰거나 마일리지 투자가 끝나면 종료
        if (max_mileage < 0 || mileage_list.empty())
            return result;

        mileage_list.pop();
        result++;
    }
}

int main()
{
    int n;                                                     // 과목 수
    int m;                                                     // 주어진 마일리지
    int p;                                                     // 신청 인원 수
    int l;                                                     // 수강 인원 수
    priority_queue<int, vector<int>, greater<int>> my_mileage; // 투자할 마일리지 목록

    // 입력
    cin >> n >> m;

    while (n--)
    {
        priority_queue<int, vector<int>, greater<int>> other_mileage; // 다른 사람들이 투자한 마일리지 목록
        int mileage;

        cin >> p >> l;

        // (신청 인원 < 수강 인원) 이면 가장 적은 마일리지 투자
        if (p < l)
            other_mileage.push(1);

        // 다른 사람들이 투자한 마일리지 목록 입력
        while (p--)
        {
            cin >> mileage;

            // other_mileage.top() : 투자된 모든 마일리지 중 l번째로 큰 마일리지
            // 목록의 크기가 수강 인원 수보다 작으면 마일리지를 목록에 추가
            if (other_mileage.size() < l)
                other_mileage.push(mileage);
            else if (mileage > other_mileage.top()) // 목록의 가장 작은 마일리지보다 새로 입력할 마일리지가 크다면
            {
                // 가장 작은 마일리지를 지우고 새로운 마일리지를 목록에 추가
                other_mileage.pop();
                other_mileage.push(mileage);
            }
        }

        // 다른 사람들이 투자한 마일리지 중 l번째로 큰 마일리지만큼 투자
        my_mileage.push(other_mileage.top());
    }

    // 출력
    cout << calcNumOfSubject(my_mileage, m);
    return 0;
}