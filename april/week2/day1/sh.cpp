#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;
unordered_map<string, int> um;
int NOW;

vector<string> split(string str, char base) {
	istringstream iss(str);
	string buf;
	vector<string> res;
	while (getline(iss, buf, base)) {
		res.push_back(buf);
	}
	return res;
}

void MakeUM(vector<string> terms) {
	int cursize = terms.size();
	for (int i = 0; i < cursize; i++) {
		vector<string> temp = split(terms[i], ' ');
		um[temp[0]] = stoi(temp[1]);
	}
}

int Dates(vector<string> v) {
	return (stoi(v[0]) - 2000) * 28 * 12 + stoi(v[1]) * 28 + stoi(v[2]);
}

vector<int> SplitPrivacies(vector<string> pri) {
	int cursize = pri.size();
	vector<int> res;

	for (int i = 0; i < cursize; i++) {
		vector<string> temp = split(pri[i], ' ');
		int remains = um[temp[1]];
		vector<string> temp2 = split(temp[0], '.');

		int sum = Dates(temp2);

		if (NOW - sum >= remains * 28) res.push_back(i + 1);
	}
	return res;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
	MakeUM(terms);
	vector<string> Today = split(today, '.');

	NOW = Dates(Today);
	vector<int> ans = SplitPrivacies(privacies);
	return ans;
}
