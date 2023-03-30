// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###// ### 미해결 문제 ###
// 접근 방식은 재귀로 4개면 n/2개씩 path -> v.push_back ( [01 02 03 12 13 23] ) 다 담는다
// i= 0 ~ 벡터 사이즈/2까지, i & vsize-i 쌍으로 하면 조합 완성(01,23) ( 02,13) (03,12) 
// 걔들 계산 -> MIN=min(MIN,abs(map[1][0] + map[0][1] - map[2][3] + map[3][2]))
// 6개부터는 3번줄 조합도 포문을 돌려야함.. (1,2,3) (4,5,6) -> 12 13 23 , 45 46 56 이딴식으로 푸는게 맞나 모르겠는데..
// 미생물로 체력 소진.
// ### 해결 문제 ###// ### 해결 문제 ###// ### 해결 문제 ###// ### 해결 문제 ###// ### 해결 문제 ###
#include <iostream>
#include <cstring>
using namespace std;
 
int N, MAP[16][16],path[16];
int MIN;
 
void calc() {
    int sumA = 0;
    int sumB = 0;
    for (int i = 0; i < N ; i++) {
        for (int j = 0; j < N; j++) {
            if (path[i] == path[j]) {
                if (path[i] == 1) sumA += MAP[i][j] ;
                if (path[i] == 0) sumB += MAP[i][j] ;
            }
        }
 
    }
    if (abs(sumA - sumB) < MIN) MIN = abs(sumA - sumB);
}
 
void dfs(int level,int cnt) {
    // N/2개 뽑았으며 면 계산 수행
    if (cnt == N / 2) {
        calc();
        return;
    }
    if (level == N)return;
    // 아직 아니라면
 
    // 뽑거나 
    path[level] = 1;
    dfs(level + 1, cnt + 1);
    path[level] = 0;
    // 안뽑거나
    dfs(level+1, cnt);
 
}
 
 
int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        // reset
        memset(MAP, 0, sizeof(MAP));
        memset(path, 0, sizeof(path));
        MIN = 21e8;
 
        // input
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> MAP[i][j];
            }
        }
 
        // solve
        dfs(0,0);
        // output
        cout <<"#"<<tc<<" "<< MIN<<'\n';
    }
 
 
}
