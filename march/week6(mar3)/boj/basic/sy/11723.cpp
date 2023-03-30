#include <iostream>
using namespace std;

int M;
int n, i;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string qry;
	cin >> M;
	for (int m = 0; m < M; m++) {
		cin >> qry;

		if (qry == "add") {
			cin >> n;
			// 원소를 추가할건데
			// (1<<n) : 1을 n칸 왼쪽으로 이동한다! 
			// i |= : or 연산 후 i에 대입한다!
			i |= (1 << n);
		}
		else if (qry == "remove") {
			cin >> n;
			// 원소를 삭제헤보자
			// ~(1<<n) : 1000에서 0과 1을 바꿈 
			// i &= : and 연산 후 i에 대입한다!
			i &= ~(1 << n);
		}
		else if(qry == "check"){
			cin >> n;
			if (i & (1 << n)) cout << 1 << '\n';
			else cout << 0 << '\n';
		}
		else if(qry == "toggle"){
			cin >> n;
			// 원소가 있다!
			if (i & (1 << n)) // 없애자!
				i &= ~(1 << n);
			else // 원소가 없다면 추가하자!
				i |= (1 << n);
			// i ^= (1<<n) -> 같은 코드
		}
		else if(qry == "all"){
			i = (1 << 21) - 1;
		}
		else {
			i = 0;
		}
	}


	return 0;
}
