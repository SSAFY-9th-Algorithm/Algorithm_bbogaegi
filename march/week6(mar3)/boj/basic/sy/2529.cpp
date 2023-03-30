#include <iostream>
#include <string>
using namespace std;
using ll = long long;

int N;
char arr[15];
int used[15];
ll MAX = -9999999999, MIN = 9999999999;
string mx, mi;

bool check(int a, int b, char s) {
    if (s == '<') return a < b;
    else return a > b;
}

void dfs(int now, string path) {
    int de = 1;
    // 기저조건 -> N + 1개 선택
    if (now == N + 1) {
        ll tmp = stoll(path);
        if (tmp > MAX) {
            MAX = tmp;
            mx = path;
        }
        if (tmp < MIN) {
            MIN = tmp;
            mi = path;
        }
        return;
    }
    // 재귀 구성 -> 0~9까지 중 N+1개 선택
    for (int i = 0; i <= 9; i++) {
        if (used[i])
            continue;
        int tmp, flag = 1;
        if (now > 0) {
            tmp = path[now - 1] - '0';
            char s = arr[now - 1];
            flag = check(tmp, i, s);
        }
        if (!flag)
            continue;
        used[i] = 1;
        path += to_string(i);
        dfs(now + 1, path);
        path.pop_back();
        used[i] = 0;
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    dfs(0, "");

    cout << mx << '\n' << mi << '\n';

    return 0;
}
