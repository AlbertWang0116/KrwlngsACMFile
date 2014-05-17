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
int f[N][N];
char s1[N], s2[N];
int n, m;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j;
	scanf("%s", s2);
	memset(f, 0, sizeof(f));
	n=strlen(s1); m=strlen(s2);
	for (i=1; i<=n; ++i) for (j=1; j<=m; ++j)
		if (s1[i-1]==s2[j-1]) f[i][j]=f[i-1][j-1]+1;
		else f[i][j]=getmax(f[i-1][j], f[i][j-1]);
	printf("%d\n", f[n][m]);	
}

int main() {
	while (scanf("%s", s1)!=EOF) conduct();
	return 0;
}
