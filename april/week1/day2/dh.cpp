#include <iostream>
#include <vector>
using namespace std;


/*

11 446 20 3
0 0 0 -1 57 0 -1 0 0 0 0
0 18 0 -1 -1 0 0 0 0 0 45
64 0 10 0 0 -1 74 0 0 33 0
0 61 0 0 -1 0 0 0 0 0 -1
0 66 0 0 0 0 0 0 16 0 0
7 0 0 0 6 0 0 -1 27 72 0
0 0 0 0 0 54 0 42 -1 -1 0
0 0 -1 0 0 0 0 1 0 0 98
-1 98 68 0 0 75 1 93 0 0 0
0 0 0 0 77 0 0 -1 0 0 0
0 -1 0 -1 0 0 0 0 45 0 0

*/

int n, m, k, c;
int MAP[21][21];
int tmp[21][21];
int jecho[21][21];

int dy[8] = { -1, 1, 0, 0, -1, 1, 1, -1 };
int dx[8] = { 0, 0, -1, 1, -1, -1, 1, 1 };

int ans;

void SetJecho() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(jecho[i][j] > 0)
				jecho[i][j] -= 1;
		}
	}
}

void Check() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			
			if (jecho[i][j] > 0 && MAP[i][j] != -1)
				MAP[i][j] = 0;
			if (MAP[i][j] > 0 && jecho[i][j] == 0)
				tmp[i][j] = 1;
			else
				tmp[i][j] = 0;
		}
	}
}

// 성장
void Plus() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tmp[i][j] == 1) {
				int cnt = 0;
				for (int p = 0; p < 4; p++) {
					int ny = i + dy[p];
					int nx = j + dx[p];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

					if (MAP[ny][nx] > 0)
						cnt++;
				} // 나무 수 체크

				MAP[i][j] += cnt;

			}
		}
	}
}

// 번식
// 나무 주변에 빈칸의 수를 체크하고 그 수만큼 나눠서 번식
void New() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if ( tmp[i][j] == 1) {
				int cnt = 0;
				for (int p = 0; p < 4; p++) {
					int ny = i + dy[p];
					int nx = j + dx[p];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

					if (tmp[ny][nx] == 0 && jecho[ny][nx] == 0 && MAP[ny][nx] >=0)
						cnt++;
				} // 빈칸의 수 체크

				for (int p = 0; p < 4; p++) {
					int ny = i + dy[p];
					int nx = j + dx[p];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

					if (tmp[ny][nx] == 0 && MAP[ny][nx] >=0 && jecho[ny][nx] == 0)
						MAP[ny][nx] += MAP[i][j] / cnt;
				} // 빈칸 채우기

				/*cout << endl;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						cout << MAP[i][j] << " ";
					}
					cout << endl;
				}*/


			}
				
		}
	}

	/*cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << MAP[i][j]<<" ";
		}
		cout << endl;
	}*/

}

int MAX = -21e8;
int idxy;
int idxx;
int nk;


void Kill() {
	MAX = -21e8;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (MAP[i][j] > 0) {
				//MAX = -21e8;
				int sum = MAP[i][j];
				//nk = 1;

				for (int q = 4; q < 8; q++) {
					nk = 1;
					while (1) {
						int ny = i + dy[q] * nk;
						int nx = j + dx[q] * nk;

						if (ny < 0 || nx < 0 || ny >= n || nx >= n) break;

						if (MAP[ny][nx] <= 0) break;

						//if (MAP[ny - dy[q]][nx - dx[q]] <= 0) continue;

						sum += MAP[ny][nx];
						

						if (nk == k) break;
						nk+=1;
					}
					
				}
				//cout << " " << sum << endl;
				if (MAX < sum) {
					MAX = sum;
					idxy = i;
					idxx = j;
				}
			}
		}
	}
	ans += MAX;
	//nk = 1;
	jecho[idxy][idxx] = c + 1;
	
		for (int q = 4; q < 8; q++) {
			nk = 1;
			while (1) {
				int ny = idxy + dy[q] * nk;
				int nx = idxx + dx[q] * nk;

				if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
					//cout << " 범위 초과로 종료 \n";
					break;
				}

				/*cout << endl;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						cout << MAP[i][j] << " ";
					}
					cout << endl;
				}*/

				if (MAP[ny][nx] <= 0) {
					//cout << " 벽 또는 제초제 만나서 종료 \n";
					jecho[ny][nx] = c + 1;
					break;
				}

				//MAP[ny][nx] = 0;
				jecho[ny][nx] = c + 1;
				//MAP[ny][nx] = 0;
				/*if (MAP[ny][nx] > 0)
					cnt++;*/

				if (nk == k) break;
				nk+=1;
			}
		}
	

}



int main() {
	cin >> n >> m >> k >> c;
	int a = 0; // 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}
	int f = 0;
	while (1) {

		//cout << f++ << endl;
		Check();
		/*cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << tmp[i][j] << " ";
			}
			cout << endl;
		}*/
		SetJecho();

		/*cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << jecho[i][j] << " ";
			}
			cout << endl;
		}*/

		Plus();
		/*cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << MAP[i][j] << " ";
			}
			cout << endl;
		}*/
		New();
		/*cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << MAP[i][j] << " ";
			}
			cout << endl;
		}*/
		Check(); 



		//cout << endl;
		//for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < n; j++) {
		//		cout << MAP[i][j] << " ";
		//	}
		//	cout << endl;
		//}




		MAX = -21e8;
		//Kill();

		int flag = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (tmp[i][j] == 1)
					flag = 1;
			}
		}
		if (flag == 0) break;

		Kill();

		//cout << endl << ans << " " << idxy << " " << idxx << endl;
		Check();
		/*cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << jecho[i][j] << " ";
			}
			cout << endl;
		}*/
		//cout << ans << endl;
		m--;
		if (m == 0) break;
	}
	cout << ans << endl;


}