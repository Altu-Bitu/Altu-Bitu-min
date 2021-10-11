// 행렬 https://www.acmicpc.net/problem/1080

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    1. a[i][j] != b[i][j]
        => a[i][j]부터 3*3 변환 연산
*/

// mat 행렬에 변환 연산을 수행하는 함수
void convertMatrix(vector<string> &mat, int row, int col)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            mat[row + i][col + j] = (mat[row + i][col + j] == '0') ? '1' : '0';
}

// 두 행렬이 같은지 판단하는 함수
bool compareMatrix(vector<string> &a, vector<string> &b)
{
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] != b[i][j])
                return false;
    return true;
}

// 최소 변환 연산 수행 횟수를 계산하는 함수
int calcNumOfConvert(vector<string> &a, vector<string> &b)
{
    int num_of_convert = 0;
    int n = a.size(), m = a[0].size();

    // a 행렬에서 b 행렬과 다른 원소가 있다면 변환 연산 수행
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = 0; j < m - 2; j++)
        {
            if (a[i][j] != b[i][j])
            {
                convertMatrix(a, i, j);
                num_of_convert++;
            }
        }
    }
    // a와 b가 같으면 변환 횟수를, 다르면 -1을 리턴
    return compareMatrix(a, b) ? num_of_convert : -1;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;               // 행
    int m;               // 열
    vector<string> a, b; // 행렬 A, B

    // 입력
    cin >> n >> m;
    a.assign(n, "");
    b.assign(n, "");
    cin.ignore(1, '\n');
    for (int i = 0; i < n; i++)
        getline(cin, a[i]);
    for (int i = 0; i < n; i++)
        getline(cin, b[i]);

    // 연산 및 출력
    cout << calcNumOfConvert(a, b);
    return 0;
}