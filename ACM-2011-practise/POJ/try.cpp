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
#define N 1010
const double eps = 1e-9;
struct pnt {
	double x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
};
typedef pnt vec;
int n;
pnt p[N];
vec v[N];
double len[N];

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }
double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

vec uvec(const vec &v) {
	double len = sqrt(square(v.x)+square(v.y));
	return v / len;
}

pnt stretch_rotate(const pnt &p, const vec &v1, const vec &v2) {
	vec v = { submul(v1, v2)/nummul(v1, v1), nummul(v1, v2)/nummul(v1, v1) };
	pnt ret = { submul(p, v), nummul(p, v) }; return ret;
} 

void conduct()
{
	int i, j, itr;
	pnt mst, lst, ret;
	vec v1, tv;
	double len1, tl, rat;
	scanf("%d", &n); for (i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	scanf("%d", &itr); scanf("%lf", &rat);
	len1 = getdis(p[0], p[n-1]); v1 = p[n-1] - p[0];
	for (i = 0; i < n; ++i) v[i] = p[i] - p[0];
	for (len[0] = 0, i = 1; i < n; ++i) len[i] = len[i-1] + getdis(p[i], p[i-1]);
	for (i = 0; i < n; ++i) len[i] /= len[n-1];
//	printf("v --> \n"); for (i = 0; i < n; ++i) printf("%.3f,%.3f\n", v[i].x, v[i].y);
//	printf("l --> "); for (i = 0; i < n; ++i) printf("%.3f ", len[i]); printf("\n");
	for (lst = p[0], mst = p[n-1], i = 0; i < itr; ++i) {
		for (j = 1; j < n; ++j) if (rat-len[j] < eps) break; 
		tl = getdis(lst, mst); tv = mst - lst;
		mst = lst + stretch_rotate(v[j], v1, tv); lst = lst + stretch_rotate(v[j-1], v1, tv);
		rat = (rat - len[j-1]) / (len[j] - len[j-1]);
	} ret = lst + (mst-lst) * rat; printf("(%.10f,%.10f)\n", ret.x, ret.y);
}

	 

int main()
{
	int time; scanf("%d", &time);
	while (time--) conduct();
	return 0;
}
