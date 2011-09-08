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

#define square(x) (x)*(x)
struct pnt { double x, y; };
#define N 50010
const double eps = 1e-8;
const double MAX = 100000;
map<double, int> stt;
pnt p[N];
double px[2*N], r[N];
int seq[2*N];
int n;

int cmp(const int &x, const int &y) { return px[x] - px[y] < -eps; }

bool crs(int i, int j, double ext)
{
//	printf("i:%d j:%d ext:%.3f\n", i, j, ext);
	if (square(p[i].x-p[j].x) + square(p[i].y-p[j].y) - square(r[i]+r[j]+2*ext) < 1e-16) return true; return false;
}

void input()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &r[i]);
}

bool judge(double ext)
{
	int i;
	map<double, int>::iterator pos, lft, rit;
	stt.clear();
	for (i = 0; i < 2*n; ++i)
		if (seq[i]%2) {
			pos = stt.find(p[seq[i]/2].y); lft = rit = pos; if (pos != stt.begin()) lft--; rit++;
			if (pos != stt.begin() && rit != stt.end() && crs(lft->second, rit->second, ext)) return true;
			stt.erase(pos);
		} else {
			if (stt.find(p[seq[i]/2].y) != stt.end()) return true;
			stt.insert(pair<double, int>(p[seq[i]/2].y, seq[i]/2));
			pos = stt.find(p[seq[i]/2].y); lft = pos; rit = pos; if (pos != stt.begin()) lft--; rit++;
			if (pos != stt.begin() && crs(pos->second, lft->second, ext)) return true; 
			if (rit != stt.end() && crs(pos->second, rit->second, ext)) return true; 
		}
	return false;
}

void conduct()
{
	int i; double lft, rit, mid;
	for (i = 0; i < n; ++i) { px[i*2] = p[i].x - r[i]; px[i*2+1] = p[i].x + r[i]; }
	for (i = 0; i < 2*n; ++i) seq[i] = i; std::sort(seq, seq+2*n, cmp);
	lft = 0.0; rit = MAX;
	while (rit - lft > eps) {
		mid = (rit + lft) / 2;
		for (i = 0; i < n; ++i) { px[i*2] = p[i].x - r[i] - mid; px[i*2+1] = p[i].x + r[i] + mid; }
		for (i = 0; i < 2*n; ++i) seq[i] = i; std::sort(seq, seq+2*n, cmp);
		if (judge(mid)) rit = mid; else lft = mid;
	}
	printf("%.6f\n", lft * 2);
}

int main()
{
	int time; scanf("%d", &time);
	while (time--) { input(); conduct(); }
	return 0;
}
