// 유레카 이론 https://www.acmicpc.net/problem/10448

#include <iostream>
#include <vector>

using namespace std;

const int MAX_K = 1000;

// num번째 삼각수 계산하는 함수
int calcTriangle(const int num)
{
    return num * (num + 1) / 2;
}

// 3개의 삼각수의 합으로 표현될 수 있는지 확인하는 함수
bool isEureka(const vector<int> &triangles, const int num)
{
    for (int i = 1; i < triangles.size(); i++)
        for (int j = 1; j < triangles.size(); j++)
            for (int k = 1; k < triangles.size(); k++)
                if (triangles[i] + triangles[j] + triangles[k] == num)
                    return true;
    return false;
}

/*
    n이 45일 때, 삼각수가 1035이므로 최대 K 값을 모두 커버함
    45개의 삼각수를 모두 검사하면 45^3 = 대략 90,000 번 검사
*/

int main()
{
    // 입출력 시간 단축
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    vector<int> triangles; // 삼각수

    // 삼각수 미리 계산(수가 MAX_K보다 작을 때까지만 계산)
    int n = 0;
    while (true)
    {
        int triangle = calcTriangle(n++);
        triangles.push_back(triangle);
        if (triangle > MAX_K)
            break;
    }

    // 입력
    cin >> t;
    while (t--)
    {
        int num;
        cin >> num;

        // 출력
        cout << isEureka(triangles, num) << '\n';
    }
    return 0;
}
