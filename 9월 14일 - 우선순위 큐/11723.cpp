// 집합 https://www.acmicpc.net/problem/11723

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // 입출력 속도 향상
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m, x;
    string cmd;
    vector<bool> s(20, false); // 숫자(1~20)가 집합에 존재하는지 표시함

    // 입력
    cin >> m;

    while (m--)
    {
        cin >> cmd;

        // 명령어가 all, empty인지 확인
        if (cmd == "empty")
        {
            s.clear();
            s.assign(20, false);
        }
        else if (cmd == "all")
        {
            s.clear();
            s.assign(20, true);
        }
        else
        {
            // all, empty가 아닐 때만 x가 입력됨
            cin >> x;
            x--;

            if (cmd == "add")
                s[x] = true;
            else if (cmd == "remove")
                s[x] = false;
            else if (cmd == "check")
            {
                if (s[x])
                    cout << 1 << '\n';
                else
                    cout << 0 << '\n';
            }
            else if (cmd == "toggle")
            {
                if (s[x])
                    s[x] = false;
                else
                    s[x] = true;
            }
        }
    }

    return 0;
}