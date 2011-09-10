#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

struct node { int val, pos, pre, idx, pv; };
#define N 1010
#define MAX 100000000
#define M 5000010
int way[N][N], ati[N][N], dis1[N][N], dis2[N][N], lst[N];
node heap[M];
bool vst[N];
int n, m, num, rch, st, ed, len;

void input()
{
	int i, j;
	scanf("%d %d", &n, &m);
	memset(way, 0, sizeof(way)); memset(ati, 0, sizeof(ati));
	for (i = 0; i < m; ++i)
	{
		scanf("%d %d %d", &st, &ed, &len);
		way[st][0]++; ati[ed][0]++;
		way[st][way[st][0]] = ed; dis1[st][way[st][0]] = len;
		ati[ed][ati[ed][0]] = st; dis2[ed][ati[ed][0]] = len;
	}
	scanf("%d %d %d", &st, &ed, &len);
//	if (st == ed) len++;
}

int cmp(int x, int y) { if (x > y) return 1; if (x < y) return -1; return 0; }

void dijkstra()
{
	int i, j, k;
	for (i = 1; i <= n; ++i) lst[i] = MAX; lst[ed] = 0;
	for (i = 1; i <= ati[ed][0]; ++i) if (lst[ati[ed][i]] > dis2[ed][i]) lst[ati[ed][i]] = dis2[ed][i];
	memset(vst, false, sizeof(vst)); vst[ed] = true;
	while (true)
	{
		j = 0; k = MAX;
		for (i = 1; i <= n; ++i) if (!vst[i] && lst[i] < k) { j = i; k = lst[i]; }
		if (!j) break; vst[j] = true;
		for (i = 1; i <= ati[j][0]; ++i) if (!vst[ati[j][i]] && lst[ati[j][i]] > lst[j] + dis2[j][i]) lst[ati[j][i]] = lst[j] + dis2[j][i];
	}
}

void downheap(int idx)
{
	if (idx == 1) return;
	if (heap[idx].val < heap[idx/2].val) { swap<node>(heap[idx], heap[idx/2]); downheap(idx/2);}
}

void upheap(int idx, int mst)
{
	int idx2;
	if (idx*2 > mst) return;
	if (idx*2+1 > mst || heap[idx*2].val < heap[idx*2+1].val) idx2 = idx*2; else idx2 = idx*2+1;
	if (heap[idx].val > heap[idx2].val) { swap<node>(heap[idx], heap[idx2]); upheap(idx2, mst); }
}

void insert(node add)
{
	if (add.pos == -1) return;
	heap[++num] = add;
	downheap(num);
}

void remove()
{
	heap[1] = heap[num--];
	upheap(1, num);
}

void getsort(int* a, int* b, int x, int y)
{
	if (x >= y) return;
	int i, j;
	int k, l;
	i = rand() % (y-x) + x;
	k = a[i]; l = b[i];
	a[i] = a[x]; b[i] = b[x];
	i = x; j = y;
	while (i < j)
	{
		while (i < j && cmp(b[j]+lst[a[j]], l+lst[k]) >= 0) --j;
		a[i] = a[j]; b[i] = b[j];
		while (i < j && cmp(b[i]+lst[a[i]], l+lst[k]) <= 0) ++i;
		a[j] = a[i]; b[j] = b[i];
	}
	a[i] = k; b[i] = l;
	getsort(a, b, x, i-1);
	getsort(a, b, j+1, y);
}

node getnode(int pos, int val, int idx)
{
	node ret;
//	printf("before: pos:%d val:%d idx:%d\n", pos, val, idx);
	if (way[pos][0] < idx) { ret.pos = -1; return ret; }
	ret.pos = way[pos][idx];
	ret.val = val - lst[pos] + dis1[pos][idx] + lst[ret.pos];
	ret.pre = pos;
	ret.pv = val;
	ret.idx = idx;
//	printf("after: pos:%d val:%d idx:%d\n", ret.pos, ret.val, ret.idx);
	return ret;
}

void conduct()
{
	int i, j;
	node ele, add;
	dijkstra();
	for (i = 1; i <= n; ++i) { getsort(way[i], dis1[i], 1, way[i][0]); while (way[i][0] > 0 && dis1[i][way[i][0]] == MAX) --way[i][0]; }
//	for (i = 1; i <= n; ++i)
//		for (j = 1; j <= way[i][0]; ++j) printf("st:%d ed:%d len:%d\n", i, way[i][j], dis1[i][j]);
	num = 0; rch = 0; add = getnode(st, lst[st], 1); insert(add);
	while (num > 0)
	{
		ele = heap[1]; remove(); rch++; if (rch == len) break;
//		printf("pos:%d val:%d\n", ele.pos, ele.val);
		add = getnode(ele.pre, ele.pv, ele.idx+1); insert(add);
		while (true)
		{
			if (ele.pos == ed) { add = getnode(ele.pos, ele.val, 1); insert(add); break; }
			else { add = getnode(ele.pos, ele.val, 2); ele = getnode(ele.pos, ele.val, 1); insert(add);}
		}
	}
	if (rch == len) printf("%d\n", ele.val);
	else printf("-1\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

