#include <iostream>
#include <string>
#include <queue>
using namespace std;

string type;
queue<string> q;

int main() {
	cin >> type;
	while (true)
	{
		string str;
		cin >> str;
		q.push(str);
		if (str[str.length() - 1] == ';')
			break;
	}
	
	int de = 1;
	while (!q.empty())
	{
		string now = q.front();
		q.pop();

		string tmp = "";
		string var = "";

		for (int i = 0; i < now.length(); i++) {
			if ((now[i] >= 'a' && now[i] <= 'z') || (now[i] >= 'A' && now[i] <= 'Z'))
				var += now[i];
			else
				break;
		}
		for (int i = now.length() - 2; i > 0; i--) {
			if ((now[i] >= 'a' && now[i] <= 'z') || (now[i] >= 'A' && now[i] <= 'Z'))
				break;
			if (now[i] == ']') {
				tmp += "[]";
				i -= 1;
				continue;
			}
			tmp += now[i];
		}
		
		cout << type + tmp << ' ' << var << ';' << '\n';
	}


	return 0;
}
