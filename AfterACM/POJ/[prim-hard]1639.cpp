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
char name[N][N];
int len[N], pre[N], t[N][N], e[N][N], vst[N], lst[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }

void mst(int s) {
	int i, j, k, l;
	memset(len, 0x7f, sizeof(len)); len[s]=0; e[s][s]=0;
	for (i=0; i<n; ++i) pre[i]=s;
	memset(vst, 0, sizeof(vst)); vst[s]=1;
	for (i=1; i<n; ++i) {
		for (j=0, k=0x7fffffff; j<n; ++j) if (!vst[j] && len[j]<k) { k=len[j]; l=j; }
		vst[l]=1; t[l][pre[l]]=t[pre[l]][l]=1;
		for (j=0; j<n; ++j) if (!vst[j] && len[j]>e[l][j]) { len[j]=e[l][j]; pre[j]=l; }
	}
}

void dfs(int x, int p) {
	if (len[x]>len[lst[p]]) lst[x]=x; else lst[x]=lst[p]; vst[x]=1;
	for (int i=0; i<n; ++i) if (t[x][i] && !vst[i]) dfs(i, x);
}
void dfs2(int x, int p, int root) {
	if (x==root) t[x][pre[x]]=t[pre[x]][x]=0;
	else dfs2(pre[x], x, root);
	pre[x]=p; len[x]=e[x][p];
}

void conduct() {
	int i, j, k, l, s, ans, tmp;
	char str1[100], str2[100];
	scanf("%d", &m);
	memset(e, 0x7f, sizeof(e)); memset(t, 0, sizeof(t)); n=0;
	for (i=0; i<m; ++i) {
		scanf("%s%s%d", str1, str2, &tmp);
		for (j=0; j<n; ++j) if (!strcmp(str1, name[j])) break;
		if (j==n) strcpy(name[n++], str1);
		for (k=0; k<n; ++k) if (!strcmp(str2, name[k])) break;
		if (k==n) strcpy(name[n++], str2);
		e[j][k]=e[k][j]=getmin(e[j][k], tmp);
	}
	for (i=0; i<n; ++i) if (!strcmp("Park", name[i])) break;
	s=i; mst(s);
	scanf("%d", &i);
	while (i--) {
		memset(vst, 0, sizeof(vst));
		lst[s]=s; dfs(s, s);
		for (j=k=0; j<n; ++j) if (e[s][j]-len[lst[j]]<k) { l=j; k=e[s][j]-len[lst[j]]; }
		if (!k) break;
		dfs2(l, l, lst[l]); pre[l]=s; len[l]=e[s][l]; t[s][l]=t[l][s]=1;
	}
	for (ans=i=0; i<n; ++i) ans+=len[i];
	printf("Total miles driven: %d\n", ans);
}

int main() {
	conduct();
	return 0;
}
