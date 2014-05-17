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

#define N 1100
#define M 50
int f[M][N], a[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }

void conduct() {
	int i, j, k, head, tail;
	int tmp, ans;
	for (i=0; i<n; ++i) cin >> a[i];
	memset(f, 0x7f, sizeof(f));
	for (tmp=i=0; i<n; ++i) {
		if (i) tmp+=i*(a[i]-a[i-1]);
		f[1][i]=tmp;
	}
	for (i=1; i<m; ++i) for (j=i-1; j<n; ++j) {
		head=tail=j; tmp=0;
		for (k=j+1; k<n; ++k) {
			tmp+=(tail-head+1)*(a[k]-a[k-1]); tail++;
			while (head<tail && a[head]-a[j]<a[k]-a[head]) tmp+=2*a[head++]-a[j]-a[k];
			f[i+1][k]=getmin(f[i+1][k], f[i][j]+tmp);
		}
	}
	for (ans=f[m][n-1], tmp=0, i=n-2; i>=m-1; --i) {
		tmp+=(n-i-1)*(a[i+1]-a[i]);
		ans=getmin(ans, f[m][i]+tmp);
	}
	printf("Total distance sum = ");
	cout << ans << endl;
}

int main() {
	int time=0;
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) {
		printf("Chain %d\n", ++time);
		conduct();
		printf("\n");
	}
	return 0;
}
