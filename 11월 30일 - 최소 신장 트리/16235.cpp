// 나무 재테크 https://www.acmicpc.net/problem/16235

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<vector<int>>> ground; // ground[i][j]: 땅(i, j)에 존재하는 나무들의 나이를 저장하는 벡터
vector<vector<int>> nutrient;       // nutrient[i][j]: 땅(i, j)의 영양 상태
vector<vector<int>> a;              // a[i][j]: 겨울에 땅(i, j)에 더해지는 영양

// 해당 좌표가 땅의 범위 내에 있는지 판별하는 함수
bool isValid(int n, int r, int c)
{
    return r >= 0 && r < n && c >= 0 && c < n;
}

// 새로 생성된 나무를 추가하는 함수 (여름)
void reproduce(int n, vector<pair<int, int>> &parent_trees)
{
    // 인접한 8칸의 좌표
    vector<int> dr = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dc = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (auto parent : parent_trees)
    {
        int r = parent.first;
        int c = parent.second;

        for (int i = 0; i < 8; i++)
        {
            int new_r = r + dr[i];
            int new_c = c + dc[i];

            // 새로 나이가 1인 나무를 심음
            if (isValid(n, new_r, new_c))
                ground[new_r][new_c].push_back(1);
        }
    }
}

// 영양을 먹거나 더하는 함수 (봄, 가을, 겨울)
void takeAndAddNutrient(int n, vector<pair<int, int>> &parent_trees)
{
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            // 해당 칸에 나무가 없으면 패스
            if (ground[r][c].empty())
                continue;

            int dead_trees = 0; // 봄에 죽은 나무들로 인해 더해지는 영양

            // 나무들을 나이를 기준으로 오름차순 정렬
            sort(ground[r][c].begin(), ground[r][c].end());
            for (auto tree = ground[r][c].begin(); tree != ground[r][c].end(); tree++)
            {
                // 칸의 영양보다 나무가 먹어야 할 영양이 많다면
                if (nutrient[r][c] < *tree)
                {
                    // 나무가 죽고 영양분으로 변함
                    dead_trees += (*tree / 2);
                    ground[r][c].erase(tree--);
                    continue;
                }

                // 나무가 영양을 먹고, 나이가 증가함
                nutrient[r][c] -= *tree;
                *tree = *tree + 1;
                // 나이가 5의 배수라면 번식이 가능한 나무 리스트에 추가
                if (*tree % 5 == 0)
                    parent_trees.push_back({r, c});
            }

            // 여름과 겨울에 영양이 더해짐
            nutrient[r][c] += dead_trees + a[r][c];
        }
    }
}

// 살아있는 나무의 개수를 세는 함수
int countAliveTree(int n)
{
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += ground[i][j].size();
    return ans;
}

int main()
{
    int n, m, k, x, y, z;

    // 입력
    cin >> n >> m >> k;
    ground.assign(n, vector<vector<int>>(n));
    nutrient.assign(n, vector<int>(n, 5));
    a.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    while (m--)
    {
        cin >> x >> y >> z;
        ground[--x][--y].push_back(z);
    }

    // 연산
    while (k--)
    {
        vector<pair<int, int>> parent_trees;
        takeAndAddNutrient(n, parent_trees);
        reproduce(n, parent_trees);
    }

    // 출력
    cout << countAliveTree(n);
    return 0;
}