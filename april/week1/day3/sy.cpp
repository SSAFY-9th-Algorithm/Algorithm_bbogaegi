#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
using pi = pair<int, int>;
/*
    설계
    1. 각 팀 정보를 가지고 
    2. 저장하여 주어진 조건에 따라 움직이며
    3. 점수를 구한다
    
    길을 1차원에 저장할 수는 없을까?
    아직 생각 
*/
// 0은 빈칸, 1은 머리사람, 2는 머리사람과 꼬리사람이 아닌 나머지, 3은 꼬리사람, 4는 이동 선
// #1. 머리사람을 따라서 한 칸 이동
// #2. 공을 던진다
// #3. k번째 사람이라면 k의 제곱만큼 점수, 공을 획득한 팀의 경우에는 머리사람과 꼬리사람이 바뀝니다. 즉 방향을 바꾸게 됩니다.

struct Team {
    int num;
    pi head;
    pi tail;
    int dir;
};

int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };

int N; // 3<= N <= 20
int M; // 팀의 개수 ( 1<= M <= 5)
int K; // 라운드 수 ( 1<= K <= 1000)
int MAP[21][21];
int RAIL[21][21];
int tail[6];

vector<pi> v[6]; 

int visited[21][21];

void input() {
    int idx = 0;
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1)
                v[idx++].push_back({ i, j });
        }
}

// 레일
void dfs(int y, int x, int idx) {
    visited[y][x] = 1;
    RAIL[y][x] = idx;

    for (int i = 0; i < 4; i++) {
        int ny = y + ydir[i];
        int nx = x + xdir[i];

        if (ny<1 || nx<1 || ny>N || nx>N)
            continue;
        if (!MAP[ny][nx])
            continue;
        if (visited[ny][nx])
            continue;
        if (v[idx].size() == 1 && MAP[ny][nx] != 2)
            continue;

        v[idx].push_back({ ny, nx });
        if (MAP[ny][nx] == 3)
            tail[idx] = v[idx].size();

        dfs(ny, nx, idx);
    }
}

void move() {

}

void shotBall() {

}

void changeDir() {

}

int main() {
    
    return 0;
}
