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

#define N 1010
int a[N][N], b[N][N], id[N], val[N];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j, ans, top, sum;
	char str[10];
	scanf("%d%d", &n, &m);
	for (i=0; i<n; ++i) for (j=0; j<m; ++j) {
		scanf("%s", str);
		if (str[0]=='R') a[i][j]=0;
		else a[i][j]=1;
	}
	for (j=0; j<m; ++j) for (sum=i=0; i<n; ++i)
		if (a[i][j]) b[i][j]=sum=sum+1;
		else b[i][j]=sum=0;
	for (ans=i=0; i<n; ++i) {
		id[0]=-1; val[0]=-1; top=0;
		for (j=0; j<m; ++j) {
			while (b[i][j]<=val[top]) {
				ans=getmax(ans, val[top]*(j-id[top-1]-1));
				top--;
			}
			++top; id[top]=j; val[top]=b[i][j];
		}
		while (top) { ans=getmax(ans, val[top]*(m-id[top-1]-1)); top--; }
	}
	printf("%d\n", ans*3);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
