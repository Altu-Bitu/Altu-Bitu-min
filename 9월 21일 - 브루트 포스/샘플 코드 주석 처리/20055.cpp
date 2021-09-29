// 컨베이어 벨트 위의 로봇 https://www.acmicpc.net/problem/20055

#include <iostream>
#include <vector>

using namespace std;

// 컨테이너 벨트 한 칸의 정보
struct info
{
    int power;  // 내구도
    bool is_on; // 로봇 존재 여부
};

vector<info> belt; // 컨테이너 벨트. 각 칸의 정보(내구도, 로봇 존재 여부)를 저장
int zero_power;    // 현재 내구도가 0인 칸의 개수

// 길이가 n인 컨테이너 벨트에서 현재 칸 이전(왼쪽) 칸의 인덱스를 구하는 함수
int minusPosition(int n, int pos)
{
    // 현재 인덱스 pos가 0이상이면
    if (--pos >= 0)
        return pos;   // 단순히 1감소한 값을 리턴
    return n * 2 - 1; // pos가 0이면 컨테이너 벨트의 마지막 칸 인덱스 리턴
}

// 로봇을 이동시키는 함수
void second(int n, int start, int end)
{
    int cur = end; // 현재 가리키는 칸의 인덱스. 내리는 위치(end) 쪽부터 검사함
    // 올리는 위치(start)까지 검사하면 종료
    while (cur != start)
    {
        // cur을 한 칸 왼쪽으로 이동
        cur = minusPosition(n, cur);
        int next = (cur + 1) % (n * 2); // 다음(오른쪽) 칸의 인덱스

        // 현재 칸에 로봇이 없고, 다음 칸에 로봇이 없고, 다음 칸의 내구도가 1 이상인 경우 로봇 이동
        if (belt[cur].is_on && !belt[next].is_on && belt[next].power)
        {
            // 현재 칸에는 로봇이 없게 됨
            belt[cur].is_on = false;
            // 다음 칸의 내구도가 1 감소됨
            belt[next].power--;
            // 다음 칸이 내리는 위치가 아닌 경우에만
            if (next != end)
                belt[next].is_on = true; // 다음 칸에 로봇이 존재하게 됨
            // 다음 칸의 내구도가 0이면
            if (belt[next].power == 0)
                zero_power++; // 내구도가 0인 칸 개수 증가
        }
    }
}

// 로봇을 올리는 위치에 올리는 함수
void third(int start)
{
    // 올리는 위치의 내구도가 1 이상이면
    if (belt[start].power)
    {
        // 올리는 위치에 로봇을 올림
        belt[start].is_on = true;
        // 올리는 위치의 내구도 1 감소
        belt[start].power--;
        // 올리는 위치의 내구도가 0이면
        if (belt[start].power == 0)
            zero_power++; // 내구도가 0인 칸 개수 증가
    }
}

/**
 * [컨베이어 벨트 위의 로봇 문제]
 * 1. 벨트가 각 칸 위의 로봇과 함께 한 칸 회전
 * 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트 회전 방향으로 한 칸 이동할 수 있다면 이동 (이동가능: 이동하려는 칸에 로봇이 없고, 그 칸의 내구도가 1 이상이어야 함)
 * 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇 올림
 * 4. 내구도가 0인 칸의 개수가 k개 이상이라면 과정 종료. 그렇지 않다면 1로 돌아감
 * -> 1 ~ 3까지가 1단계
 *
 * [문제 풀이]
 * 벨트의 로봇을 옮기는 게 아니라, 올리는 위치와 내리는 위치의 인덱스 값을 바꿔서 접근
 * 필요한 컨테이너: 내구도와 로봇의 존재여부를 체크할 배열
 * 1번: 벨트의 방향이 오른쪽이므로, 벨트 한 칸 회전 시 올리는 위치와 내리는 위치의 인덱스 값은 하나 감소
 * 2번: 가장 먼저 올라간 로봇부터 고려해야 하므로 (내리는 위치 - 1)부터 (올리는 위치)까지 검사 -> 로봇 옮기는 거 가능하면 존재여부 체크하고 내구도 감소
 * 3번: 올리는 위치 칸 내구도 0이 아니라면 해당 칸 로봇 존재 여부 체크 + 내구도 감소
 */

int main()
{
    // 입출력 시간 단축
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // 벨트 길이
    int k; // 내구도가 0인 칸의 최종 개수

    // 입력
    cin >> n >> k;
    belt.assign(n * 2, {0, false}); // 컨테이너 벨트 초기화 (길이는 2n)
    for (int i = 0; i < n * 2; i++) // 컨테이너 벨트의 길이 만큼 반복
        cin >> belt[i].power;       // 각 칸의 내구도 입력

    // 연산
    int start = 0;   // 올리는 위치
    int end = n - 1; // 내리는 위치
    int step = 0;    // 단계 수

    // 무한 루프
    while (true)
    {
        // 벨트 회전
        start = minusPosition(n, start); // 올리는 위치를 한 칸 왼쪽으로 이동
        end = minusPosition(n, end);     // 내리는 위치를 한 칸 왼쪽으로 이동

        // 벨트 회전 후, 내리는 위치에 로봇이 존재한다면
        if (belt[end].is_on)
            belt[end].is_on = false; // 로봇 내림

        // 로봇 이동시키기
        second(n, start, end);

        // 올리는 위치에 로봇 올리기
        third(start);

        // 단계 증가
        step++;

        // 현재 내구도가 0인 칸 개수가 최종 개수 이상이 되면
        if (zero_power >= k)
            break; // 무한 루프 중지
    }

    //출력
    cout << step << '\n';

    return 0;
}