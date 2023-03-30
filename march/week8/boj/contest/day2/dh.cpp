#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// ���� 1 2 3 4 -> �� �� �� ��

// �� ���� ������ ��� struct�� ���� �ѹ��� ����
struct Shark {
    int x;
    int y;
    int dir; // ����� ���� ����
    vector<int>priority[5]; 
    // priority[1]: ���� ������ �� ���϶� ���� ���� �켱����
    // priority[2]: ���� ������ �� ���϶� ���� ���� �켱����
    int flag;
    // flag�� 0�̸� �� ���� 1�̸� �Ѱܳ����Ƿ� ���� üũ�����ʿ� ����
};


int MAP[3][21][21];

//vector<int>MAP[21][21]; // �ʿ� ������ �����Ѵ� -> ó���� �̷��� �ߴµ� push_back���� ���� �־�����ؼ� �ȵ�
// �ʿ� �����ϴ� ���, ������ �������� �ð�, ������ ��� ����� ������ ������ ����
// MAP[0][x][y], MAP[1][x][y], MAP[2][x][y]
int N, M, k;
Shark shark[450];

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };


int Check()
{
    for (int i = 2; i <= M; i++)
    {
        if (shark[i].flag == 0) return 0; // 1���� ������ ��� �ϳ��� ������ ���� ����X
    }
    return 1;
}


void smellSet(int t) // t�� ����ð�
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            MAP[1][i][j] -= 1;

    for (int i = 1; i <= M; i++)
    {
        if (shark[i].flag == 1) continue; // �̹� �Ѱܳ� ���

        int x = shark[i].x;
        int y = shark[i].y;
        MAP[1][x][y] = k;
        MAP[2][x][y] = i;
    }
}

void Move(int t) // ��� �����̱�
{
    for (int i = 1; i <= M; i++) {
        if (shark[i].flag == 1) continue;
        int x = shark[i].x;
        int y = shark[i].y;
        MAP[0][x][y] = 0; // ���� ������ ��ġ �������
    }

    for (int i = 1; i <= M; i++) {
        if (shark[i].flag == 1) continue;

        int x = shark[i].x;
        int y = shark[i].y;
        int d = shark[i].dir;

        // �ڱ� ���� ��ġ�� ���� ���� ���
        int storeX = -1; // ó���� 0���� �ʱ�ȭ�ߴµ� ��ǥ�� 0�ϼ��� �ִ�
        int storeY = -1;
        int storeDir = -1;
       
        int flag = 0;

        for (int j = 0; j < shark[i].priority[d].size(); j++) // ���� ������ �켱���� ������ �����̱�
        {
            if (shark[i].flag == 1) continue; // �Ѱܳ� ���� ���X
            int ndir = shark[i].priority[d][j];
            int nx = x + dx[ndir];
            int ny = y + dy[ndir];
            if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                if (MAP[1][nx][ny] <= 0)
                {
                    flag = 1; // �ֺ��� �̹� ������ �ѷ��� �ִ� ��� ���� ���ֱ� ����
                    if (MAP[0][nx][ny] == 0) { // �� ĭ�� �� ���� -> �׳� �̵� ����
                        MAP[0][nx][ny] = i;
                    }
                    else { // 0�� �ƴ� �� ��ȣ�� �� �����Ѵ�
                        if (MAP[0][nx][ny] < MAP[0][x][y])
                            MAP[0][nx][ny] = i;
                        else {
                            shark[i].flag = 1;
                            continue;
                        }
                    }
                    shark[i].x = nx;
                    shark[i].y = ny;
                    shark[i].dir = ndir;
                    break;
                }
                else // ������ ������ ĭ�� �ٸ� ����� ������ �ѷ����ִ�
                {
                    if (MAP[2][nx][ny] == i) 
                    {
                        if (storeX == -1)   // �켱���� ������ ���ٰ� ���� ���� �ڱ� ������ �߰����� �� 
                        {
                            storeX = nx;
                            storeY = ny;
                            storeDir = ndir;
                        } // �̷��� �����صΰ� ����� ������ �ѷ��������� (flag=0�� ��) �� ��ǥ�� �̵���Ų��
                    }
                }
            }
        }

        if (flag == 0)
        {
            MAP[0][storeX][storeY] = i;
            shark[i].x = storeX;
            shark[i].y = storeY;
            shark[i].dir = storeDir;
        }
    }
}


int main() {
    cin >> N >> M >> k;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> MAP[0][i][j];
            int num = MAP[0][i][j]; // ��� ��ȣ
            if (MAP[0][i][j] != 0) { // �� �����Ѵ�
                shark[num].x = i;
                shark[num].y = j;
            }
            MAP[1][i][j] = 0;
            MAP[2][i][j] = 0;
        }
    }



    for (int i = 1; i <= M; i++) {
        int d;
        cin >> d;
        shark[i].dir = d;
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= 4; j++) {
            int arr[4];
            cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
            for (int k = 0; k < 4; k++)
            {
                shark[i].priority[j].push_back(arr[k]);
                // �� ���⸶�� �켱���� ���� ����
            }
        }
    }

   

    int res = 0;

    for (int t = 0; t <= 1000; t++) {

        
        if (Check()) {
            res = t;
            break;
        }
        smellSet(t);
        
        Move(t);
       
    }
    if (res != 0)
        cout << res << endl;
    else
        cout << -1 << endl;
}