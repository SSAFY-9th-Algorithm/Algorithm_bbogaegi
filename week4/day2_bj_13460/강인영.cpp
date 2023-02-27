#include <iostream>
using namespace std;

struct Node{
int y; 
int x;
};
Node red, blue, hole;
int n, m;
char map[10][10];

int main() {
  cin >> n >> m;
  for(int i=0; i<n;i++){
    for(int j=0; j<m;j++){
      cin >> map[i][j];
      if(map[i][j]=='R')
        red = {i,j};
      else if(map[i][j]=='B')
        blue = {i,j};
      else if(map[i][j]=='O')
        hole = {i,j};
    }
  }

  for(int i=0; i<n;i++){
    for(int j=0; j<m;j++){
      cout << map[i][j];
    }cout << endl;
  }
}
