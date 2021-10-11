// 222-풀링 https://www.acmicpc.net/problem/17829

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> a;

int findSecondMax(int row, int col)
{
    vector<int> v;
    for (int i = row; i < row + 2; i++)
        for (int j = col; j < col + 2; j++)
            v.push_back(a[i][j]);
    sort(v.begin(), v.end());
    return v[1];
}

int calcCNN(int row, int col, int size)
{
    vector<vector<int>> result;

    if (size <= 2)
        return findSecondMax(row, col);
    else
    {
        vector<int> v;
        size /= 2;
        v.push_back(calcCNN(row, col, size));
        v.push_back(calcCNN(row + size, col, size));
        v.push_back(calcCNN(row, col + size, size));
        v.push_back(calcCNN(row + size, col + size, size));
        sort(v.begin(), v.end());
        return v[1];
    }
}

int main()
{
    int n;

    // 입력
    cin >> n;
    a.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
            
    // 출력
    cout << calcCNN(0, 0, n);

    return 0;
}