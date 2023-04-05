#include <iostream>
#include <vector>
using namespace std;

struct tree {
	int y;
	int x;
};


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
			if (jecho[i][j] > 0)
				MAP[i][j] = 0;
			if (MAP[i][j] > 0 && jecho[i][j] == 0)
				tmp[i][j] = 1;
			else
				tmp[i][j] = 0;
		}
	}
}

// ¼ºÀå
void Plus() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (MAP[i][j] > 0 && tmp[i][j] == 1) {
				int cnt = 0;
				for (int p = 0; p < 4; p++) {
					int ny = i + dy[p];
					int nx = j + dx[p];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

					if (MAP[ny][nx] > 0)
						cnt++;
				} // ºóÄ­ÀÇ ¼ö Ã¼Å©

				MAP[i][j] += cnt;

			}
		}
	}
}

// ¹ø½Ä
// ³ª¹« ÁÖº¯¿¡ ºóÄ­ÀÇ ¼ö¸¦ Ã¼Å©ÇÏ°í ±× ¼ö¸¸Å­ ³ª´²¼­ ¹ø½Ä
void New() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (MAP[i][j] > 0 && tmp[i][j] == 1) {
				int cnt = 0;
				for (int p = 0; p < 4; p++) {
					int ny = i + dy[p];
					int nx = j + dx[p];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

					if (MAP[ny][nx] >= 0 && tmp[ny][nx] == 0 && jecho[ny][nx] == 0)
						cnt++;
				} // ºóÄ­ÀÇ ¼ö Ã¼Å©

				for (int p = 0; p < 4; p++) {
					int ny = i + dy[p];
					int nx = j + dx[p];

					if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

					if (tmp[ny][nx] == 0 && MAP[ny][nx] >=0 && jecho[ny][nx] == 0)
						MAP[ny][nx] += MAP[i][j] / cnt;
				} // ºóÄ­ Ã¤¿ì±â

			
			}
				
		}
	}


}

int MAX = -21e8;
int idxy;
int idxx;
int nk;
int cnt;

void Kill() {
	MAX = -21e8;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (MAP[i][j] > 0) {
				int sum = MAP[i][j];
				nk = 1;
				while (1) {
					for (int q = 4; q < 8; q++) {
						int ny = i + dy[q] * nk;
						int nx = j + dx[q] * nk;

						if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

						if (MAP[ny][nx] == -1) continue;

						if (MAP[ny-dy[q]][nx-dx[q]] <= 0) continue;

						sum += MAP[ny][nx];
					}
					
					if (nk == k) break;
					nk++;
				}

				if (MAX < sum) {
					MAX = sum;
					idxy = i;
					idxx = j;
				}
			}
		}
	}
	ans += MAX;
	nk = 0;
	while (1) {
		for (int q = 4; q < 8; q++) {
			int ny = idxy + dy[q] * nk;
			int nx = idxx + dx[q] * nk;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (MAP[ny-dy[q]][nx-dx[q]] <= 0) continue;

			
			jecho[ny][nx] = c+1;
			
		}
		nk++;
		if (nk == k+1) break;
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

	while (1) {

		Check();
		
		SetJecho();
		Plus();
		
		New();
		
		Check();

		Kill();

		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << jecho[i][j] << " ";
			}
			cout << endl;
		}*/
		
		m--;
		if (m == 0) break;
	}
	cout << ans << endl;


}