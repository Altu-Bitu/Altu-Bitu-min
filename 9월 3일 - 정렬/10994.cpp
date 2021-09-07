// 별 찍기 - 19 https://www.acmicpc.net/problem/10994

#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> stars;

void drawStars(int rStart, int cStart, int rEnd, int cEnd)
{
    if (rStart > rEnd)
        return;
    for (int r = rStart; r < rEnd; r++)
    {
        stars[r][cStart] = '*';
        stars[r][cEnd - 1] = '*';
    }
    for (int c = cStart; c < cEnd; c++)
    {
        stars[rStart][c] = '*';
        stars[rEnd - 1][c] = '*';
    }
    drawStars(rStart + 2, cStart + 2, rEnd - 2, cEnd - 2);
}

int main()
{
    int n;
    cin >> n;
    n = 4 * n - 3;
    for (int i = 0; i < n; i++)
        stars.assign(n, vector<char>(n, ' '));

    drawStars(0, 0, n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << stars[i][j];
        cout << "\n";
    }
}