#include <stdio.h>
using namespace std;

// 뭔가 누적합을 해놓고 dp를 사용 가능해보여서
// dp 사용
// 처음 풀때는 몰라서 교수님께 접근법 물어봄

int N;
int MAP[20][20];
int dp[3][20][20];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &MAP[i][j]);

	// 초기 설정 -> 가로 파이프
	dp[0][1][2] = 1;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			// 초기 값
			if (i == 1 && j == 2)
				continue;
			// 내가 현재 벽이면 설치 불가
			if (MAP[i][j])
				continue;
			// 내가 현재 가로 파이프를 놓으려 할때
			// 왼쪽이 벽이면 설치할 수 없다!
			if (MAP[i][j - 1] == 1)
				dp[0][i][j] = 0;
			else
				dp[0][i][j] = dp[0][i][j - 1] + dp[2][i][j - 1];

			// 내가 현재 설치할 방향이 세로이고
			// 위쪽이 벽이면 설치할 수 없다!
			if (MAP[i - 1][j] == 1)
				dp[1][i][j] = 0;
			else
				dp[1][i][j] = dp[1][i - 1][j] + dp[2][i - 1][j];

			// 내가 현재 설치할 방향이 대각선이고
			// 왼쪽과 위쪽이 벽이면 설치할 수 없다!
			if (MAP[i][j - 1] == 1 || MAP[i - 1][j] == 1)
				dp[2][i][j] = 0;
			else
				dp[2][i][j] = dp[0][i - 1][j - 1] + dp[1][i - 1][j - 1] + dp[2][i - 1][j - 1];
		}
	}

	printf("%d\n", dp[0][N][N] + dp[1][N][N] + dp[2][N][N]);

	return 0;
}
