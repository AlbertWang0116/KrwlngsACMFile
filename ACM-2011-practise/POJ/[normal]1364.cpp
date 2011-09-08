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
#define N 110
#define M 1010
node way[M];
int rd[N], seq[N], pre[N], dis[N];
bool vst[N], tmp[N], tag[N];
int n, m, rc;
const int MAX = LONG_MAX;

void input()
{
	int i, s, l, val;
	char cmd[10];
	scanf("%d", &m);
	memset(rd, 0, sizeof(rd)); rc = 0;
	for (i = 0; i < m; ++i) {
		scanf("%d%d%s%d", &s, &l, cmd, &val);
		if (cmd[0] == 'g') { ++rc; way[rc].d = s-1; way[rc].l = -val-1; way[rc].next = rd[s+l]; rd[s+l] = rc; }
		else { ++rc; way[rc].d = s+l; way[rc].l = val-1; way[rc].next = rd[s-1]; rd[s-1] = rc; }
	}
}

bool spfa(int s)
{
	int i, head, tail, cnt, v, u;
	for (i = 0; i <= n; ++i) vst[i] = tag[i]; cnt = 1;
	for (i = 0; i <= n; ++i) dis[i] = MAX; dis[s] = 0; pre[s] = 0;
	for (seq[head = tail = 0] = s; cnt; cnt--, head = (head+1) % N) {
		u = seq[head]; vst[u] = false; if (pre[u] > n) return false;
		for (i = rd[u]; i; i = way[i].next) if (dis[way[i].d] > dis[u] + way[i].l) {
			v = way[i].d; if (!vst[v]) { cnt++; vst[v] = tmp[v] = true; seq[tail = (tail+1) % N] = v; }
			dis[v] = dis[u] + way[i].l; pre[v] = pre[u] + 1;
		}
	}
	return true;
}

void conduct()
{
	int i, j;
	memset(tag, 0, sizeof(tag)); memset(tmp, 0, sizeof(tmp));
	for (i = 0; i <= n; ++i) {
		if (!tag[i] && !spfa(i)) break;
		for (j = 0; j <= n; ++j) tag[j] = tmp[j];
	}
	if (i <= n) printf("successful conspiracy"); else printf("lamentable kingdom");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	bool again = false;
	while (scanf("%d", &n) != EOF && n) { 
		if (again) printf("\n"); else again = true;
		input(); conduct(); 
	}
//	fclose(stdin);
//	fclose(stdout);
}

