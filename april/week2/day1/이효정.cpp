#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <cstdio>

using namespace std;
unordered_map<char, int> um;

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    int year;
    int month;
    int day;
    sscanf(today.c_str(), "%d.%d.%d", &year, &month, &day);
    for (string s: terms) {
        char ch;
        int temp;
        sscanf(s.c_str(), "%c %d", &ch, &temp);
        um[ch] = temp;
    }
    int idx = 0;
    for (string s: privacies) {
        int y, m, d;
        char ch;
        sscanf(s.c_str(), "%d.%d.%d %c", &y, &m, &d, &ch);
        m += um[ch];
        d--;
        if (d == 0) {
            d = 28;
            m--;
        }
        while (m > 12) {
            m -= 12;
            y += 1;

        }
        //printf("%d %d %d \n", y, m, d);
        ++idx;
        if (y < year) {
            answer.push_back(idx);
            continue;
        }
        else if (y > year) {
            continue;
        }
        if (m < month) {
            answer.push_back(idx);
            continue;
        } 
        else if (m > month) {
            continue;
        }
        if (d < day) {
            answer.push_back(idx);
            continue;
        }
    }

    //cout << year << month << day;
    return answer;
}
