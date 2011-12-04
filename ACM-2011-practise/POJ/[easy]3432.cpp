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

struct pnt {
	int x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const int c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const int c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	} bool operator<(const pnt &p) const {
		if (x == p.x) return y < p.y;
		return x < p.x;
	}
};
typedef pnt vec;
#define N 2010
pnt p[N];
map<pnt, int> hsh;
int n;

bool check(const pnt &p1, const pnt &p2) {
	vec v1 = p2-p1, v2 = {-v1.y, v1.x}, v3 = v1 + v2;
	if (hsh.find(p1+v2) == hsh.end()) return 0;
	if (hsh.find(p1+v3) == hsh.end()) return 0;
	return 1;
}

void conduct() {
	int i, j, ret;
	hsh.clear();
	for (i = 0; i < n; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		hsh.insert(pair<pnt, int>(p[i], i));
	} for (ret = i = 0; i < n; ++i) for (j = 0; j < n; ++j) 
		if (i != j && check(p[i], p[j])) ret++;
	printf("%d\n", ret/4);
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
