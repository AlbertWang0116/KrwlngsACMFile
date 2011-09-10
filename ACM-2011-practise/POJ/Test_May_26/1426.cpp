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

struct node { int idx, pre, ori; };
#define N 1000
string ans[N];
node seq[N];
bool visit[N][2];
int n;

bool valid(int x)
{
	while (x > 0)
	{
		if (x % 10 > 1) return false;
		x /= 10;
	}
	return true;
}

string transstr(int x)
{
	string ret = "";
	while (x > 0)
	{
		ret = (char)(x % 10 + '0') + ret;
		x /= 10;
	}	
	return ret;
}

void init()
{
	int i, j, k, l, num;
	int next;
	for (i = 1; i <= 200; ++i)
	{
		if (valid(i)) { ans[i] = transstr(i); continue; } num = 0; ans[i] = "";
		if (i % 2 == 0) { next = i; while (next % 2 == 0) { next /= 2; ans[i] = ans[i] + '0'; } ans[i] = ans[next] + ans[i]; continue;}
		memset(visit, false, sizeof(visit));
		for (j = 1; j < i; ++j) if (valid(j)) { seq[num].idx = j; seq[num].pre = -1; visit[j][0] = true; visit[j][1] = true; num++; }
		for (j = 0; j < num; ++j)
		{
			for (l = 0; l < 2; ++l)
			{
				next = (seq[j].idx * 10 + l) % i; if (visit[next][l]) continue;
				seq[num].idx = next; seq[num].ori = l; seq[num].pre = j; visit[next][l] = true; num++;
			}
		}
		for (j = 0; j < num; ++j) if (seq[j].idx == 0) break;
//		printf("I:%d J:%d num:%d\n", i, j, num);
		while (true)
		{
			if (seq[j].pre == -1) { ans[i] = transstr(seq[j].idx) + ans[i]; break; }
			else { ans[i] = (char)(seq[j].ori + '0') + ans[i]; }
			j = seq[j].pre;
		}
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	init();
	while (scanf("%d", &n) != EOF && n) cout << ans[n] << endl;
//	fclose(stdin);
//	fclose(stdout);
}

