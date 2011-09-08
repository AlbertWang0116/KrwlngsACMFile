#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;

#define N 1100
int ss[N], ter[N], fal[N], way[N][10], seq[10], tmp[10];
bool btr[N];
int n;

int cmp(const int &x, const int &y) { return (fal[tmp[x]]+2) * ter[tmp[y]] < (fal[tmp[y]]+2) * ter[tmp[x]]; }

void input()
{
	int i, pre; char state[10];
	for (i = 1; i <= n; ++i) way[i][0] = 0;
	for (i = 1; i <= n; ++i) {
		scanf("%d%s", &pre, state);
		if (state[0] == 'Y') btr[i] = true; else btr[i] = false;
		if (pre != -1) way[pre][++way[pre][0]] = i;
	}
}

void dfs(int x)
{
	int i, fs;
	if (!way[x][0]) { ter[x] = 1; return; }
	for (i = 1; i <= way[x][0]; ++i) dfs(way[x][i]);
	for (i = 1; i <= way[x][0]; ++i) { fal[x] += fal[way[x][i]] + 2; ter[x] += ter[way[x][i]]; }
	if (btr[x]) fal[x] = 0;
	for (i = 1; i <= way[x][0]; ++i) { seq[i] = i; tmp[i] = way[x][i]; } 
	std::sort(seq+1, seq+way[x][0]+1, cmp); fs = 0;
	for (i = 1; i <= way[x][0]; ++i) { 
		ss[x] += (fs+1) * ter[tmp[seq[i]]] + ss[tmp[seq[i]]]; 
		fs += fal[tmp[seq[i]]] + 2; 
	}
}

void conduct()
{
	memset(ss, 0, sizeof(ss)); memset(fal, 0, sizeof(fal)); memset(ter, 0, sizeof(ter));
	dfs(1);
	printf("%.4f\n", (double)ss[1]/ter[1]);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n) {
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

