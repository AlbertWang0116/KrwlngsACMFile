#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;

#define M 9901
int prm[M], tag[M];
int sum[M], num[M], ele[M];
int n, m;

void erase(int x, int id) {
	int i, upr;
	tag[x] = 1; upr = (M-1)/x;
	for (i = id; i < prm[0] && upr >= prm[i]; ++i) erase(x*prm[i], i);
}

void init() {
	int i, cur;
	memset(tag, 0, sizeof(tag)); prm[0] = 0;
	for (i = 2; i < M; ++i) if (!tag[i]) {
		for (cur = 1; (M-1)/cur >= i; cur *= i) erase(cur*i, 1);
		prm[++prm[0]] = i;
	} 
}

void input() {
	scanf("%d%d", &n, &m);
}

void conduct() {
	int i, j, cnt, cur;
	if (n == 0) { printf("0\n"); return; }
	for (cnt = 0, i = 1; i <= prm[0]; ++i) if (n % prm[i] == 0) {
		ele[cnt] = prm[i]; num[cnt] = 0; while (n % prm[i] == 0) { num[cnt]++; n /= prm[i]; } cnt++;
	} if (n != 1) { ele[cnt] = n % M; num[cnt] = 1; cnt++; n = 1; }
	for (i = 0; i < cnt; ++i) {
		sum[0] = 0; sum[1] = 1; cur = 1;
		for (j = 2; j < M; ++j) { cur = (cur*ele[i]) % M; sum[j] = (sum[j-1]+cur) % M; }
//		for (j = 0; j < 20; ++j) printf("sum[%d]=%d\n", j, sum[j]);
		n = (n * ((num[i]*m+1)/(M-1)*sum[M-1]+sum[(num[i]*m+1)%(M-1)]) % M) % M;
	} printf("%d\n", n);
}

int main() {
	init();
	input();
	conduct();
	return 0;
}
