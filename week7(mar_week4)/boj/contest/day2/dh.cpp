#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
    int y;
    int x;
};
int N, M;
int MAP[8][8];
vector<Node>pos;
int MIN = 21e8;

int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, -1, 0, 1 };

// x, y에서 cctv가 d방향 확인
void check(int x, int y, int d) {
    d = d % 4; // 0, 1, 2, 3 -> 우 상 좌 하
    while (1) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        y = ny;
        x = nx;
        if (nx < 0 || ny < 0 || nx >= N || ny >= M) break;
        if (MAP[nx][ny] == 6) break;;
        if (MAP[nx][ny] != 0) continue;
        MAP[nx][ny] = '#';
    }
}


void func(int a) {
    if (a == pos.size()) { // 미리 넣어둔 cctv를 모두 확인했음
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (MAP[i][j] == 0) cnt++;
            }
        }
        MIN = min(cnt, MIN);
        return;
    }
    int y = pos[a].x;
    int x = pos[a].y;
    int tmp[8][8];
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
            tmp[i][j] = MAP[i][j];

    for (int dir = 0; dir < 4; dir++) { // 4번 회전
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                tmp[i][j] = MAP[i][j];
            }
        }
       
        if (MAP[x][y] == 1) {
            check(x, y, dir); 
        }
        else if (MAP[x][y] == 2) {
            check(x, y, dir);       // 우 상 좌 하
            check(x, y, dir + 2);   // 좌 하 우 상

        }
        else if (MAP[x][y] == 3) {
            check(x, y, dir);       // 우 상 좌 하
            check(x, y, dir + 1);   // 상 좌 하 우
        }
        else if (MAP[x][y] == 4) {
            check(x, y, dir);       // 우 상 좌 하
            check(x, y, dir + 1);   // 상 좌 하 우
            check(x, y, dir + 2);   // 좌 하 우 상

        }
        else if (MAP[x][y] == 5) {
            check(x, y, dir);       // 네 방향 모두
            check(x, y, dir + 1); 
            check(x, y, dir + 2); 
            check(x, y, dir + 3); 
        }
        func(a + 1); //다음 cctv 회전시키기
        for (int i = 0; i < N; i++) { // 복구
            for (int j = 0; j < M; j++) {
                MAP[i][j] = tmp[i][j];
            }
        }
    }
}


int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] >= 1 && MAP[i][j] <= 5) {
                pos.push_back({ i, j });
            }
        }
    }
    func(0);
    cout << MIN;

    return 0;
}