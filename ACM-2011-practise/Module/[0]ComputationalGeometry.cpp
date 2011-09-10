//this section include the basic structure and operation in 2D-plane calculation

#define square(x) (x)*(x)
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
		pnt ret. ret.x = x / c;
		ret.y = y / c; return ret;
	}
	this section is necessary in complex calculation */
}
typedef vec pnt;
const double eps = 1e-6; //1e-8, 1e-10, 1e-16
const double pi = acos(-1.0);

double getdis(const pnt &p1, const pnt &p2) { return sqrt(square(p2.x-p1.x) + square(p2.y-p1.y)); }
double getdis(const line &l, const pnt &p) { return fabs(l.a * p.x + l.b * p.y - l.c) / sqrt(square(l.a) + square(l.b)); }
double oridis(const line &l, const pnt &p) { return l.a * p.x + l.b * p.y - l.c; }

double nummul(const vec &v1, const vec &v2) { return v1.x * v2.x + v1.y * v2.y; }
double submul(const vec &v1, const vec &v2) { return v1.x * v2.y - v2.x * v1.y; }

pnt getcrs(const line &l1, const line &l2) {
	pnt ret; ret.x = (l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	ret.y = (l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l2.a * l1.b); return ret;
}

vec getvec(const pnt &p1, const pnt &p2) { return p2 - p1; }
vec uvec(const vec &v) {
	double len = sqrt(square(v.x) + square(v.y));
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
