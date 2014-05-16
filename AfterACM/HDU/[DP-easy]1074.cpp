#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>
using namespace std;

#define N 110000
#define M 20
char name[M][110];
int a[M], b[M], f[N], pre[N];
int n, m;

void print(int x) {
	if (x) print(x^(1<<pre[x]));
	else return;
	printf("%s\n", name[pre[x]]);
}

void conduct() {
	int i, j, k, tmp;
	scanf("%d", &n);
	for (i=0; i<n; ++i) scanf("%s%d%d", name[i], &a[i], &b[i]);
	memset(f, 0x70, sizeof(f)); f[0]=0;
	for (i=0; i<(1<<n); ++i) {
		for (j=k=0; j<n; ++j) if (i&(1<<j)) k+=b[j];
		for (j=n-1; ~j; --j) if ((i&(1<<j))==0) {
			tmp=f[i]+(k+b[j]>a[j]?k+b[j]-a[j]:0);
			if (tmp<f[i|(1<<j)]) { f[i|(1<<j)]=tmp; pre[i|(1<<j)]=j; }
		}
	}
	printf("%d\n", f[(1<<n)-1]);
	print((1<<n)-1);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
