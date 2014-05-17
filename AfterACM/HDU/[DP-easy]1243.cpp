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

#define N 110000
char str[N], s1[N], s2[N];
int sc[N];
int n, l1, l2;

inline int getmax(int x, int y) { return x>y?x:y; }

void conduct() {
	int i, j;
	scanf("%s", str);
	for (i=0; i<n; ++i) {
		scanf("%d", &j);
		sc[str[i]]=j;
	}
	scanf("%s", s1); l1=strlen(s1);
	scanf("%s", s2); l2=strlen(s2);
	int **f = (int**)malloc((l1+1)*sizeof(int*));
	for (i=0; i<=l1; ++i) f[i]=(int*)malloc((l2+1)*sizeof(int));
	for (i=0; i<=l1; ++i) f[i][0]=0;
	for (i=0; i<=l2; ++i) f[0][i]=0;
	for (i=1; i<=l1; ++i) for (j=1; j<=l2; ++j)
		f[i][j]=getmax(f[i-1][j-1]+(s1[i-1]==s2[j-1]?sc[s1[i-1]]:0), getmax(f[i-1][j], f[i][j-1]));
	printf("%d\n", f[l1][l2]);
	for (i=0; i<=l1; ++i) free(f[i]);
	free(f);
}

int main() {
	while (scanf("%d", &n)!=EOF) conduct();
	return 0;
}
