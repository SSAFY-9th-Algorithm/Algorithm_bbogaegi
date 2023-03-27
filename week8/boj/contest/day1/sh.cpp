#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
10 1 1000
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
100 100 100 100 100 100 100 100 100 100
1 1 1
*/

struct coord {int y, x;};
struct tree {
    int y, x, age, isAlive;

    bool operator< (tree next)const {
        if (age < next.age) return false;
        if (age > next.age) return true;
        return false;
    }
};


queue<coord> q;
priority_queue<tree> pq;
vector<int> v[11][11];
int A[11][11], MAP[11][11], N, M, K;


void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
        {
            cin >> A[i][j];
            MAP[i][j] = 5;
        }
    }

    for (int i = 0; i < M; i++) {
        int y, x, age;
        cin >> y >> x >> age;
        q.push({y,x});
        pq.push({ y,x,age,1 });
    }
}

 void seasons() {

     int temp[11][11] = {0,};
     int qsize = q.size();

     for(int qs=0;qs<qsize;qs++){

         int ydir[] = { -1,-1,-1,0,0,1,1,1 };
         int xdir[] = { -1,0,1,-1,1,-1,0,1 };

         coord now = q.front(); q.pop();
         int vsize = v[now.y][now.x].size();
         int flag = 0;

         if (vsize >= 1) {
             sort(v[now.y][now.x].begin(), v[now.y][now.x].end());

             for (int i = 0; i < vsize; i++) {// 빼야하는데
                 int age = v[now.y][now.x][i];
                 if (MAP[now.y][now.x] < age)
                 {
                     temp[now.y][now.x] += age / 2;
                     continue;
                 }

                 else {
                     flag = 1;
                     MAP[now.y][now.x] -= age;
                     age++;
                     if (age % 5 == 0) {
                         for (int i = 0; i < 8; i++) {
                             int ny = now.y + ydir[i];
                             int nx = now.x + xdir[i];
                             if (ny<1 || nx<1 || ny>N || nx>N)continue;
                             v[ny][nx].push_back(1);
                         }
                     }
                 }
                 v[now.y][now.x].push_back(age);
             }
             
         }
         if (flag)q.push(now);
     }

    // 겨울
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            MAP[i][j] += A[i][j] + temp[i][j];


}

int main() {

    input();

    for (int i = 0; i < K; i++) seasons();
    cout << pq.size();


}
