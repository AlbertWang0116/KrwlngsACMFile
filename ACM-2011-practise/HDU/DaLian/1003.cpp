#pragma comment(linker, "/STACK:1024000000,1024000000")
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

struct node { int d, l, next; };
#define N 20010
node w[N];
int s1[N], s2[N], rd[N], pc[N], v[N], u[N];
bool lrt[N], vst[N];
int n, rt, rbt, tot, rc, lc;

void input()
{
	int i, st, ed, len;
	memset(rd, 0, sizeof(rd)); memset(pc, 0, sizeof(pc)); rc = 0;
	for (i = 0; i < n-1; ++i) {
		scanf("%d%d%d", &st, &ed, &len);
		rc++; w[rc].d = ed; w[rc].l = len; w[rc].next = rd[st]; rd[st] = rc; pc[st]++;
		rc++; w[rc].d = st; w[rc].l = len; w[rc].next = rd[ed]; rd[ed] = rc; pc[ed]++;
	}
}

int dfs(int x, int up)
{
	int tmp, tot, i;
//	printf("x:%d", x);
	vst[x] = true;
	if (x == rt || pc[x] > 2) lrt[x] = true; else lrt[x] = false;
//	printf("lrt:%d\n", lrt[x]);
	if (x != rt && pc[x] == 1) return 0; tot = 0;
	for (i = rd[x]; i; i = w[i].next) if (!vst[w[i].d]) {
		tmp = dfs(w[i].d, up+w[i].l); tot += tmp + w[i].l;
		if (lrt[w[i].d]) lrt[x] = true;
		if (lrt[x] && !lrt[w[i].d]) { v[lc] = tmp + w[i].l; u[lc] = up; ++lc;}
	} return tot;
}

int cmp1(const int &x, const int &y) { return v[x]+u[x] > v[y]+u[y]; }
int cmp2(const int &x, const int &y) { return v[x]-u[x] > v[y]-u[y]; }

void conduct()
{
	int i, j, ans[11];
	if (n == 1) { printf("0\n"); return; }
	lc = 0; memset(vst, 0, sizeof(vst)); tot = dfs(rt, 0);
	for (i = 0; i < n; ++i) s1[i] = s2[i] = i;
	sort(s1, s1+lc, cmp1); sort(s2, s2+lc, cmp2);
//	printf("lc:%d\n", lc);
//	for (i = 0; i < lc; ++i) printf("lc:%d v:%d u:%d\n", i, v[i], u[i]);
	memset(vst, 0, sizeof(vst));
	ans[0] = tot * 2; ans[1] = ans[0] - (v[s1[0]] + u[s1[0]]); vst[s1[0]] = true;
	if (lc == 1) { printf("%d\n", ans[1]); return; }
	if (s1[0] == s2[0])
		if (v[s1[0]]+u[s1[0]]+v[s2[1]]-u[s2[1]] > v[s1[1]]+u[s1[1]]+v[s2[0]]-u[s2[0]]) {
			vst[s2[1]] = true; ans[2] = ans[0] - (v[s1[0]]+u[s1[0]]+v[s2[1]]-u[s2[1]]);
		} else { vst[s1[1]] = true; ans[2] = ans[0] - (v[s1[1]]+u[s1[1]]+v[s2[0]]-u[s2[0]]); }
	else { vst[s2[0]] = true; ans[2] = ans[1] - (v[s2[0]] - u[s2[0]]); }
	for (i = 0, j = 2; j < rbt;) {
		if (vst[s2[i]]) i++;
		else if (i == lc || v[s2[i]] - u[s2[i]] <= 0) { ans[j+1] = ans[j]; j++; }
		else { ans[j+1] = ans[j] - (v[s2[i]] - u[s2[i]]); i++; j++; }
	} printf("%d\n", ans[rbt]);
}
		

int main()
{
	while (scanf("%d%d%d", &n, &rt, &rbt) != EOF) { input(); conduct(); }
	printf("\n");
	return 0;
}
