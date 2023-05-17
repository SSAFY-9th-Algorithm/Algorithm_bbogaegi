#define _CRT_SECURE_NO_WARNINGS
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
* 90도 회전을 가지고있으면
* 시간 복잡도 -> 4*10*9*8*1024
#1. 조합을 뽑는다
#2. 배치해보고
#3. 가장 크면 갱신
*/

struct Info {
    int efi;
    char color;
};

int N;
Info MAP[5][5];
Info COPY[5][5];
int efficacy[10][4][4][4]; // [n][y][x][dir]
char element[10][4][4][4]; // [n][y][x][dir]
int visited[10];
int ans;

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                cin >> efficacy[i][y][x][0];
            }
        }

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                cin >> element[i][y][x][0];
            }
        }
    }
}

void rotate(int t, int d) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            efficacy[t][i][j][d] = efficacy[t][3 - j][i][d - 1];
            element[t][i][j][d] = element[t][3 - j][i][d - 1];
        }
    }
}

int getScore(Info mat[5][5]) {
    int R = 0, G = 0, B = 0, Y = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            char now = mat[i][j].color;
            int val = mat[i][j].efi;
            if (now == 'R')
                R += val;
            else if (now == 'G')
                G += val;
            else if (now == 'B')
                B += val;
            else if (now == 'Y')
                Y += val;
        }
    }
    return 7 * R + 5 * B + 3 * G + 2 * Y;
}

void fillMap(Info mat[5][5], int y, int x, int t, int d) {
    
    memcpy(COPY, mat, sizeof(COPY));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int val = mat[i + y][j + x].efi + efficacy[t][i][j][d];

            if (val < 0)
                COPY[i + y][j + x].efi = 0;
            else if (val > 9)
                COPY[i + y][j + x].efi = 9;
            else COPY[i + y][j + x].efi = val;
            char cl = element[t][i][j][d];
            if (cl != 'W') {
                COPY[i + y][j + x].color = cl;
            }
        }
    }
}

void dfs(Info mat[5][5], int cnt) {
    if (cnt == 3) {
        int score = getScore(mat);
        if (score > ans) ans = score;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (visited[i])
            continue;

        visited[i] = 1;
        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 2; x++) {
                for (int d = 0; d < 4; d++) {
                    fillMap(mat, y, x, i, d);
                    Info tmp[5][5] = { 0, };
                    memcpy(tmp, COPY, sizeof(COPY));
                    dfs(tmp, cnt + 1);
                }
            }
        }
        visited[i] = 0;
    }
}

void init() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            MAP[i][j].efi = 0;
            MAP[i][j].color = 'W';
        }
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int d = 1; d <= 3; d++) {
            rotate(i, d);
        }
    }
    init();
    dfs(MAP, 0);
    cout << ans << '\n';
}

int main() {
    fastIO;
    input();
    solve();
    return 0;
}
