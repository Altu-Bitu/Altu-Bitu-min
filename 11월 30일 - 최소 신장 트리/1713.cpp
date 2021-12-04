// 후보 추천하기 https://www.acmicpc.net/problem/1713

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_STUDENT_NUM = 100;

// 사진틀에서 사진을 삭제하는 함수
void removePicture(int n, vector<int> &pictures, vector<int> &recommend)
{
    vector<int>::iterator rm = pictures.begin(); // 삭제하려는 사진
    for (auto it = pictures.begin() + 1; it != pictures.end() - 1; it++)
        // 추천 받은 횟수가 더 낮은 학생의 사진으로 갱신
        if (recommend[*rm] > recommend[*it])
            rm = it;

    recommend[*rm] = 0; // 학생의 추천수 초기화
    pictures.erase(rm); // 사진 삭제
}

int main()
{
    int n; // 사진틀 개수
    int m; // 총 추천 횟수

    // 입력
    cin >> n >> m;
    vector<int> pictures(0);                       // 사진이 게시된 학생의 번호를 저장하는 배열
    vector<int> recommend(MAX_STUDENT_NUM + 1, 0); // 각 학생의 추천 받은 횟수를 저장하는 배열
    while (m--)
    {
        int student; // 새로 추천 받은 학생
        cin >> student;
        recommend[student]++; // 추천 수 증가

        vector<int>::iterator it = find(pictures.begin(), pictures.end(), student);
        // 추천 받은 학생의 사진이 현재 게시되지 않았다면
        if (it == pictures.end())
            pictures.push_back(student); // 사진 게시 (맨 뒤에 삽입)

        // 사진틀의 개수가 부족하면
        if (pictures.size() > n)
            removePicture(n, pictures, recommend); // 사진 삭제
    }

    // 최종 후보들의 번호를 오름차순으로 정렬
    sort(pictures.begin(), pictures.end());

    // 출력
    for (int picture : pictures)
        cout << picture << ' ';
    return 0;
}