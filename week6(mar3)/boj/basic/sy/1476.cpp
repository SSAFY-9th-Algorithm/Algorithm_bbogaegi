#include <iostream>
using namespace std;

int E, S, M;

int main() {
    cin >> E >> S >> M;
	int year = 1;
	while (true)
	{
		if ((year - E) % 15 == 0 && (year - S) % 28 == 0 && (year - M) % 19 == 0)
			break;
		year++;
	}
	cout << year;
    return 0;
}
