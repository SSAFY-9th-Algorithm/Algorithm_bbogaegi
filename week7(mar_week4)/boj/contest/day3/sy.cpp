// 한 번의 이동에서 이미 합쳐진 블록은 또 합쳐질 수 없기 때문이다.
// 문제를 잘 읽자
// 문제가 생겼던 부분 -> memcpy에서 복사가 제대로 안됨
// 이거모르고 계속 삽질

#include <iostream>
#include <cstring>
using namespace std;

int N;
int ans = 0;

void getMax(int MAP[25][25]) {
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
            ans = max(ans, MAP[i][j]);
}

void up(int MAP[25][25]) {
    int DAT[25][25] = { 0, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (MAP[i][j] == 0)
                continue;
            for (int k = i; k > 0; --k) {
                if (MAP[k - 1][j] != 0) {
                    if (MAP[k - 1][j] == MAP[k][j] && (!DAT[k - 1][j])) {
                        MAP[k - 1][j] *= 2;
                        DAT[k - 1][j] = 1;
                        MAP[k][j] = 0;
                    }
                    break;
                }
                else {
                    MAP[k - 1][j] = MAP[k][j];
                    MAP[k][j] = 0;
                    DAT[k - 1][j] = DAT[k][j];
                    DAT[k][j] = 0;
                }
            }
        }
    }
    getMax(MAP);
}

void down(int MAP[25][25]) {
    int DAT[25][25] = { 0, };
    for (int i = N - 1; i >= 0; --i) {
        for (int j = N - 1; j >= 0; --j) {
            if (MAP[i][j] == 0)
                continue;
            for (int k = i; k < N - 1; ++k) {
                if (MAP[k + 1][j] != 0) {
                    if (MAP[k + 1][j] == MAP[k][j] && (!DAT[k + 1][j])) {
                        MAP[k + 1][j] *= 2;
                        DAT[k + 1][j] = 1;
                        MAP[k][j] = 0;
                    }
                    break;
                }
                else {
                    MAP[k + 1][j] = MAP[k][j];
                    MAP[k][j] = 0;
                    DAT[k + 1][j] = DAT[k][j];
                    DAT[k][j] = 0;
                }
            }
        }
    }
    getMax(MAP);
}

void left(int MAP[25][25]) {
    int DAT[25][25] = { 0, };
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            if (MAP[i][j] == 0)
                continue;
            for (int k = j; k > 0; --k) {
                if (MAP[i][k - 1] != 0) {
                    if (MAP[i][k - 1] == MAP[i][k] && (!DAT[i][k - 1])) {
                        MAP[i][k - 1] *= 2;
                        DAT[i][k - 1] = 1;
                        MAP[i][k] = 0;
                    }
                    break;
                }
                else {
                    MAP[i][k - 1] = MAP[i][k];
                    MAP[i][k] = 0;
                    DAT[i][k - 1] = DAT[i][k];
                    DAT[i][k] = 0;
                }
            }
        }
    }
    getMax(MAP);
}

void right(int MAP[25][25]) {
    int DAT[25][25] = { 0, };
    for (int j = N - 1; j >= 0; --j) {
        for (int i = N - 1; i >= 0; --i) {
            if (MAP[i][j] == 0)
                continue;
            for (int k = j; k < N - 1; ++k) {
                if (MAP[i][k + 1] != 0) {
                    if (MAP[i][k + 1] == MAP[i][k] && (!DAT[i][k + 1])) {
                        MAP[i][k + 1] *= 2;
                        DAT[i][k + 1] = 1;
                        MAP[i][k] = 0;
                    }
                    break;
                }
                else {
                    MAP[i][k + 1] = MAP[i][k];
                    MAP[i][k] = 0;
                    DAT[i][k + 1] = DAT[i][k];
                    DAT[i][k] = 0;
                }
            }
        }
    }
    getMax(MAP);

}

void dfs(int move, int dir, int MAP[25][25]) {
    if (move == 5) {
        return;
    }
    int COPY[25][25];
    /*memcpy(COPY, MAP, sizeof(MAP));*/
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            COPY[i][j] = MAP[i][j];
    if(dir == 0)
        up(COPY);
    else if(dir == 1)
        down(COPY);
    else if(dir == 2)
        left(COPY);
    else
        right(COPY);

    for (int i = 0; i < 4; ++i) {
        dfs(move + 1, i, COPY);
    }
}

int main() {
    int MAP[25][25] = { 0, };
    cin >> N;
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j) 
            cin >> MAP[i][j];
        
    for (int i = 0; i < 4; ++i) 
        dfs(0, i, MAP);
    
    cout << ans << '\n';
    return 0;
}
