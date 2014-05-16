#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

#define N 110
int a[N][N], b[N][N];
int n;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, k, ans, tmp;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &a[i][j]);
	ans=0x80000000;
	for (k=1; k<=n; ++k) {
		for (j=0; j<n; ++j) {
			for (tmp=i=0; i<k; ++i) tmp+=a[i][j]; b[i-k][j]=tmp;
			for (; i<n; ++i) { tmp=tmp+a[i][j]-a[i-k][j]; b[i-k+1][j]=tmp; }
		}
		for (i=0; i<n-k+1; ++i) 
			for (tmp=j=0; j<n; ++j) {
				tmp=tmp>=0?tmp+b[i][j]:b[i][j];
				ans=getmax(ans, tmp);
			}
	}
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
