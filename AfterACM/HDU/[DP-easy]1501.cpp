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
char str[N], s1[N], s2[N];
int n, m;

void conduct() {
	int i, j;
	scanf("%s%s%s", s1, s2, str);
	memset(f, 0, sizeof(f)); f[0][0]=1;
	n=strlen(s1); m=strlen(s2);
	for (i=0; i<=n; ++i) for (j=0; j<=m; ++j) if (f[i][j]) {
		if (i<n && s1[i]==str[i+j]) f[i+1][j]=1;
		if (j<m && s2[j]==str[i+j]) f[i][j+1]=1;
	}
	if (f[n][m]) printf("yes\n"); else printf("no\n");
}

int main() {
	int time; scanf("%d", &time);
	for (int i=1; i<=time; ++i) {
		printf("Data set %d: ", i);
		conduct();
	}
}
