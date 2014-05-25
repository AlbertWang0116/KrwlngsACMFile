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

#define N 110
char s1[N], s2[N];
int f[N][N], cmd[N][N];
int n, m, ans;

void print(int x, int y) {
	if (!x && !y) return;
	if (cmd[x][y]==0) print(x-1, y-1);
	else if (cmd[x][y]==1) {
		printf("%d Replace %d,%c\n", ++ans, x, s2[y-1]);
		print(x-1, y-1);
	}
	else if (cmd[x][y]==2) {
		printf("%d Insert %d,%c\n", ++ans, x+1, s2[y-1]);
		print(x, y-1);
	}
	else if (cmd[x][y]==3) {
		printf("%d Delete %d\n", ++ans, x);
		print(x-1, y);
	}
}

void conduct() {
	int i, j;
	memset(f, 0x7f, sizeof(f)); f[0][0]=0;
	n=strlen(s1); m=strlen(s2);
	for (i=0; i<=n; ++i) for (j=0; j<=m; ++j) {
		if (i<n && f[i+1][j]>f[i][j]+1) { cmd[i+1][j]=3; f[i+1][j]=f[i][j]+1; }
		if (j<m && f[i][j+1]>f[i][j]+1) { cmd[i][j+1]=2; f[i][j+1]=f[i][j]+1; }
		if (i<n && j<m)
			if (s1[i]==s2[j] && f[i+1][j+1]>f[i][j]) { cmd[i+1][j+1]=0; f[i+1][j+1]=f[i][j]; }
			else if (s1[i]!=s2[j] && f[i+1][j+1]>f[i][j]+1) { cmd[i+1][j+1]=1; f[i+1][j+1]=f[i][j]+1; }
	}
	printf("%d\n", f[n][m]); ans=0;
	print(n, m);
}

int main() {
	while (scanf("%s%s", s1, s2)!=EOF) conduct();
	return 0;
}
