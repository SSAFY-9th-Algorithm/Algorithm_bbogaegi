#include <iostream>
#include <queue> 
using namespace std;

int y;      
int x;      // ó�� ���� �ɴ� ��ǥ
int N, M;   // ���� N ���� M

int MAP[500][500];
int DAT[500][500];

int day;                // ��¥ ����
int cnt;                // ���� ���� ����
int cnt_arr[1000000];   // ���� ���� ����
int MAX = -21e8;
int idx;                // ���� ���� �ִ��϶� day

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
            // ���� ��ȭ ���θ� �ٷ� Ȯ���ϱ� ���� 
            // ���ο� �迭 DAT
        /*  100       210       321       432       543
            000  ->   100  ->   210  ->   321  ->   432
            000       000       100       210       321   */
        

      /* DAT�迭�� ������ ���� ����������� �ٷ� ���� ������ ���� ����
         cnt_arr�� �������ش�. �� �� ���� ������ 
         DAT[i][j] >= 2 && DAT[i][j] <= MAP[i][j] (���� ����� ����) �� ��
         cnt++���ָ� ������ ���� �� �ִ�. */
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
        �� ���� DAT�� ������ visited�� �����ִ� ���
   
        */
/////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // ���� ���� ����
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

    cout << idx <<"��"<< endl << MAX<<"��";


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