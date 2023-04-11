#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
unordered_map<char, int> um;

// 오늘 날짜를 담을 변수들
int year;
int month;
int day;

void getTerms(vector<string>& terms) {
    int SIZE = terms.size();
    for (int i = 0; i < SIZE; i++) {
        string now = terms[i];
        char tmp;
        int date;
        sscanf(now.c_str(), "%c %d", &tmp, &date);
        um[tmp] = date;
    }
}

bool isValid(int y, int m, int d, char t) {
    int du = um[t];

    int m_tmp = m + du;
    if (m_tmp % 12 == 0)
        y += (m_tmp / 12) - 1;
    else
        y += (m_tmp / 12);
    m_tmp %= 12;
    if (m_tmp == 0)
        m_tmp = 12;
    //
    if (y > year)
        return 1;
    if (y < year)
        return 0;
    if (m_tmp > month)
        return 1;
    if (m_tmp < month)
        return 0;
    return d > day;
}

void check(vector<string>& p, vector<int>& ans) {
    int SIZE = p.size();
    for (int i = 0; i < SIZE; i++) {
        int y, m, d;
        char t;
        string now = p[i];
        sscanf(now.c_str(), "%d.%d.%d %c", &y, &m, &d, &t);
        if (!isValid(y, m, d, t))
            ans.push_back(i + 1);
    }
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;

    // 오늘 날짜 파싱
    sscanf(today.c_str(), "%d.%d.%d", &year, &month, &day);
    // 약관과 기간 파싱
    getTerms(terms);
    int de = 1;
    // 개인정보 확인
    check(privacies, answer);
    return answer;
}
