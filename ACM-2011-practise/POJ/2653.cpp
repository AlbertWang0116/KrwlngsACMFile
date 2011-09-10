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

void input()
{
	for (int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y, &q[i].x, &q[i].y);
}

void conduct()
{
	evt.clear(); seg.clear(); memset(cov, 0, sizeof(cov));
	for (i = 1; i <= n; ++i) if (q[i] < p[i]) { ptmp = p[i]; p[i] = q[i]; q[i] = ptmp; }
	for (i = 1; i <= n; ++i) {
		pos = evt.find(p[i]); if (pos == evt.end()) pos = evt.insert(pair<pnt, node>(p[i], dft)).first;
		snext[i] = pos->second.s; pos->second.s = i;
		pos = evt.find(q[i]); if (pos == evt.end()) pos = evt.insert(pair<pnt, node>(q[i], dft)).first;
		tnext[i] = pos->second.t; pos->second.t = i;
	}
	while (evt.size()) {
		pos = evt.begin(); info = pos->second; evp = pos->first;
		if (info.c) {
			cur = seg.find(info.c); lft = rit = cur; cl[0] = 0;
			while (lft != seg.begin()) { lft--; if (fabs(oridis(l[lft->first], evp))<eps) cl[++cl[0]] = lft->first; else break; }
			while (rit != seg.end() && fabs(oridis(l[rit->first], evp))<eps) { cl[++cl[0]] = rit->first; rit++; }
		} else cl[0] = 0;
		mst = 0;
		for (i = info.s; i; i = snext[i]) if (i < mst) cov[i] = true; else { cov[mst] = true; mst = i; }
		for (i = 1; i <= cl[0]; ++i) if (cl[i] < mst) cov[cl[i]] = true; else { cov[mst] = true; mst = cl[i]; }
		for (if (fabs(oridis(l[lft->first], evp))>eps) lft++; lft != rit; ) { cur = lft; lft++; seg.erase(cur); }
		mst = info.s; lst = info.s; pmst = plst = seg.insert(pair<int, int>(info.s, 0)).first;
		for (i = snext[info.s]; i; i = snext[i]) {


int main()
{
	while (scanf("%d", &n) != EOF && n) { input(); conduct(); }
	return 0;
}
