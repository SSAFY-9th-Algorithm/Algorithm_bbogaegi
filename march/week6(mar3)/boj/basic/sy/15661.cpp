#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int used[21];
int MAP[21][21];
int ans = 21e8;
int M;

void dfs(int now, int cnt) {
    if (cnt == M) {
        int A = 0, B = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (used[i] && used[j])
                    A += MAP[i][j];
                if (!used[i] && !used[j])
                    B += MAP[i][j];
            }
        }
        int tmp = abs(A - B);
        ans = min(ans, tmp);
        return;
    }
    if (now >= N || ans == 0)
        return;

    used[now] = 1;
    dfs(now + 1, cnt + 1);
    used[now] = 0;

    dfs(now + 1, cnt);
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> MAP[i][j];
    for (int i = 1; i <= N / 2; i++) {
        M = i;
        dfs(0, 0);
        if (ans == 0)
            break;
    }
    cout << ans;
    return 0;
}
