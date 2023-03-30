#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std; 

int s;
string str;

int LCD[10][7] = {
	{1,1,1,0,1,1,1}, //0
	{0,0,1,0,0,1,0}, //1
	{1,0,1,1,1,0,1}, //2
	{1,0,1,1,0,1,1}, //3
	{0,1,1,1,0,1,0}, //4
	{1,1,0,1,0,1,1}, //5
	{1,1,0,1,1,1,1}, //6
	{1,0,1,0,0,1,0}, //7
	{1,1,1,1,1,1,1}, //8
	{1,1,1,1,0,1,1}, //9
};

void printNum(char tmp, int idx) {
	int num = tmp - '0';

	if (idx % 3 == 0) {
		cout << " ";
		if (LCD[num][idx]) {
			for (int i = 0; i < s; i++) 
				cout << "-"; 
		}
		else { 
			for (int i = 0; i < s; i++) 
				cout << " "; 
		}
		cout << "  ";
	}
	else {
		if (LCD[num][idx]) {
			cout << "|"; 
		}
		else cout << " ";
		if (idx % 3 == 1) { 
			for (int i = 0; i < s; i++) 
				cout << " "; 
		}
		else cout << " ";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> s >> str;

	// 가장 윗줄부터 찍어보자
	for (int i = 0; i < str.size(); i++)
		printNum(str[i], 0);
	cout << "\n";

	// 2번째 라인찍어보자
	for (int k = 0; k < s; k++) {
		for (int i = 0; i < str.size(); i++)
			for (int j = 1; j < 3; j++)
				printNum(str[i], j);
		cout << '\n';
	}

	// 3번째
	for (int i = 0; i < str.size(); i++)
		printNum(str[i], 3);
	cout << "\n";

	// 4번째 라인
	for (int k = 0; k < s; k++) {
		for (int i = 0; i < str.size(); i++)
			for (int j = 4; j < 6; j++)
				printNum(str[i], j);
		cout << '\n';
	}

	// 마지막 줄
	for (int i = 0; i < str.size(); i++)
		printNum(str[i], 6);
	cout << '\n';
	return 0;
}
