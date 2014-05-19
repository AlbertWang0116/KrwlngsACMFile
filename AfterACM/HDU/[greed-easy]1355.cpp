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

#define N 3100
#define M 61
int a[M][M];
int seq[N];
int n, m, mst;

int cmp(const int &i, const int &j) { return a[i/m][i%m]>a[j/m][j%m]; }

void conduct() {
	int i, j, mst, ans;
	scanf("%d%d%d", &n, &m, &mst);
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) scanf("%d", &a[i][j]);
	for (i=0; i<n*m; ++i) seq[i]=i; sort(seq, seq+n*m, cmp);
	if ((seq[0]/m+1)*2+1>mst) { printf("0\n"); return; }
	mst-=seq[0]/m+2; ans=a[seq[0]/m][seq[0]%m];
	for (i=1; i<n*m && abs(seq[i]/m-seq[i-1]/m)+abs(seq[i]%m-seq[i-1]%m)+seq[i]/m+2<=mst; ++i) {
		ans+=a[seq[i]/m][seq[i]%m];
		mst-=abs(seq[i]/m-seq[i-1]/m)+abs(seq[i]%m-seq[i-1]%m)+1;
	}
	printf("%d\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
