// Java vs C++ https://www.acmicpc.net/problem/3613

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const string ERROR_MSG = "Error!";

// java 형식 변수명을 c++ 형식으로 바꾸는 함수
string javaToCPP(string var)
{
    string result;

    // 첫 글자가 대문자면 에러 출력
    if (isupper(var[0]))
        return ERROR_MSG;

    for (int i = 0; i < var.length(); i++)
    {
        // 대문자는 앞에 '_' 삽입, 소문자로 변경 후 결과에 합침
        if (isupper(var[i]))
        {
            result += '_';
            result += tolower(var[i]);
        }
        else
            result += var[i]; // 다른 문자들은 그대로 결과에 합침
    }
    return result;
}

// c++ 형식 변수명을 java 형식으로 바꾸는 함수
string CPPToJava(string var)
{
    string result;

    // 첫 글자 혹은 마지막 글자가 '_'면 에러 출력
    if (var[0] == '_' || var[var.length() - 1] == '_')
        return ERROR_MSG;

    for (int i = 0; i < var.length(); i++)
    {
        // 대문자가 존재하면 에러 출력
        if (isupper(var[i]))
            return ERROR_MSG;

        // '_'의 다음 문자는 대문자로 변경 후 결과에 합침
        if (var[i] == '_')
        {
            // '_'가 연달아 나오거나 다음 문자가 대문자면 에러 출력
            if (!isalpha(var[++i]) || isupper(var[i]))
                return ERROR_MSG;

            result += toupper(var[i]);
        }
        else
            result += var[i]; // 다른 문자들은 그대로 결과에 합침
    }
    return result;
}

// 변수명의 형식을 전환하는 함수 (c++ ↔ java)
string switchVariableName(string var)
{
    string result;

    // var에 '_'가 있다면
    if (var.find('_') != string::npos)
        result = CPPToJava(var); // c++ -> java
    else
        result = javaToCPP(var); // java -> c++

    return result;
}

int main()
{
    string var;
    cin >> var;                      // 입력
    cout << switchVariableName(var); // 출력
}