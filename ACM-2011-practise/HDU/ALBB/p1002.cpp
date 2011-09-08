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

#define getmax(x, y) (x)>(y)?(x):(y)
struct pnt { int x, y; };
typedef pnt vec;
#define N 20
int pc[N];
bool val[N];
pnt p[N][N];
int n;

void input()
{
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &pc[i]);
		for (j = 0; j < pc[i]; ++j) scanf("%d%d", &p[i][j].x, &p[i][j].y);
		p[i][pc[i]] = p[i][0];
	}
}

vec getvec(pnt p1, pnt p2)
{
	vec ret; ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y; return ret;
}

int submul(vec v1, vec v2)
{
	int val = v1.x * v2.y - v2.x * v1.y;
	if (val > 0) return 1; else if (val < 0) return 2; return 0;
}

void conduct()
{
	int i, j, k, l, u, v, ans, cnt;
	vec stt;
	ans = 1;
	for (i = 1; i < n && ans < n; ++i) for (j = i+1; j <= n && ans < n; ++j)
		for (k = 0; k < pc[i]; ++k) for (l = 0; l < pc[j]; ++l) {
			cnt = 0; stt = getvec(p[i][k], p[j][l]);
			for (v = 1; v <= n; ++v) if (v == i || v == j) cnt++; else {
				memset(val, 0, sizeof(val));
				for (u = 0; u < pc[v]; ++u) val[submul(stt, getvec(p[i][k], p[v][u]))] = true;
				if (val[0]) cnt++; else if (val[1] && val[2]) cnt++;
			}
			ans = getmax(ans, cnt);
		}
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	for (int i = 1; i <= time; ++i) {
		printf("Case %d: ", i);
		input(); conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

