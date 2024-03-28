#include<iostream>
using namespace std;
const int N = 1e5 + 10;
int fa[N];

//带路径压缩查找 
int find(int x){
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

//合并，把一个集合的根指向另一个集合的根 
void unionset(int x, int y){
	fa[find(x)] = find(y);
}

int main(){
	int n, m, x, y, z;
	cin >> n >> m;
	//fa[]初始化 
	for(int i = 1; i <= n; i++) fa[i] = i;
	while(m--){
		cin >> z >> x >> y;
		if(z == 1) unionset(x, y);
		else{
			x = find(x), y = find(y);
			if(x == y) puts("Y");
			else puts("N");
		}
	}
	return 0;
}
//p3367
 
//4 7
//2 1 2
//1 1 2
//2 1 2
//1 3 4
//2 1 4
//1 2 3
//2 1 4

//N
//Y
//N
//Y
