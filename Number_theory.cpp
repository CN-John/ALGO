#include<iostream>
using namespace std;
typedef long long LL; 
const int N = 1e6 + 10;
int prime[N], cnt;
int phi[N];//欧拉函数 
int de_cnt[N];//质因子个数
int mu[N];//莫比乌斯函数
int a[N]/*记录i的最小质因子的次数*/, d[N]/*i的约数个数*/; 
int g[N]/*i的最小质因子的1+p^1+..+p^k*/, f[N]/*约数和*/;
bool vis[N];

//最大公约数-欧几里得算法(辗转相除法)
int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

//质数判定-试除法 
bool isPrime(int x){
	for(int i = 2; i*i <= x; i++){
		if(!(x%i)) return false;
	}
	return true;
}

//分解质因数-试除法 
void decompose(int x){
	for(int i = 2; i*i <= x; i++)
		while(!(x%i)) de_cnt[i]++, x /= i;
	if(x > 1) de_cnt[x]++; 
} 

//筛质数-埃氏筛法 O(nloglogn)
void e_prime(int n){ 
	for(int i = 2; i <= n; i++){
		if(!vis[i]){
			prime[cnt++] = i;
			for(int j = i*i; j <= n; j += i) vis[j*i] = 1;
		}		
	}
}

//筛质数-线性筛法 O(n)
void o_prime(int n){ 
	for(int i = 2; i <= n; i++){
		if(!vis[i]) prime[cnt++] = i;
		for(int j = 0; 1ll*i*prime[j] <= n; j++){
			vis[i*prime[j]] = 1;
			if(!(i%prime[j])) break; //整除中断 
		}
	}
}

//试除法求欧拉函数 
int Phi(int x){
	int res = x;
	for(int i = 2; i*i <= x; i++){
		if(!(x%i)){
			res = res/i*(i - 1);
			while(!(x%i)) x /= i;
		}
	}
	if(x > 1) res = res/x*(x - 1);
	return res;
} 

//筛法求欧拉函数
void get_Phi(int n){ 
	phi[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!vis[i]){
			prime[cnt++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0; i*prime[j] <= n; j++){
			vis[i*prime[j]] = 1;
			if(!(i%prime[j])){
				phi[i*prime[j]] = prime[j]*phi[i];
				break;
			}else phi[i*prime[j]] = (prime[j] - 1)*phi[i]; 
		}
	}
}

//筛法求莫比乌斯函数 
void get_mu(int n){
	mu[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!vis[i]){
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for(int j = 0; i*prime[j] <= n; j++){
			vis[i*prime[j]] = 1;
			if(!(i%prime[j])){
				mu[i*prime[j]] = 0;
				break;
			}
			else mu[i*prime[j]] = -mu[i];
		}
	}
} 

//筛法求约数个数
void get_d(int n){ 
	d[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!vis[i]){
			prime[cnt++] = i;
			a[i] = 1, d[i] = 2;
		}
		for(int j = 0; i*prime[j] <= n; j++){
			int m = i*prime[j]; 
			vis[i*prime[j]] = 1;
			if(!(i%prime[j])){
				a[m] = a[i] + 1;
				d[m] = d[i]/a[m]*(a[m] + 1);
				break;
			}
			else a[m] = 1, d[m] = d[i]*2;
		}
	}
} 

//筛法求约数和
void get_f(int n){
	g[1] = f[1] = 1;
	for(int i = 2; i <= n; i++){ 
		if(!vis[i]){
			prime[cnt++] = i;
			g[i] = f[i] = i + 1;
		}
		for(int j = 0; i*prime[j] <= n; j++){
			int m = i*prime[j];
			vis[m] = 1;
			if(!(i%prime[j])){
				g[m] = g[i]*prime[j] + 1;
				f[m] = f[i]/g[i]*g[m];
				break;
			}
			else g[m] = prime[j] + 1, f[m] = f[i]*g[m];
		}
	}
}

signed main(){
//	cout << gcd(18, 12);
//	cout << isPrime(4);
//	decompose(280);
//	o_prime(20);
//	cout << Phi(10); 
//	get_Phi(20);
//	get_mu(20);
//	get_d(20);
	get_f(20);
	for(int i = 1; i <= 20; i++)
		cout << i << ' ' << f[i] << endl;
	return 0;
}
