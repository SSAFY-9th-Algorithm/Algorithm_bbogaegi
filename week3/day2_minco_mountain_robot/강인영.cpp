/*
1. 반복문 탐색하면서 map에 있는 한 칸에서 이동 진행
2. 이동한 위치에서 최소값 갱신
3. 터널 처리
4. 결과값 
*/

#include <iostream>
#include <string.h>
using namespace std;

int T;
int n, m;
int map[31][31];
int fuelmap[31][31];
int ans;
struct Tunnel {
    int ay;
    int ax;
    int by;
    int bx;
    int cost;
};
Tunnel tunnel[31];

//각 칸의 높이를 비교해서 필요한 연료를 계산하기 위한 함수
int getFuel(int y, int x, int ny, int nx) {
    if (map[y][x] > map[ny][nx]) {
        return 0;
    }
    else if (map[y][x] < map[ny][nx]) {
        return (map[ny][nx] - map[y][x]) * 2;
    }
    else {
        return 1;
    }
}

int  dir[4][2] = {
    -1,0,
    1,0,
    0,-1,
    0,1
};
//상,하,좌,우 이동을 통해 소요되는 연료 값을 최소로 갱신
void update(int y, int x) {
  //첫 시작 좌표는 연료 0으로 고정
    if (y == 1 && x == 1) {
        fuelmap[y][x] = 0;
    }
   
    for (int i = 0; i < 4; i++) {
        int ny = y + dir[i][0];
        int nx = x + dir[i][1];
        if (ny >= 1 && nx >= 1 && nx <= n && ny <= n) {
            int fuel = getFuel(y, x, ny, nx); //칸 높이를 계산해서 얻은 연료 값
            fuelmap[ny][nx] = min(fuelmap[ny][nx], fuel+fuelmap[y][x]); //기존에 입력되어 있던 연료값과 새로운 이동을 통해 소요된다고 보는 연료 중 최소로 업데이트
        }
    }
}
//터널을 사용하는 경우를 위한 함수
void gothrough(Tunnel tun) {
    int sfuel = fuelmap[tun.ay][tun.ax]; //터널 시작위치의 연료값
    int ffuel = sfuel + tun.cost; //터널 끝 위치의 연료값
  //만약 터널을 통과하는 경우가 기존의 이동보다 연료가 적게 든다면 터널을 이용하는 것으로 갱신
    if (fuelmap[tun.by][tun.bx] > ffuel) {
        fuelmap[tun.by][tun.bx] = ffuel;
        update(tun.by, tun.bx);//터널 이동 후에 변경된 값으로 상,하,좌,우 다시 갱신
    }
    
    return;    
}

int main() {
    
    cin >> T;
    int t = 1;
    while (t <= T) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> map[i][j];
            }
        }
        for (int i = 0; i < m; i++) {
            cin >> tunnel[i].ay >> tunnel[i].ax >> tunnel[i].by >> tunnel[i].bx >> tunnel[i].cost;
        }

        //최소값으로 fuelmap 생성
        memset(fuelmap, 600, sizeof(fuelmap));
        //1 & 2. 이동한 후에 이동 위치 최소값 갱신
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
               update(i, j);
            }
        }
        //3. 터널 처리
        for (int i = 0; i < m; i++) {
            Tunnel tun = tunnel[i];
            gothrough(tun);
        }
        //4. 결과값
        ans = fuelmap[n][n];
        cout << "#" << t++ << " " << ans<<endl;
        
    }

    return 0;
}
