// 나무 재테크 https://www.acmicpc.net/problem/16235

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
typedef tuple<int, int, int> tp;

// 봄: 나무가 양분을 먹어 나이가 증가하거나 양분을 먹지 못해 죽음
queue<tp> spring(matrix &land, deque<tp> &tree, queue<pair<int, int>> &breeding_tree)
{
    queue<tp> dead_tree;    // 죽은 나무 목록
    int size = tree.size(); // 현재 심겨진 나무의 총 개수
    // 모든 나무 검사
    while (size--)
    {
        int age = get<0>(tree.front()); // 나이
        int row = get<1>(tree.front()); // 행
        int col = get<2>(tree.front()); // 열
        tree.pop_front();               // 맨 앞 나무를 목록에서 제거

        // 자신의 나이만큼 양분을 먹을 수 없다면
        if (land[row][col] < age)
        {
            dead_tree.push({age, row, col}); // 죽은 나무 목록에 추가
            continue;                        // 다음 나무 검사
        }
        land[row][col] -= age;                // 나무가 자신의 나이 만큼 땅의 양분을 섭취
        tree.emplace_back(age + 1, row, col); // 나무의 나이가 증가하고, 목록의 맨 뒤로 감
        if ((age + 1) % 5 == 0)               // 나무의 나이가 5의 배수라면
            breeding_tree.push({row, col});   // 번식이 가능한 나무 목록에 추가
    }
    return dead_tree; // 죽은 나무 목록 리턴
}

// 여름: 봄에 죽은 나무들이 양분이 됨
void summer(queue<tp> &dead_tree, matrix &land)
{
    // 죽은 모든 나무들에 대해 반복
    while (!dead_tree.empty())
    {
        int age = get<0>(dead_tree.front()); // 죽은 나무의 나이
        int row = get<1>(dead_tree.front()); // 죽은 나무의 행 위치
        int col = get<2>(dead_tree.front()); // 죽은 나무의 열 위치
        dead_tree.pop();                     // 맨 앞의 원소(죽은 나무) 제거
        land[row][col] += (age / 2);         // 나이의 절반 만큼의 양분이 땅에 더해짐
    }
}

// 가을: 나이가 5의 배수인 나무들이 번식하여 인접한 땅에 새 나무들이 생김
void fall(int n, deque<tp> &tree, queue<pair<int, int>> &breeding_tree)
{
    int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; // 인접 8칸을 가리키기 위한 행 증가량
    int dc[8] = {0, 0, -1, 1, -1, 1, -1, 1}; // 인접 8칸을 가리키기 위한 열 증가량

    // 번식이 가능한 모든 나무들에 대해 반복
    while (!breeding_tree.empty())
    {
        int row = breeding_tree.front().first;  // 번식할 나무의 행
        int col = breeding_tree.front().second; // 번식할 나무의 열
        breeding_tree.pop();                    // 맨 앞의 원소(번식할 나무) 제거

        // 인접한 8칸에 새 나무가 생김
        for (int j = 0; j < 8; j++)
        {
            int nr = row + dr[j]; // 새 나무의 행 인덱스
            int nc = col + dc[j]; // 새 나무의 열 인덱스

            // 새 나무의 위치가 땅의 범위를 벗어난다면
            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue; // 다음 칸으로 넘어감

            tree.push_front({1, nr, nc}); // 새로 생긴 나무 추가
        }
    }
}

// 겨울: 로봇이 양분을 추가함
void winter(int n, matrix &a, matrix &land)
{
    // 모든 칸에 대해 반복
    for (int i = 0; i < n; i++)     // i: 행 인덱스
        for (int j = 0; j < n; j++) // j: 열 인덱스
            land[i][j] += a[i][j];  // 땅(i, j)에 a[i][j] 만큼 양분을 추가
}

/**
 * [문제 설명] - 단순 구현 문제
 * 봄: 하나의 칸마다 나이가 어린 나무부터 자신의 나이만큼 양분을 먹고, 나이가 1 증가함
 *    각 칸에 양분이 부족해 자신의 나이만큼 양분을 못 먹는 나무는 즉시 죽음
 * 여름: 봄에 죽은 나무가 양분으로 변함. 죽은 나무마다 나이를 2로 나눈 값이 양분으로 추가 (소수점 버림)
 * 가을: 나이가 5의 배수인 나무가 번식. 인접한 8개 칸에 나이가 1인 나무가 생김
 * 겨울: 로봇(S2D2)이 땅을 돌아다니면서 A[r][c]만큼 각 칸에 양분 추가
 *
 * K년이 지난 후 상도의 땅에 살아있는 나무의 개수
 *
 * [문제 풀이]
 * a: 로봇(S2D2)가 겨울에 주는 양분의 양
 * land: 땅의 양분
 * breeding_tree: 나이가 5의 배수인 트리 (번식할 트리)
 * tree: 땅에 심은 나무 나이, 행, 열 정보
 * -> deque 컨테이너를 활용해 번식한 나무를 앞에 넣어주면 입력 후에만 정렬해서 사용 가능
 *
 * 문제의 설명대로 계절별 연산을 진행
 */

int main()
{
    int n; // 땅의 한 변의 크기
    int m; // 첫 해에 심은 나무의 개수
    int k; // 계산할 햇수
    int x; // 나무의 x 좌표
    int y; // 나무의 y 좌표
    int z; // 나무의 나이

    // 입력
    cin >> n >> m >> k;
    matrix a(n, vector<int>(n, 0));      // 겨울에 추가될 양분의 양
    matrix land(n, vector<int>(n, 5));   // 처음 양분 모든 칸에 5
    queue<pair<int, int>> breeding_tree; // 번식할 트리
    deque<tp> tree;                      // 땅에 심은 나무들의 정보 <나이, 행, 열>

    // 겨울에 땅에 추가될 양분의 양 입력
    for (int i = 0; i < n; i++)     // i: 행 인덱스
        for (int j = 0; j < n; j++) // j: 열 인덱스
            cin >> a[i][j];         // 땅(i, j)에 추가될 양분

    // 첫 해에 심은 나무들의 정보 입력
    while (m--)
    {
        cin >> x >> y >> z;                 // 나무의 행, 열, 나이
        tree.emplace_back(z, x - 1, y - 1); // (0, 0)부터 시작하도록 구현하기위해 1을 빼준 인덱스에 접근
    }

    // 연산
    sort(tree.begin(), tree.end()); // 어린 나이 순으로 정렬
    // 입력으로 주어진 햇수 만큼 반복
    while (k--)
    {
        // 봄이 지나고 죽은 나무
        queue<tp> dead_tree = spring(land, tree, breeding_tree); // 봄
        summer(dead_tree, land);                                 // 여름
        fall(n, tree, breeding_tree);                            // 가을
        winter(n, a, land);                                      // 겨울
    }

    //출력
    cout << tree.size();
}