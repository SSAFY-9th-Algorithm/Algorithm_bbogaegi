#include<iostream>
#include <queue>
using namespace std;

int T;
int cost[4]; // 1일 이용권, 1달 이용권, 3달 이용권, 1년 이용권
int day[13];
int result;

void dfs(int now, int sum) {
    
    if (result <= sum) return;

    if (now > 12) {
        if (result < sum) {
            return;
        }
        else {
            result = sum;
            return;
        }
    }

    //없음
    if (day[now] == 0) {
        dfs(now + 1, sum);
    }
    else {

        //1일
        dfs(now + 1, sum + cost[0] * day[now]);
        //1달
        dfs(now + 1, sum + cost[1]);
        //3달
        dfs(now + 3, sum + cost[2]);
    }

}

int main(int argc, char** argv)
{
    cin >> T;

    int t = 1;
    while (t <= T) {
        for (int i = 0; i < 4; i++) {
            cin >> cost[i];
        }

        for (int i = 1; i < 13; i++) {
            cin >> day[i];
        }

        result = cost[3];
        dfs(0, 0);

        cout << "#" << t << ' ' << result << "\n";
        t++;
    }

    return 0;
}
