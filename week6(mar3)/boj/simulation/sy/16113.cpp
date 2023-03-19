#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std; 

int N;
unordered_map<string, int> um = {
    {"####.##.##.####", 0},
    {"###..#####..###", 2},
    {"###..####..####", 3},
    {"#.##.####..#..#", 4},
    {"####..###..####", 5},
    {"####..####.####", 6},
    {"###..#..#..#..#", 7},
    {"####.#####.####", 8},
    {"####.####..####", 9}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	string sig;
	cin >> sig;

	int n = N / 5;

    vector<string> v;

    for (int i = 0; i < N; i += n) 
        v.push_back(sig.substr(i, N));

    for (int i = 0; i < n; i++) {
        if (v[0][i] == '#') {

            if (i == n - 1 || (v[0][i + 1] == '.' && v[3][i] == '#')) {
                cout << 1;
                continue;
            }

            string res = "";
            for (int j = 0; j < 5; j++)
                res += v[j].substr(i, 3);
            

            if (um.find(res) != um.end()) {
                cout << um[res];
                i += 3;
            }
        }
    }
	return 0;
}
