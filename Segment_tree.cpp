#include<iostream>
#define lc p<<1
#define rc p<<1|1
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int n, m, a[N];
struct node{
	int l, r, add;
	LL sum;
}tr[N*4];

void build(int p, int l, int r){
	tr[p] = {l, r, 0, 0};
	if(l == r){ //是叶子节点则返回 
		tr[p].sum = a[l];
		return;	
	}
	//不是叶子则裂开 
	int m = l + r >> 1;
	build(lc, l, m);
	build(rc, m + 1, r);
	tr[p].sum = tr[lc].sum + tr[rc].sum;
}

//void update(int p, int x, int k){
//	if(tr[p].l == x && tr[p].r == x){
//		tr[p].sum += k;
//		return;
//	}
//	int m = tr[p].l + tr[p].r >> 1;
//	if(x <= m) update(lc, x, k);
//	if(x > m) update(rc, x, k);
//	tr[p].sum = tr[lc].sum + tr[rc].sum;
//}

//向下更新 
void pushdown(int p){
	if(tr[p].add){
		tr[lc].sum += tr[p].add*(tr[lc].r - tr[lc].l + 1),
		tr[rc].sum += tr[p].add*(tr[rc].r - tr[rc].l + 1),
		tr[lc].add += tr[p].add,
		tr[rc].add += tr[p].add,
		tr[p].add = 0; 
	}
}

LL query(int p, int x, int y){
	//覆盖则返回 
	if(x <= tr[p].l && tr[p].r <= y) return tr[p].sum;
	//不覆盖则裂开 
	int m = tr[p].l + tr[p].r >> 1;
	pushdown(p);
	LL sum = 0;
	if(x <= m) sum += query(lc, x, y);
	if(y > m) sum += query(rc, x, y);
	return sum;
}

void update(int p, int x, int y, int k){
	//覆盖则修改 
	if(x <= tr[p].l && tr[p].r <= y){
		tr[p].sum += (tr[p].r - tr[p].l + 1)*k;
		tr[p].add += k;
		return;
	}
	//不覆盖则裂开 
	int m = tr[p].l + tr[p].r >> 1;
	pushdown(p);
	if(x <= m) update(lc, x, y, k);
	if(y > m) update(rc, x, y, k);
	tr[p].sum = tr[lc].sum + tr[rc].sum;
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	while(m--){
		int t, x, y, k;
		cin >> t >> x >> y;
		if(t == 1){
			cin >> k;
			update(1, x, y, k);
		}else cout << query(1, x, y) << endl;
	}
}

//p3372

//5 5
//1 5 4 2 3
//2 2 4
//1 2 3 2
//2 3 4
//1 1 5 1
//2 1 4

//11
//8
//20
