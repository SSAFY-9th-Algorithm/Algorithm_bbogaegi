// 모든 칸에 5 양분
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;

struct treedetail {
	int age;
	int grow;
};
int n, m, k;
int fuel[11][11];
int morefuel[11][11];
vector<treedetail>MAP[11][11];

bool cmp(treedetail a, treedetail b) {
	return a.age > b.age;
}

int main() {
	//memset(fuel, 5, sizeof(fuel));
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> morefuel[i][j];
			fuel[i][j] = 5;
		}
	}

	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		MAP[y-1][x-1].push_back({z, 0});
	}

	int year = 0;
	while (year != k) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int treeCnt = MAP[i][j].size();
				int deadTree = 0;
				if (!MAP[i][j].empty()) {
					sort(MAP[i][j].begin(), MAP[i][j].end(), cmp);
					vector<treedetail>tmpMAP;
					for (int t = 0; t < treeCnt; t++) {
						treedetail tree = MAP[i][j].back();
						MAP[i][j].pop_back();
						if (tree.grow > year) {
							//MAP[i][j].push_back(tree);
							tmpMAP.push_back(tree);
							continue;
						}
						if (fuel[i][j] >= tree.age) {
							fuel[i][j] -= tree.age;
							//MAP[i][j].push_back({ tree.age + 1, year +1 });
							tmpMAP.push_back({ tree.age + 1, year + 1 });
						}
						else {
							deadTree += (tree.age / 2);
						}
					}
					int tmpMAPsize = tmpMAP.size();
					for (int t = 0; t < tmpMAPsize; t++) {
						MAP[i][j].push_back(tmpMAP[t]);
					}
					fuel[i][j] += deadTree;
				}
			}
		}
		
		//가을
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int treeCnt = MAP[i][j].size();
				if ( !MAP[i][j].empty() ) {
					for (int t = 0; t < treeCnt; t++) {
						treedetail tree = MAP[i][j][t];
						int diry[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
						int dirx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
						if (tree.age % 5 == 0) {
							for (int ii = 0; ii < 8; ii++) {
								int ni = i + diry[ii];
								int nj = j + dirx[ii];
								if (ni < 0 || nj < 0 || ni >= n || nj >= n)
									continue;
								MAP[ni][nj].push_back({ 1, 0 });
							}
						}
					}
				}
			}
		}
		//겨울
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fuel[i][j] += morefuel[i][j];
			}
		}

		year++;

	}

	int trees = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (MAP[i][j].size() != 0)
				trees += MAP[i][j].size();
		}
	}
	cout << trees;
}
