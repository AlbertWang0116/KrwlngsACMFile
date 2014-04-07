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

struct edge { int src, des, len; };
#define N 110
#define M 11000
edge e[M];
int seq[M], root[N];
int n, m;

inline int getmin(int x, int y) { return x<y?x:y; }

int cmp(const int &i, const int &j) { return e[i].len<e[j].len; }

int get_root(int x) { if (root[x]==x) return x; else return root[x]=get_root(root[x]); }
int merge_root(int x, int y) { root[get_root(x)]=get_root(y); }

int construct(int n, int id) {
	int i, j;
	for (i=0; i<N; ++i) root[i]=i;
	for (i=1, j=id; i<n; ++i) {
		for (; j<m; ++j) if (get_root(e[seq[j]].src)!=get_root(e[seq[j]].des)) break;
		if (j<m) merge_root(e[seq[j]].src, e[seq[j]].des); else return -1;
	}
	return e[seq[j]].len-e[seq[id]].len;
}

int kruskal(int n, int m) {
	int i, j, tmp, ret;
	for (i=0; i<m; ++i) seq[i]=i; sort(seq, seq+m, cmp);
	ret=construct(n, 0); if (!~ret) return ret;
	for (i=j=0; j<m; i=j) {
		for (; j<m && e[seq[j]].len==e[seq[i]].len; ++j);
		tmp=construct(n, j); 
		if (!~tmp) return ret; else ret=getmin(ret, tmp);
	}
	return ret;
}

void conduct() {
	int i;
	for (i=0; i<m; ++i) scanf("%d%d%d", &e[i].src, &e[i].des, &e[i].len);
	printf("%d\n", kruskal(n, m));
}

int main() {
	while (scanf("%d%d", &n, &m)!=EOF && (n||m)) conduct();
	return 0;
}
