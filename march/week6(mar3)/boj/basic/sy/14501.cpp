#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int T[1100];
int P[1100];
int dp[20];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) 
        cin >> T[i] >> P[i];
    
    for (int i = N; i > 0; i--) {
        int last = i + T[i];
        if (last > N + 1)
            dp[i] = dp[i + 1];
        else
            dp[i] = max(dp[i + 1], dp[last] + P[i]);
    }
   
    cout << dp[1];
    return 0;
}
