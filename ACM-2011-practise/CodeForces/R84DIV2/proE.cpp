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

struct node { int d, w, next; };
#define N 200010
long long g1[N], g2[N];
long long ans;
node w[N];
bool vst[N];
int rd[N];
int n, rc;

void insert(int st, int ed, int wi) {
	++rc; w[rc].d = ed; w[rc].w = wi; w[rc].next = rd[st]; rd[st] = rc;
}

bool judge(int x) {
	while (x) { if (x % 10 != 4 && x % 10 != 7) return false; x /= 10; }
	return true;
}

void dfs(int x) {
	int i; vst[x] = 1;
	for (i = rd[x]; i; i = w[i].next) if (!vst[w[i].d]) {
		dfs(w[i].d);
		if (judge(w[i].w)) {
			g1[x] += g1[w[i].d] + g2[w[i].d] + 1;
		} else {
			g1[x] += g1[w[i].d];
			g2[x] += g2[w[i].d] + 1;
		}
	} vst[x] = 0;
}

void dfs2(int x, long long val1, long long val2, long long val3, bool valid) {
	long long tv, tg; int i;
	tv = g1[x]; vst[x] = 1;
//	printf("x:%d val1:%lld val2:%lld val3:%lld\n", x, val1, val2, val3);
	if (valid) { val1 += val2; val2 = val3 = 0; }
	tv += val1 + val3; ans += tv * (tv-1);
//	printf("x:%d g1:%lld tv:%lld\n", x, g1[x], tv);
	for (i = rd[x]; i; i = w[i].next) if (!vst[w[i].d]) {
		if (judge(w[i].w)) tg = g1[w[i].d] + g2[w[i].d] + 1; else tg = g1[w[i].d];
		dfs2(w[i].d, val1, val2+g1[x]+g2[x]-g1[w[i].d]-g2[w[i].d], val3+g1[x]-tg, judge(w[i].w));
	} vst[x] = 0;
}

int main()
{
	int i, st, ed, wi;
	scanf("%d", &n);
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 0; i < n-1; ++i) {
		scanf("%d%d%d", &st, &ed, &wi); --st; --ed;
		insert(st, ed, wi); insert(ed, st, wi);
	} for (i = 0; i < n; ++i) g1[i] = g2[i] = 0;
	memset(vst, 0, sizeof(vst));
	ans = 0; dfs(0); dfs2(0, 0, 0, 0, 0); cout << ans << endl;
}
