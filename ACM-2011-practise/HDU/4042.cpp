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

void conduct()
{
	for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y); p[n] = p[0];
	for (i = 0; i < m; ++i) scanf("%lf%lf", &q[i].x, &q[i].y); q[m] = q[0];
	ver1 = submul(getvec(p[0], p[1]), getvec(p[0], p[2]));
	ver2 = submul(getvec(q[0], q[1]), getvec(q[0], q[2]));
	ori = submul(ver1, ver2); d1 = nummul(ver1, p[0]); d2 = nummul(ver2, q[0]);
	if (len(ori) < eps) {
		if (fabs(d1-d2) > eps) { printf("NO\n"); return; }
		for (i = 0; i < n; ++i) for (j = 0; j < m; ++j) 
			if (checkcrs(p[i], p[i+1], q[i], q[i+1])) { printf("YES\n"); return; }
	} else {
		tmp1 = submul(ori, ver1); t = (d2 - nummul(ver2, p[0])) / nummul(ver2, tmp1);
		org = p[0] + tmp1 * t;
		for (i = s1[0] = 0; i < n; ++i) {
			tmp1 = submul(getvec(org, p[i]), ori); tmp2 = submul(getvec(org, p[i+1]), ori);
			if (nummul(tmp1, tmp2) > eps) continue;
			tmp1 = getvec(p[i+1], p[i]); if (len(submul(ori, tmp1)) < eps) continue;
				

int main()
{
	while (scanf("%d%d", &n, &m) != EOF) conduct();
	return 0;
}
