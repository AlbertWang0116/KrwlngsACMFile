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

struct pnt { double x, y; };
#define N 1010
const double eps = 1e-8;
const int P = 500, Q = 501;
pnt p[N], q[N], tmp[N];
int n, m;

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (i = 0; i < m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y);
}

pnt gravity(int st, int ed) 
{
	pnt ret; return ret;
}

void conduct()
{
	int pos, i, j;
	pnt last, gp, fp, cp, np, fq, cq, nq;
	fp = p[0]; fq = q[0]; cp = fp; cq = fq;
	np = p[1]; nq = q[1]; i = 1; j = 1;
	tmp[P] = p[0]; tmp[Q] = q[0]; last.x = (p[0].x + q[0].x) / 2; last.y = 0;
	for (pos = 1;; ++pos) {
		if (np.y < nq.y) {
			fp = cp; fq = cq; cp = np; cq.y = cp.y;
			cq.x = (np.y-fq.y) * (nq.x-fq.x) / (nq.y-fq.y);
			np = p[++i];
		} else {
			fp = cp; fq = cq; cq = nq; cp.y = cq.y;
			cp.x = (nq.y-fp.y) * (np.x-fp.x) / (np.y-fp.y);
			nq = q[++j];
		}
		tmp[P-pos] = cp; tmp[Q+pos] = cq;
		gp = gravity(P-pos, Q+pos+1);
		if (gp.x - p[0].x < -eps) { printf("%.3f\n", fp.y+(cp.y-fp.y)*(last.x-p[0].x)/(last.x-gp.x)); return; }
		if (gp.x - q[0].x > eps) { printf("%.3f\n", fp.y+(cp.y-fp.y)*(q[0].x-last.x)/(gp.x-last.x)); return; }
		if (i == n || j == m) { printf("%.3f\n", cp.y); return; }
		last = gp;
	}
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF) { input(); conduct(); }
	return 0;
}
