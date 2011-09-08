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

#define N 110
int cmd[N], t1[N], t2[N], p1[N], p2[N];
int n1, n2, n, cs;

int getmax(int x, int y) { return x > y ? x : y;}

void input()
{
	int i, y;
	char x;
	scanf("%d", &n);
	n1 = 0; n2 = 0; t1[0] = 0; t2[0] = 0;
	for (i = 0; i < n; ++i)
	{
		scanf(" %c %d", &x, &y);
		if (x == 'O') { cmd[i] = 1; p1[++n1] = y;}
		else { cmd[i] = 2; p2[++n2] = y;}
//		printf("%c %d\n", x, y);
	}
}

void conduct()
{
	int c1, c2, ans, pos, i;
	for (pos = 1, i = 1; i <= n1; ++i) {t1[i] = t1[i-1] + abs(pos-p1[i]) + 1; pos = p1[i];}
	for (pos = 1, i = 1; i <= n2; ++i) {t2[i] = t2[i-1] + abs(pos-p2[i]) + 1; pos = p2[i];}
	c1 = 1; c2 = 1;
	for (i = 0; i < n; ++i)
		if (cmd[i] == 1)
		{
			if (c2 <= n2 && t1[0] + t1[c1] >= t2[0] + t2[c2]) t2[0] = t1[0] + t1[c1] + 1 - t2[c2];
			c1++;
		}
		else
		{
			if (c1 <= n1 && t2[0] + t2[c2] >= t1[0] + t1[c1]) t1[0] = t2[0] + t2[c2] + 1 - t1[c1];
			c2++;
		}
	ans = getmax(t1[0] + t1[n1], t2[0] + t2[n2]);
	cout << "Case #" << cs << ": " << ans << endl;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	for (cs = 1; cs <= time; ++cs)
	{
		input();
		conduct();
	}
	fclose(stdin);
	fclose(stdout);
}

