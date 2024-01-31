#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int A[N], B[N], C[N], la, lb, lc;

//高精度加法 
void add(int* A, int* B, int* C){
	for(int i = 0; i < lc; i++){
		C[i] += A[i] + B[i]; //累加
		C[i + 1] = C[i]/10;  //进位
		C[i] %= 10; 		 //存余 
	}
	if(C[lc]) lc++;
}

bool cmp(int* A, int* B){
	if(la != lb) return la > lb;
	for(int i = la - 1; i >= 0; i--){
		if(A[i] != B[i]) return A[i] > B[i];
	}
	return true; //避免结果为0 
}

//高精度减法 
void sub(int* A, int* B, int* C){
	if(!cmp(A, B)) swap(A, B), cout << '-';
	for(int i = 0; i < lc; i++){
		if(A[i] < B[i])
			A[i + 1]--, A[i] += 10; //错位 
		C[i] = A[i] - B[i];			//存差 
	}
	while(lc && !C[lc]) lc--;		//处理前导0 
}

//高精度乘法 
void mul(int* A, int* B, int* C){
	for(int i = 0; i < la; i++){
		for(int j = 0; j < lb; j++){
			C[i + j] += A[i]*B[j];		//累加乘积 
			C[i + j + 1] += C[i + j]/10;//进位 
			C[i + j] %= 10;				//存余 
		}
	}
	while(lc && !C[lc]) lc--;
}

//高精度除法 
void div(int* A, int b, int* C){
	LL r = 0;
	for(int i = la - 1; ~i; i--){
		r = r*10 + A[i];	//被除数 
		C[la - 1 - i] = r/b;//存商 
		r %= b;				//余数 
	}
	for(int i = 0; i != lc/2; i++){
		int tmp = C[i];
		C[i] = C[lc - 1 - i];
		C[lc - 1 - i] = tmp;
	}	//reverse 
	while(lc && !C[lc]) lc--;
} 

signed main(){
//	string a, b;
//	cin >> a >> b;
//	la = a.size(), lb = b.size(), lc = max(la, lb);
//	for(int i = la - 1; i >= 0; i--) A[la - 1 - i] = a[i] - '0';
//	for(int i = lb - 1; i >= 0; i--) B[lb - 1 - i] = b[i] - '0';

//	add(A, B, C);
//	for(int i = lc - 1; ~i; i--) cout << C[i];

//	sub(A, B, C);
//	for(int i = lc; ~i; i--) cout << C[i];

//	lc = la + lb;
//	mul(A, B, C);
//	for(int i = lc; ~i; i--) cout << C[i];
	
	string a;
	int b;
	cin >> a >> b;
	lc = la = a.size();
	for(int i = la - 1; i >= 0; i--) A[la - 1 - i] = a[i] - '0';
	div(A, b, C);
	for(int i = lc; ~i; i--) cout << C[i];
	return 0;
}
