#include <iostream>
#include <queue> 
using namespace std;

int y;      
int x;      // 처음 씨앗 심는 좌표
int N, M;   // 세로 N 가로 M

int MAP[500][500];
int DAT[500][500];

int day;                // 날짜 세기
int cnt;                // 꽃의 개수 세기
int cnt_arr[1000000];   // 꽃의 개수 저장
int MAX = -21e8;
int idx;                // 꽃의 개수 최대일때 day

struct Node {
    int y; 
    int x; 
};

void bfs(int y, int x) {
   
    queue<Node>q;
    q.push({ y, x });

    
    int visited[500][500] = { 0, };
    visited[y][x] = 1; 

    
    int ydir[] = { -1, 1, 0, 0 };
    int xdir[] = { 0, 0, -1, 1 };

   
    //cout << "DAY #" << day << '\n';


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            DAT[i][j] = visited[i][j];
///////////////////////////////////////////////////////////////////////////////////
            // 꽃의 개화 여부를 바로 확인하기 위해 
            // 새로운 배열 DAT
        /*  100       210       321       432       543
            000  ->   100  ->   210  ->   321  ->   432
            000       000       100       210       321   */
        

      /* DAT배열이 다음과 같이 만들어졌을때 바로 꽃의 개수를 세준 다음
         cnt_arr에 저장해준다. 이 때 꽃의 개수는 
         DAT[i][j] >= 2 && DAT[i][j] <= MAP[i][j] (땅의 비옥함 정도) 일 때
         cnt++해주면 개수를 구할 수 있다. */
//////////////////////////////////////////////////////////////////////////////////


            //cout << visited[i][j];
        }
        //cout << '\n';
    }
    //cout << endl;

    while (!q.empty()) {
        cnt = 0;
        day++;
        int cursize = q.size();
        for (int i = 0; i < cursize; i++) {
            Node now = q.front();
            q.pop();

           /* for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (DAT[i][j] == 1)
                        DAT[i][j] += 1;
                }
            }*/

            for (int i = 0; i < 4; i++) {

                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];
               /* if (visited[now.y][now.x] == 1) {
                    visited[now.y][now.x] = 2;
                    if (DAT[now.y][now.x] == 1)
                        DAT[now.y][now.x] = 2;
                    DAT[now.y][now.x] += 1;
                }*/

                

                if (ny < 0 || nx < 0 || ny >= N || nx >= M)
                    continue;


                if (visited[ny][nx] != 0)
                    continue;

                if (MAP[ny][nx] == 0)
                    continue;


                visited[ny][nx] = 1;
                
                
                q.push({ ny, nx });
                //if (visited[now.y][now.x] == 2 && visited[now.y][now.x] == MAP[now.y][now.x])
                    //visited[now.y][now.x] = -1;
            }
            //if(visited[now.y][now.x] == 2 && visited[now.y][now.x])
            //visited[now.y][now.x] += 1;
            
            
            /*for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    DAT[i][j] = visited[i][j] + visited[now.y][now.x];
                }
            }*/
          
            //DAT[now.y][now.x] = 1 + day;
            //if (visited[now.y][now.x] == 2 && visited[now.y][now.x] == MAP[now.y][now.x])
                //visited[now.y][now.x] = -1;
        }

       /* for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (visited[i][j] > 0)
                    visited[i][j] += 1;
            }
        }*/

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                DAT[i][j] += visited[i][j];
            }
        }
/////////////////////////////////////////////////////////////////////////////////////////////
        /*
 visited[][]
        100     110     111     111     111
        000 ->  100 ->  110 ->  111 ->  111
        000     000     100     110     111
         
 DAT[][] 
        그 정의 DAT와 현재의 visited를 더해주는 방식
   
        */
/////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // 꽃의 개수 세기
                if (DAT[i][j] <= MAP[i][j]+1 && DAT[i][j] >= 2) {
                    cnt++;
                }
            }
        }
        cnt_arr[day] = cnt;

        if (cnt_arr[day] > MAX) {
            MAX = cnt_arr[day];
            idx = day;
        }

       /* cout << "DAY #" << day << '\n';
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << visited[i][j];
            }
            cout << '\n';
        }
        cout << '\n';*/

       /* for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << DAT[i][j];
            }
            cout << '\n';
        }
        cout << '\n';

        cout << cnt << endl;*/
    }
        //cout << visited[by][bx] - 1;

    cout << idx <<"일"<< endl << MAX<<"개";


   /* for (int i = 0; i < 100000; i++) {
        if (cnt_arr[i] > MAX) {
            MAX = cnt_arr[i];
        }
    }*/
    
}


int main() {

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
        }
    }
    cin >> y >> x;
    bfs(y, x);

    return 0;
}