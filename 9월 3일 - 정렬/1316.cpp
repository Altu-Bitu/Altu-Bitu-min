// 그룹 단어 체커 https://www.acmicpc.net/problem/1316

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isGroup(string word)
{
    vector<bool> alpha(26, false);
    alpha[word[0] - 'a'] = true;
    for (int i = 1; i < word.length(); i++)
    {
        char ch = word[i];
        if (ch != word[i - 1])
        {
            if (alpha[ch - 'a'])
                return false;
            alpha[ch - 'a'] = true;
        }
    }
    return true;
}

int main()
{
    int n, result = 0;
    string word;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> word;
        if (isGroup(word))
            result++;
    }

    cout << result << "\n";
    return 0;
}