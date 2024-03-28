#include<iostream>
using namespace std;
const int N = 5e5 + 10;
int a[N], s[N]/*区间和*/, n, m;

//提取i的低位二次幂 
int lowbit(int i){return i & -i;}

int query(int i){ //向前查 
	int ans = 0;
	while(i) s[i], i -= lowbit(i);
	return ans;
}

void update(int i, int v){ //向后修 
	while(i <= n) s[i] += v, i += lowbit(i);
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	while(m--){
		int t, x, y;
		cin >> t >> x;
		if(t == 1){
			cin >> y >> t;
			//利用差分，将区修转化为点修
			//差分的前缀和即修改值
			//原始值+修改值即答案 
			update(x, t);
			update(y + 1, -t);
		}
		else cout << a[x] + query(x) << endl; 
	}
	return 0;
}
