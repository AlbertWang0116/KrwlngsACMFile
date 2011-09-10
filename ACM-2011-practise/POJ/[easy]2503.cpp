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

#define N 100010
#define M 50
#define L 9997
char head[N][M], tail[N][M];
int node[L];
int next[N];

int gethash(char* str)
{
	int n = strlen(str);
	int i;
	int ret = 0;
	for (i = 0; i < n; ++i) ret = (ret * 26 + str[i] - 'a') % L;
	return ret;
}

void init()
{
	int idx, val;
	char input[M*3], st[M], ed[M];
	strcpy(tail[0], "eh");
	memset(node, 0, sizeof(node));
	idx = 1;
	while (true)
	{
		gets(input);
		if (strlen(input) == 0) break;
		sscanf(input, "%s %s", ed, st);
		strcpy(head[idx], st); strcpy(tail[idx], ed);
		val = gethash(st); next[idx] = node[val]; node[val] = idx; idx++;
	}
}

int main()
{
	int i, val;
	char st[M];
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	init();
	while (scanf("%s", st) != EOF)
	{
		val = node[gethash(st)];
		while (val) if (!strcmp(head[val], st)) break; else val = next[val];
		printf("%s\n", tail[val]);
	}
//	fclose(stdin);
//	fclose(stdout);
}

