// 비슷한 단어 https://www.acmicpc.net/problem/2607

/*
    단어1에서 한 문자를 더하거나 빼면 같은 구성이 되는 경우, 
    단어1의 철자가 단어2보다 1개 많거나, 1개 적다. 
    단어1에서 하나의 문자를 다른 문자로 바꾸어 같은 구성이 되는 경우, 
    단어1의 철자가 단어2보다 1개 많으면서, 단어2의 철자가 단어1보다 1개 많다.

    1. 비교할 두 단어의 구성을 각각 파악한다.
    2. 두 단어의 서로 다른 부분을 체크한다.
    3. 서로 다른 부분이 1 이하면, 두 단어는 비슷한 구성이다. (한 문자를 더하거나 빼는 경우)
    4. 서로 다른 부분이 2이면서 두 단어의 길이가 같으면, 비슷한 구성이다. (한 문자를 교체한 경우)
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int SIZE_OF_ALPHA = 26; // 알파벳 개수

// 두 단어가 비슷한 구성인지 판별하는 함수
bool isSimilar(vector<int> &first, vector<int> &second, int len1, int len2)
{
    // 두 단어의 길이가 2 이상 차이나면, 두 단어는 비슷하지 않으므로 false 리턴
    if (abs(len1 - len2) > 1)
        return false;

    int cnt = 0; // 두 단어가 서로 다른 부분을 카운트
    for (int i = 0; i < SIZE_OF_ALPHA; i++)
        cnt += abs(first[i] - second[i]);   // 서로 다른 철자의 수만큼 카운트 증가

    // 조건 1인 경우, first에서 한 문자만 더하거나 빼면 second를 만들 수 있으므로 true 리턴
    // 조건 2인 경우, first에서 한 문자만 바꾸면 second를 만들 수 있으므로 true 리턴
    if (cnt < 2 || (cnt == 2 && len1 == len2))
        return true;
    // 위 조건에 만족하지 않으면 false 리턴
    return false;
}

int main()
{
    int n;                               // 단어의 개수
    string first_word;                   // 첫 번째 단어
    vector<int> first(SIZE_OF_ALPHA, 0); // 첫 번째 단어를 구성하는 알파벳
    int ans = 0;                         // 비슷한 단어의 개수

    // 첫 번째 단어 구성 파악
    cin >> n >> first_word;
    for (int i = 0; i < first_word.length(); i++)
        first[first_word[i] - 'A']++;

    while (--n)
    {
        string word;
        cin >> word;

        vector<int> second(SIZE_OF_ALPHA, 0); // 두 번째 단어를 구성하는 알파벳
        // 두 번째 단어 구성 파악
        for (int i = 0; i < word.length(); i++)
            second[word[i] - 'A']++;

        // 첫 번째 단어와 비슷한지 체크
        if (isSimilar(first, second, first_word.length(), word.length()))
            ans++;
    }

    // 출력
    cout << ans;
    return 0;
}