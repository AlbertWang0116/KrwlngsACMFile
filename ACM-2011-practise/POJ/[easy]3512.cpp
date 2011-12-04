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
	long long x, y;
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	} pnt operator*(const long long c) const {
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	} pnt operator/(const long long c) const {
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	} bool operator<(const pnt &p) const {
		if (x == p.x) return y < p.y;
		 return x < p.x;
	}
};
typedef pnt vec;
#define N 1010
pnt p[N];
vec v[N];
int seq[N];
int n;
char str[N];

long long submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

int getmax( int x, int y) { return x > y ? x : y; }
int cmp(const int &i, const int &j) { return submul(v[i], v[j]) > 0; }

bool input() {
	n = 0;
	while (true) {
		gets(str);
		if (str[0] == '-' && str[1] == '-') return n;
		sscanf(str, "%lld%lld", &p[n].x, &p[n].y); n++;
	}
}

void conduct() {
	int i, j, k, ret, cnt;
	sort(p, p+n);
	for (ret = i = 0; i < n;) {
		for (cnt = 1, ++i; i < n && !(p[i-1]<p[i]); ++cnt, ++i);
		for (j = i; j < n; ++j) v[j-i] = p[j]-p[i-1];
		for (j = 0; j < n-i; ++j) seq[j] = j; sort(seq, seq+n-i, cmp);
		for (j = 0; j < n-i; ) {
			for (k = j+1; k < n-i && !cmp(seq[j], seq[k]); ++k);
			ret = getmax(ret, k-j+cnt); j = k;
		}
	} printf("%d\n", ret);
}

int main() {
	int time = 0;
	while (true) {
		if (!input()) break;
		printf("%d. ", ++time);
		conduct();
	} return 0;
}
