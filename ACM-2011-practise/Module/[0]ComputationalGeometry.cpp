//this section include the basic structure and operation in 2D-plane calculation

#define square(x) (x)*(x)
#define getvec(x, y) ((y)-(x))
#define xmul(x1, y1, x2, y2) ((x1)*(y2)-(x2)*(y1))
struct line { double a, b, c; };   //ax + by = c
struct pnt {
	double x, y;
/*	pnt operator+(const pnt &p) const{
		pnt ret; ret.x = x + p.x;
		ret.y = y + p.y; return ret;
	}
	pnt operator-(const pnt &p) const{
		pnt ret; ret.x = x - p.x;
		ret.y = y - p.y; return ret;
	}
	pnt operator*(const double &c) const{
		pnt ret; ret.x = x * c;
		ret.y = y * c; return ret;
	}
	pnt operator/(const double &c) const{
		pnt ret; ret.x = x / c;
		ret.y = y / c; return ret;
	}
	bool operator<(const pnt &p) const{
		if (fabs(x-p.x)<eps) return y-p.y < -eps;
		return x-p.x < -eps;
	}
	this section is necessary in complex calculation */
};
typedef pnt vec;
const double eps = 1e-6; //1e-8, 1e-10, 1e-16
const double pi = acos(-1.0);

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return xmul(v1.x, v1.y, v2.x, v2.y); }

int lessver(const pnt &p1, const pnt &p2) {
	if (fabs(p1.y-p2.y)<eps) return p1.x-p2.x < -eps;
	return p1.y-p2.y < -eps;
}

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }
double getdis(const line &l, const pnt &p) { return fabs(l.a * p.x + l.b * p.y - l.c) / sqrt(square(l.a) + square(l.b)); }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = xmul(l1.b, l1.c, l2.b, l2.c) / xmul(l1.b, l1.a, l2.b, l2.a);
	ret.y = xmul(l1.a, l1.c, l2.a, l2.c) / xmul(l1.a, l1.b, l2.a, l2.b); return ret;
} 
pnt rotate(const pnt &p, double ang) {
	pnt q, ret;
	q = (pnt){ sin(ang), cos(ang) }; ret.x = submul(p, q);
	ret.y = nummul(p, q); return ret;
}

vec uvec(const vec &v) {
	double len = sqrt(nummul(v, v));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; return ret;
}

line getline(const pnt &p1, const pnt &p2) {
	vec v = getvec(p1, p2); /* v = uvec(v); */
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p1.x + ret.b * p1.y; return ret;
}
line getline(const pnt &p, const vec &dv) {
	vec v = dv; /* v = uvec(v); */
	line ret; ret.a = -v.y; ret.b = v.x;
	ret.c = ret.a * p.x + ret.b * p.y; return ret;
}
line getmidver(const pnt &p1, const pnt &p2) {
	vec v = getvec(p1, p2); v = v/2; pnt mid = p1 + v; v = uvec(v);
	line ret; ret.a = v.x; ret.b = v.y; ret.c = ret.a*mid.x + ret.b*mid.y; return ret;
}

//it should be garanteed that p[i] < q[i]
bool checkcrs(pnt* p, pnt* q, line* l, int i, int j, pnt &crs) {
	if (q[i] < p[j] || q[j] < p[i]) return false;
	if (submul(getvec(p[i], q[i]), getvec(p[i], p[j])) * submul(getvec(p[i], q[i]), getvec(p[i], q[j])) > eps) return false;
	if (submul(getvec(p[j], q[j]), getvec(p[j], p[i])) * submul(getvec(p[j], q[j]), getvec(p[j], q[i])) > eps) return false;
	if (fabs(submul(getvec(p[i], q[i]), getvec(p[j], q[j]))) < eps) if (q[i] < q[j]) crs = q[i]; else crs = q[j];
	else crs = getcrs(l[i], l[j]); return true;
}

//graham method to get convex
int tmp[N];
int vercmp(const int &x, const int &y) { return lessver(p[x], p[y]); }

int graham(int n, pnt* p, int *seq) {
	int i, top, bot;
	for (i = 0; i < n; ++i) tmp[i] = i; sort(tmp, tmp+n, vercmp);
	for (seq[top = bot = 0] = tmp[0], i = 1; i < n; ++i) {
		while (top > bot && submul(getvec(p[seq[top-1]], p[seq[top]]), getvec(p[seq[top]], p[tmp[i]])) < eps) --top;
		seq[++top] = tmp[i];
	} bot = top;
	for (i = n-2; i >= 0; --i) {
		while (top > bot && submul(getvec(p[seq[top-1]], p[seq[top]]), getvec(p[seq[top]], p[tmp[i]])) < eps) --top;
		seq[++top] = tmp[i];
	} return top;
}

//melkman method to get convex
int tmp[N];
int melkman(int n, pnt *p, int *seq)
{
	int i, j, bot, top;
	for (i = top = 0; i < n; ++i) if (p[i] < p[top]) top = i;
	for (j = top, i = 0; i < n; ++i, j = (j+1)%n) tmp[i] = j;
	seq[n] = tmp[0]; seq[n-1] = tmp[1]; seq[n+1] = tmp[1];
	for (i = 2; i < n; ++i) if (fabs(submul(getvec(p[seq[n]], p[seq[n-1]]), getvec(p[seq[n-1]], p[tmp[i]])))<eps) {
		if (p[seq[1]] < p[tmp[i]]) { seq[n-1] = tmp[i]; seq[n+1] = tmp[i]; }
	} else break; top = n+1; bot = n-1;
	for (; i < n; ++i) {
		if (submul(getvec(p[seq[top-1]], p[seq[top]]), getvec(p[seq[top]], p[tmp[i]])) > -eps &&
			submul(getvec(p[seq[bot+1]], p[seq[bot]]), getvec(p[seq[bot]], p[tmp[i]])) < eps) continue;
		while (submul(getvec(p[seq[top-1]], p[seq[top]]), getvec(p[seq[top]], p[tmp[i]])) < eps) --top;
		while (submul(getvec(p[seq[bot+1]], p[seq[bot]]), getvec(p[seq[bot]], p[tmp[i]])) > -eps) ++bot;
		seq[++top] = seq[--bot] = tmp[i];
	} for (i = bot; i <= top; ++i) seq[i-bot] = seq[i]; return top - bot;
}
