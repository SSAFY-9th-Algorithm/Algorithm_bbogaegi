#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

// 마을을 두 그룹으로 나눈 뒤 조건을 만족하는지 확인한다 => 마을들 중에서 임의의 수의 마을을 선택하면 나머지 마을들끼리 한 그룹이 된다. --> "조합"
// 조건 1. A, B그룹에 마을이 최소 한개가 들어 있는가?
// 조건 2. A, B그룹에 들어있는 마을들끼리 서로 연결되어 있는가?

int T;
int N;
int MAP[9][9];
int visited[9];
int P[21];
int TP; // Total People
vector<int>A;
vector<int>B;
int res;
int MIN = 21e8;

bool Connect(vector<int>v) {    // 그룹내의 마을들이 서로 연결되었는지 확인하는 함수
   
    int cnt = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (MAP[v[i]][v[j]] == 1) {
                cnt++;
            }
        }
    }
    if (cnt < (v.size() - 1) * 2) {     // 길의 개수가 마을의 수 N-1보다 작으면 모두 연결될 수 없다 (양방향이므로 x2를 해준 것)
        return false;
    }

    int flag = 0;
    for (int i = 0; i < v.size()-1; i++) {
        flag = 0;
        for (int j = i+1; j < v.size(); j++) {
            if (MAP[v[i]][v[j]] == 1)   // 
                flag = 1;
            break;
        }
        if (flag == 0) {
            break;
            return false;
        }
    }
    if (flag == 1)
        return true;
}

bool Check() {
    for (int i = 0; i < N; i++) {
        if (visited[i] == 1)
            A.push_back(i);
        else
            B.push_back(i);
    }
    
    if (A.size() == 0 || B.size() == 0)
        return false;

    if (Connect(A) == true && Connect(B) == true)
        return true;
}

void dfs(int now, int cnt) {

    if (cnt >= 1) {
        if (Check() == true) {
            int AP = 0;
            int BP = 0;
            for (int i = 0; i < A.size(); i++) {
                AP += P[A[i]];
            }
            res = abs(2 * AP - TP);
            if (MIN > res)
                MIN = res;

        }
    }
    
    for (int next = now; next < N; next++) {
        
        if (visited[next] == 1) continue;
        visited[next] = 1;
   
        dfs(next, cnt + 1);
        //cout << MIN;

    }
}

int main() {
    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        memset(MAP, 0, sizeof(MAP));
        memset(P, 0, sizeof(P));
        memset(visited, 0, sizeof(visited));
        A.clear();
        B.clear();
        TP = 0;
        res = 0;
        MIN = 21e8;


        cin >> N;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> MAP[i][j];

        for (int i = 0; i < N; i++) {
            cin >> P[i];
            TP += P[i];
        }
        dfs(0, 0);
        cout << '#' << tc << ' ' << MIN << endl;


    }
    return 0;
}