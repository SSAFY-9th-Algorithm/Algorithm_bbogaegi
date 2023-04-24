#include <iostream>
#include <vector>
using namespace std;

/*
N X N 격자판
(r,c) : r 행 c 열 1부터 시작 -> 벽 or 빈 칸
3개의 - | \ 방향 가능
파이프 밀면서 회전 가능. 회전 45도만 가능. 오른쪽,아래,오른아래 방향.
가로로 놓인 경우 -> 이동 2가지 방법 : -> \
세로로 놓인 경우 -> 이동 2가지 방법 : | \
대각선 놓인 경우 -> 이동 3가지 방법 : -> | \
처음 파이프 (1,1) (1,2) 가로 방향 차지.
한쪽 끝을 (N,N)으로 이동시키는 방법 개수.
*/

int N;
int MAP[17][17];
int answer;

struct Pipe {
    int ly;
    int lx;
    int ry;
    int rx;
    int d;
};
                        //가로    //세로   //대각선
int dirChance[3][3] = { {1,0,1}, {0,1,1}, {1,1,1} }; //확인해야 할 방향들
int dirList[3][3] = { {1,0,0}, {0,1,0}, {1,1,1} }; //dir에서 가는향방향
int dir[3][2] = {
   {0,1}, //가로
   {1,0}, //세로
   {1,1}  //대각선
};
vector<int>path; //경로 기담기

void dfs(Pipe nowpipe) {

    if (nowpipe.ry == N-1 && nowpipe.rx == N-1) {
        /*for (int i = 0; i < path.size(); i++) {
            cout << path[i] << ' ';
        }
        cout << endl;*/
        answer++;
        return;
    }

    for (int i = 0; i < 3; i++) {
        int chance = dirChance[nowpipe.d][i];
        if (chance != 1)
            continue;

        if (i == 2)
            int de = 1;

        // 확인해야 할 곳들(sum)이 괜찮으면 flag 값 증가
        int flag = 0;
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            if (dirList[i][j] != 1)
                continue;
            sum++;
            int ny = nowpipe.ry + dir[j][0];
            int nx = nowpipe.rx + dir[j][1];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N)
                continue;
            if (MAP[ny][nx] == 1)
                continue;

            flag++;
        }
        
        //모두 괜찮아서 해당 방향은 갈 수 있다고 확정됨
        if (flag == sum) {
            //갈 수 있는 경로
            int nry = nowpipe.ry + dir[i][0];
            int nrx = nowpipe.rx + dir[i][1];

            path.push_back(i);
            dfs({ nowpipe.ry, nowpipe.rx, nry, nrx, i });
            path.pop_back();
        }
    }
}

int main() {

    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[i][j];
        }
    }

    // 출발지
    Pipe start = { 0,0,0,1,0 };

    dfs(start);

    cout << answer;

}
