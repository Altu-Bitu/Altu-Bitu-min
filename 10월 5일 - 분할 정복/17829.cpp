// 222-풀링 https://www.acmicpc.net/problem/17829

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> matrix; // 행렬

// 222-풀링을 반복 적용해 1*1 크기의 행렬로 만드는 함수
int divide(int row, int col, int size)
{
    // Conquer : n의 크기가 1
    if (size == 1)               // 행렬의 크기가 1이면
        return matrix[row][col]; // 원소를 그대로 리턴함

    // Divide : 행렬 4등분 하기
    int next_size = size / 2;                           // 크기를 절반으로 나눔
    vector<int> sub_problem;                            // 나눠진 행렬의 222-풀링 결과를 저장
    for (int i = 0; i <= next_size; i += next_size)     // i만큼 행 증가
        for (int j = 0; j <= next_size; j += next_size) // j만큼 열 증가
            // 4등분 한 행렬에 각각 222-풀링을 적용한 결과를 저장함
            sub_problem.push_back(divide(row + i, col + j, next_size));

    // Combine : 두번째로 큰 수만 남기기
    sort(sub_problem.begin(), sub_problem.end(), greater<>()); // 원소들을 내림차순으로 정렬
    return sub_problem[1];                                     // 두번째로 큰 원소를 리턴함
}

/**
 * 1. 행렬 4등분 하기
 * 2. 행렬의 크기가 1이라면 원소 리턴
 * 3. 리턴된 원소 4개 모아서 두번째로 큰 수만 리턴
 */
int main()
{
    int n; // 행렬의 크기

    cin >> n;                         // 행렬의 크기 입력
    matrix.assign(n, vector<int>(n)); // n*n 크기의 행렬 선언
    for (int i = 0; i < n; i++)       // i: 행
        for (int j = 0; j < n; j++)   // j; 열
            cin >> matrix[i][j];      // 행렬의 i행 j열 원소 입력

    //연산 & 출력
    cout << divide(0, 0, n);
}