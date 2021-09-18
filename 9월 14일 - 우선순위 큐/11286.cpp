// 절댓값 힙 https://www.acmicpc.net/problem/11286

#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

// 우선순위 비교 연산자 (절댓값이 작을수록 우선순위가 큼)
struct compare
{
    bool operator()(int a, int b)
    {
        if (abs(a) == abs(b))
            return a > b;
        return abs(a) > abs(b);
    }
};

int main()
{
    // 입출력 속도 향상
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, x;
    priority_queue<int, vector<int>, compare> absolute_heap;

    // 입력
    cin >> n;
    while (n--)
    {
        cin >> x;

        if (x == 0) // x가 0이면 pop()
        {
            if (absolute_heap.empty())
                cout << 0 << '\n';
            else
            {
                cout << absolute_heap.top() << '\n';
                absolute_heap.pop();
            }
        }
        else // x가 0이 아니면 push()
            absolute_heap.push(x);
    }
    return 0;
}