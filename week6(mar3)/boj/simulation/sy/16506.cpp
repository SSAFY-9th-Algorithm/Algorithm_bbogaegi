#include <iostream>
#include <unordered_map>
#include <string>
using namespace std; 

unordered_map<string, string> opcode = {
	{"ADD", "00000"},
	{"ADDC", "00001"},
	{"SUB", "00010"},
	{"SUBC", "00011"},
	{"MOV", "00100"},
	{"MOVC", "00101"},
	{"AND", "00110"},
	{"ANDC", "00111"},
	{"OR", "01000"},
	{"ORC", "01001"},
	{"NOT", "01010"},
	{"MULT", "01100"},
	{"MULTC", "01101"},
	{"LSFTL", "01110"},
	{"LSFTLC", "01111"},
	{"LSFTR", "10000"},
	{"LSFTRC", "10001"},
	{"ASFTR", "10010"},
	{"ASFTRC", "10011"},
	{"RL", "10100"},
	{"RLC", "10101"},
	{"RR", "10110"},
	{"RRC", "10111"}
};

int ans[16];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// reset
		string qry;
		int rD, rA, rB;
		// input
		cin >> qry >> rD >> rA >> rB;
		cout << opcode[qry] + "0";
		// solve
		for (int i = 2; i >= 0; i--){
			int temp = (rD >> i) & 1;
			cout << temp;
		}

		if (rA == 0)
			cout << "000";
		else {
			for (int i = 2; i >= 0; i--) {
				int temp = (rA >> i) & 1;
				cout << temp;
			}
		}

		if (opcode[qry][4] == '0') {
			for (int i = 2; i >= 0; i--) {
				int temp = (rB >> i) & 1;
				cout << temp;
			}
			cout << 0 << '\n';
		}
		else if(opcode[qry][4] == '1'){
			for (int i = 3; i >= 0; i--) {
				int temp = (rB >> i) & 1;
				cout << temp;
			}
			cout << '\n';
		}
	}

	return 0;
}
