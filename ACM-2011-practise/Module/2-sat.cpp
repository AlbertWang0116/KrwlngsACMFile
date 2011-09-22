//The meaning of the edge(u->v) means u must be chosen before v is chosen.
struct node { int des, next; };
struct edge { int st, ed; };
#define N 10010
#define M 1000010
node way[M];
edge e[M];
int rd[N], seq[N], col[N], pre[N], cpn[N];
bool vst[N], use[M], chs[N];
int n, cnt, cc, rc;

void dfs(int x)
{
	int i;
	vst[x] = true;
	for (i = rd[x]; i; i = way[i].next) if (!vst[way[i].des]) dfs(way[i].des);
	seq[++cnt] = x;
}

void dfs2(int x, int c)
{
	int i;
	vst[x] = true; col[x] = c;
	for (i = rd[cpn[x]]; i; i = way[i].next) if (!vst[cpn[way[i].des]]) dfs2(cpn[way[i].des], c);
}

void release(int x)
{
	int i;
	vst[x] = true; vst[cpn[x]] = true; chs[x] = true; chs[cpn[x]] = false; cc += 2;
	for (i = rd[x]; i; i = way[i].next) pre[way[i].des]--;
}

void twosat()
{
	int i;
	//judge section
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = 1; i <= n; ++i) if (!vst[i]) dfs(i);
	memset(vst, false, sizeof(vst)); cnt = 0;
	for (i = n; i > 0; --i) if (!vst[seq[i]]) dfs2(seq[i], ++cnt);
	for (i = 1; i <= n; ++i) if (col[i] == col[cpn[i]]) { printf("NO\n"); return; } printf("YES\n");
	//output section
	for (i = 1; i <= n; ++i) seq[col[i]] = col[cpn[i]]; for (i = 1; i <= cnt; ++i) cpn[i] = seq[i];
	memset(use, true, sizeof(use));
	for (i = 1; i <= rc; ++i) if (col[e[i].st] == col[e[i].ed]) use[i] = false; 
	else { e[i].st = col[e[i].st]; e[i].ed = col[e[i].ed]; }
	memset(rd, 0, sizeof(rd)); memset(pre, 0, sizeof(pre));
	for (i = 1; i <= rc; ++i) if (use[i]) { way[i].des = e[i].ed; way[i].next = rd[e[i].st]; rd[e[i].st] = i; pre[e[i].ed]++; }
	memset(vst, false, sizeof(vst)); cc = 0;
	while (cc < cnt) for (i = 1; i <= cnt; ++i) if (!vst[i] && !pre[i]) release(i);
	for (i = 1; i <= n; ++i) if (chs[col[i]]) printf("%d ", i); printf("\n");
}
