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

struct pnt { 
	int x, y; 
	pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	}
};
typedef pnt vec;
#define N 24
#define M 1 << N
#define L N+10
int next[M], val[M], pre[M];
int bit[L], dis[L][L], rd[L];
pnt p[L], cen;
map<int, int> hash;
int n;

int nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }

void insert(int i, int j) {
	next[j] = rd[i]; rd[i] = j;
}

void conduct()
{
	int i, j, k, l, cur, pos, ans, tv;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) { scanf("%d%d", &p[i].x, &p[i].y); p[i] = p[i] - cen; }
	memset(dis, 0, sizeof(dis));
	for (i = 0; i < n; ++i) for (j = i+1; j < n; ++j) dis[i][j] = dis[j][i] = nummul(p[i], p[j]);
	hash.clear(); hash[1] = 0; bit[0] = 1;
	for (i = j = 1; i <= n; ++i) { j *= 2; hash[j] = i; bit[i] = j;}
	memset(rd, -1, sizeof(rd)); insert(0, 0);
	memset(val, -1, sizeof(val)); memset(pre, -1, sizeof(pre));
	for (val[0] = pre[0] = i = 0; i < n; ++i) for (j = rd[i]; j >= 0; j = next[j]) 
		for (cur = bit[n]-j-1; (pos = cur & -cur); cur = cur ^ pos) {
			k = hash[pos]; l = j|bit[i]|pos; tv = val[j] + dis[i][k];
//			printf("now:"); for (ans = 0; ans < n; ++ans) if (i & bit[ans]) printf("1"); else printf("0"); printf("\n");
//			printf("pro:"); for (ans = 0; ans < n; ++ans) if (l & bit[ans]) printf("1"); else printf("0"); printf("\n");
//			printf("%d->%d val:%d tv:%d\n", i, k, val[l], tv);
			if (tv > val[l]) {
				if (val[l] < 0) { k = bit[n]-l-1; k = k & -k; insert(hash[k], l); }
				val[l] = tv; pre[l] = bit[i]|pos;
			}
		}
	for (ans = i = 0; i < n; ++i) ans += nummul(p[i], p[i]); ans = (ans-val[bit[n]-1])*2;
	printf("%d\n", ans);
	for (i = bit[n]-1; i; i = i ^ pre[i]) {
		printf("0 "); for (j = 0; j < n; ++j) if (bit[j] & pre[i]) printf("%d ", j+1);
	} printf("0\n");
}

int main()
{
	while (scanf("%d%d", &cen.x, &cen.y) != EOF) conduct();
	return 0;
}
