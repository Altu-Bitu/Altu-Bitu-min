// 그룹 단어 체커 https://www.acmicpc.net/problem/1316

#include <iostream>
#include <string>
#include <array>

using namespace std;

int result = 0;
array<int, 26> alpha = {0};

void isGroup(string word)
{
    alpha.fill(0);
    alpha[word[0] - 97]++;
    for (int i = 1; i < word.length(); i++)
    {
        char ch = word[i];
        if (ch != word[i - 1])
        {
            if (alpha[ch - 97] > 0)
                return;
            alpha[ch - 97]++;
        }
    }
    result++;
}

int main()
{
    int n;
    string word;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> word;
        isGroup(word);
    }

    cout << result << endl;
    return 0;
}