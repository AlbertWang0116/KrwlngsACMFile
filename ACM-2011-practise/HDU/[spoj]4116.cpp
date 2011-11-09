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
const double eps = 1e-7, pi = acos(-1.0);
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
#define N 1010
#define M 4*N
pnt p[N];
int seq[M], tmp[M];
double ang[M], r[N];
int n, cnt, ret, top, tot;
char ch, str[110];
bool tag;

inline int getmax(int x, int y) { return x > y ? x : y; }
double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x)+square(p2.y-p1.y)); }

inline void insert(double val) {
	while (val+pi<-eps) val += 2*pi;
	while (val-pi>-eps) val -= 2*pi;
	ang[top++] = val;
}

inline int cmpl(const int &i, const int &j) {
	if (fabs(ang[i]-ang[j])<eps) return (i % 2 == 0 && j % 2 == 1);
	return ang[i]-ang[j]<-eps;
}

inline void inputpnt(int i) {
	p[i].x = p[i].y = r[i] = 0;
	while ((ch = getchar()) != '-' && (ch < '0' || ch > '9')); tag = 1;
	do {
		if (ch == ' ') { if (!tag) p[i].x *= -1.0; break; }
		else if (ch == '-') tag = 0;
		else p[i].x = p[i].x * 10 + ch - '0';
	} while (ch = getchar()); while ((ch = getchar()) != '-' && (ch < '0' || ch > '9')); tag = 1;
	do {
		if (ch == ' ') { if (!tag) p[i].y *= -1.0; break; }
		else if (ch == '-') tag = 0;
		else p[i].y = p[i].y * 10 + ch - '0';
	} while (ch = getchar()); while ((ch = getchar()) != '-' && (ch < '0' || ch > '9')); 
	do {
		if (ch < '0' || ch > '9') return;
		r[i] = r[i] * 10 + ch - '0';
	} while (ch = getchar());
}

void conduct()
{
	int i, j, k, l, ii, jj; double dis, ang1, ang2, ang3;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) inputpnt(i);
//	for (i = 0; i < n; ++i) printf("p[%d]=(%.3f,%.3f) r:%.3f\n", i, p[i].x, p[i].y, r[i]);
	for (ret = i = 0; i < n; ++i) {
		for (cnt = top = j = 0; j < n; ++j) {
			dis = getdis(p[i], p[j]);
			if (dis-r[i]-r[j] > eps) {
				ang1 = acos((r[i]-r[j])/dis); ang2 = acos((r[i]+r[j])/dis);
				ang3 = atan2(p[j].y-p[i].y, p[j].x-p[i].x); if (ang3-pi>-eps) ang3 = -pi;
				ang[top] = ang3-ang1; while (ang[top]+pi<-eps) ang[top] += 2*pi; ++top;
				ang[top] = ang3-ang2; while (ang[top]+pi<-eps) ang[top] += 2*pi; ++top;
				ang[top] = ang3+ang2; while (ang[top]-pi>-eps) ang[top] -= 2*pi; ++top;
				ang[top] = ang3+ang1; while (ang[top]-pi>-eps) ang[top] -= 2*pi; ++top;
			} else if (r[j]-r[i]-dis > -eps) { cnt++; if (cnt>ret) ret = cnt; }
			else if (r[i]-r[j]-dis > -eps) continue;
			else {
				ang1 = acos((r[i]-r[j])/dis); 
				ang3 = atan2(p[j].y-p[i].y, p[j].x-p[i].x); if (ang3-pi>-eps) ang3 = -pi;
				ang[top] = ang3-ang1; while (ang[top]+pi<-eps) ang[top] += 2*pi; ++top;
				ang[top] = ang3+ang1; while (ang[top]-pi>-eps) ang[top] -= 2*pi; ++top;
			}
		} for (j = 0; j < top; ++j) seq[j] = j;
		for (j = 0; j < top; ++j) {
			for (k = seq[j], ii = j+1, jj = (ii>>1); jj; ii = jj, jj = (ii>>1)) 
				if (cmpl(k, tmp[jj])) tmp[ii] = tmp[jj]; else break;
			tmp[ii] = k;
		} for (j = 0; j < top; ++j) {
			seq[j] = tmp[1]; k = tmp[top-j]; l = top-j-1;
			for (ii = 1, jj = (ii<<1); jj <= l; ii = jj, jj = (ii<<1)) {
				if (jj < l && cmpl(tmp[jj+1], tmp[jj])) ++jj;
				if (cmpl(tmp[jj], k)) tmp[ii] = tmp[jj]; else break;
			} tmp[ii] = k;
		} for (j = 0; j < top/2; ++j) if (ang[j*2]-ang[j*2+1]>eps) cnt++;
		for (j = 0; j < top; ++j)
			if (seq[j]%2) cnt--;
			else { cnt++; if (cnt>ret) ret = cnt; }
	} printf("%d\n", ret);
}

int main() {
//	printf("start:%d\n", time(0));
	int t; scanf("%d", &t); tot = 0;
	for (int i = 1; i <= t; ++i) {
		printf("Case #%d: ", i); tot++;
		conduct();
	} 
//	printf("end:%d\n", time(0));	
	return 0;
}
