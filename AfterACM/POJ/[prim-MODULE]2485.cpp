#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<string>
using namespace std;

struct edge { int nxt, des, len; };
struct node {
	int u, len;
	node(int _u, int _len) { u=_u; len=_len; }
	int operator<(const node &item) const {
		if (len==item.len) return u<item.u;
		else return len<item.len;
	}
};
#define N 510
#define M 1100000
edge e[M];
int hd[N], len[N], vst[N], pre[N];
int n, m, cnt;

int getmax(int x, int y) { return x>y?x:y; }

void insert(int i, int j, int k) {
	++cnt; e[cnt].des=j; e[cnt].len=k; e[cnt].nxt=hd[i]; hd[i]=cnt;
}

int prim(int s, int n) {
	int i, u, v;
	memset(len, 0x7f, sizeof(len)); memset(vst, 0, sizeof(vst)); len[s]=0; pre[s]=s;
	set<node> que; que.clear(); que.insert(node(s, len[s]));
	while (n-- && !que.empty()) {
		u=que.begin()->u; que.erase(que.begin()); vst[u]=1;
		for (i=hd[u]; i; i=e[i].nxt) if (!vst[v=e[i].des] && len[v]>e[i].len) {
			que.erase(node(v, len[v])); len[v]=e[i].len; pre[v]=u; que.insert(node(v, len[v]));
		}
	} return n;
}

void conduct() {
	int i, j, k, ans;
	scanf("%d", &n);
	memset(hd, 0, sizeof(hd)); cnt=0;
	for (i=0; i<n; ++i) for (j=0; j<n; ++j) {
		scanf("%d", &k); insert(i, j, k);
	}
	prim(0, n);
	for (ans=i=0; i<n; ++i) ans=getmax(ans, len[i]);
	printf("%d\n", ans);
}

int main() {
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
