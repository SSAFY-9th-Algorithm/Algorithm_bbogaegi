#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

int arr[50000];
unordered_map<int, int>um;

int main(int argc, char** argv)
{
	int N, Q;
	cin>>N>>Q;
	for(int i=0;i<N;i++) {
		cin>>arr[i];
	}
	sort(arr, arr+N);
	um[arr[0]] = um[arr[N-1]] = 0;
	for(int i=1;i<N-1;i++) {
		int now = arr[i];
		um[now] = i*(N-i-1);
	}

	for(int i=0;i<Q;i++) {
		int q;
		cin>>q;
		if(um.find(q) == um.end()) {
			cout<<"0\n";
		}
		else{
			cout<<um[q]<<'\n';
		}
	}

	return 0;
}
