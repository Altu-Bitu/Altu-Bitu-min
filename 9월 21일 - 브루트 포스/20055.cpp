// 컨베이어 벨트 위의 로봇 https://www.acmicpc.net/problem/20055

#include <iostream>
#include <vector>

using namespace std;

// 컨테이너 벨트의 칸
struct Belt
{
    int dur;    // 칸의 현재 내구도
    bool robot; // 칸 위에 로봇이 있는지 판단
};

// 컨테이너 벨트에서 현재 칸 이전(왼쪽) 칸의 인덱스를 구하는 함수
int nextIndexOfBelt(int n, int current_index)
{
    return (--current_index < 0) ? (2 * n - 1) : current_index;
}

// 로봇을 이동시키는 함수
// Return: 현재 단계에서 생겨난 내구도 0인 칸의 개수
int moveRobots(vector<Belt> &container, const int n, const int in_pointer, const int out_pointer)
{
    int number_of_zero = 0; // 내구도 0인 칸의 개수
    int index = out_pointer;

    // 내리는 위치의 로봇 내림
    container[out_pointer].robot = false;

    // 로봇 이동 (뒤에서부터)
    while (index != in_pointer)
    {
        int next_index = nextIndexOfBelt(n, index);

        // 왼쪽 칸에 로봇이 있고, 현재 칸의 내구도가 0 이상이면 로봇 이동
        if (container[next_index].robot && !container[index].robot && container[index].dur > 0)
        {
            container[next_index].robot = false;
            if (index != out_pointer)
                container[index].robot = true;
            container[index].dur--;

            if (container[index].dur == 0)
                number_of_zero++;
        }

        index = next_index;
    }

    // 올리는 위치에 내구도가 0 이상이면 로봇을 올림
    if (container[in_pointer].dur > 0)
    {
        container[in_pointer].dur--;
        container[in_pointer].robot = true;

        if (container[in_pointer].dur == 0)
            number_of_zero++;
    }

    return number_of_zero;
}

int main()
{
    int n;                  // 벨트 길이
    int k;                  // 종료되었을 때 내구도 0인 칸 개수
    vector<Belt> container; // 컨테이너 벨트
    int current_zero = 0;   // 현재 내구도 0인 칸 개수
    int ans = 0;            // 현재 진행 중인 단계

    // 입력
    cin >> n >> k;
    container.assign(2 * n, {0, false});
    for (int i = 0; i < 2 * n; i++)
        cin >> container[i].dur;

    int in_pointer = 0;      // 올리는 위치를 가리킴
    int out_pointer = n - 1; // 내리는 위치를 가리킴

    // 컨테이너 벨트 회전
    while (current_zero < k)
    {
        // 한 단계 증가
        ans++;

        // 벨트 회전
        in_pointer = nextIndexOfBelt(n, in_pointer);
        out_pointer = nextIndexOfBelt(n, out_pointer);

        // 로봇 이동 및 추가
        current_zero += moveRobots(container, n, in_pointer, out_pointer);
    }

    // 출력
    cout << ans;
    return 0;
}