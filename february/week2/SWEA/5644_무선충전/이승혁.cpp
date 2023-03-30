#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Charger {
    int x,y;
    int range, power;
};

int Move[2][100];
int da[5][2] = { {0,0},{-1,0},{0,1},{1,0},{0,-1} };
int M, C, X1, X2, Y1, Y2 , sum;

Charger charger[8];
vector<int> v[2];

bool cmp(Charger left, Charger right) {
    if (left.power < right.power)
        return false;
    if (left.power > right.power)
        return true;
    return false;
}

void moving(int time) {
    int ch1d = Move[0][time];
    Y1 = Y1 + da[ch1d][0];
    X1 = X1 + da[ch1d][1];

    int ch2d = Move[1][time];
    Y2 = Y2 + da[ch2d][0];
    X2 = X2 + da[ch2d][1];
}

void findCharger() {
    for (int i = 0; i < C; i++) {
        if ((abs(charger[i].y -Y1) + abs(charger[i].x - X1)) <= charger[i].range) 
            v[0].push_back(i);
        if ((abs(charger[i].y - Y2) + abs(charger[i].x - X2)) <= charger[i].range)
            v[1].push_back(i);
    }
}

void charging() {

    findCharger();

    int v1 = v[0].size();
    int v2 = v[1].size();

    if (v1 == 0 && v2 == 0) return;

    if (v1 == 0) {
        sum += charger[v[1][0]].power;
        return;
    }
    else if (v2 == 0) {
        sum += charger[v[0][0]].power;
        return;
    }

    if (v[0][0] == v[1][0])
    {
        int temp = 0;
        for (int i = 0; i < v1; i++) {
            for (int j = 0; j < v2; j++) {
                if (charger[v[0][i]].power == charger[v[1][j]].power) temp = max(temp, charger[v[0][i]].power);
                else temp = max(charger[v[0][i]].power + charger[v[1][j]].power, temp);
            }
        }
        sum += temp;
        return;
    }
 
    else {
        sum += charger[v[0][0]].power;
        sum += charger[v[1][0]].power;
    }

}


int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        X1 = 1;
        Y1 = 1;
        X2 = 10;
        Y2 = 10;
        sum = 0;
        memset(charger, 0, sizeof(charger));
        memset(Move, 0, sizeof(Move));
        // input
        cin >> M >> C;
        for (int i = 0; i < 2; i++) for (int j = 0; j < M; j++) cin >> Move[i][j];
        for (int i = 0; i < C; i++) {
            Charger temp;
            cin >> temp.x >> temp.y >> temp.range >> temp.power;
            charger[i] = temp;
        }
        sort(charger, charger + C, cmp);

        // solve
        for (int time = 0; time <= M; time++) {
            charging();
            v[0].clear();
            v[1].clear();
            moving(time);
        }

        // output
        cout <<"#"<<tc<<" "<<sum<<'\n';
    }


}
