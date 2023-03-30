#include <iostream>
#include <vector>
using namespace std;

/*
10 10
1 1 1 1 1 1 1 1 1 1

10 10
1 1 1 1 1 1 1 1 1 10
*/

int N, S;
vector<int> v;

int main() {
	cin >> N >> S;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}

	int left = 0;
	int right = 0;

	int len, milen = 21e8;

	int sum = 0;
	while (true)
	{
		int de = 1;
		if (milen == 1)
			break;
		if (sum >= S) {
			len = right - left;
			if (milen > len)
				milen = len;
			sum -= v[left];
			left++;
		}
		else if (right == N)
			break;
		else if(sum < S){
			sum += v[right];
			right++;
		}
	}
	
	if (milen == 21e8) milen = 0;
	cout << milen;
	return 0;
}
