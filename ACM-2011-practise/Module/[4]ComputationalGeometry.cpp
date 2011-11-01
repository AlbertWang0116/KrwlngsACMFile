//3D section. including the basical operation as well as some important method which take the important role in 3D geometry solving.


#define square(x) (x)*(x)
#define xmul(x1, y1, x2, y2) ((x1)*(y2)-(x2)*(y1))
#define dmul(x1, y1, x2, y2) ((x1)*(x2)+(y1)*(y2))
const double pi = acos(-1.0), eps = 1e-8;

struct pnt { 
	double x, y, z; 
	pnt operator+(const pnt &p) const {
		pnt ret; ret.x = x + p.x; ret.y = y + p.y;
		ret.z = z + p.z; return ret;
	} pnt operator-(const pnt &p) const {
		pnt ret; ret.x = x - p.x; ret.y = y - p.y;
		ret.z = z - p.z; return ret;
	} pnt operator*(const double c) const {
		pnt ret; ret.x = x * c; ret.y = y * c;
		ret.z = z * c; return ret;
	} pnt operator/(const double c) const {
		pnt ret; ret.x = x / c; ret.y = y / c;
		ret.z = z / c; return ret;
	}
};
typedef pnt vec;
struct plane { vec ori; double val; };

double nummul(const vec &v1, const vec &v2) { return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }
vec submul(const vec &v1, const vec &v2) {
	vec ret; ret.x = xmul(v1.y, v1.z, v2.y, v2.z); ret.y = xmul(v1.z, v1.x, v2.z, v2.x);
	ret.z = xmul(v1.x, v1.y, v2.x, v2.y); return ret;
}

vec uvec(vec v) {
	double len = sqrt(square(v.x)+square(v.y)+square(v.z));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; ret.z = v.z / len; return ret;
}

plane getplane(const pnt &p1, const pnt &p2, const pnt &p3) {
	vec v1 = p2 - p1, v2 = p3 - p1;
	plane ret; ret.ori = uvec(submul(v1, v2)); 
	ret.val = nummul(ret.ori, p1); return ret;
}
plane uplane(const plane &s) {
	double len = sqrt(square(s.ori.x)+square(s.ori.y)+square(s.ori.z));
	plane ret; ret.ori = s.ori / len; ret.val = s.val / len; return ret;
}

//give the rotate angle(conter-clockwise) and the normal vector for rotate, output the position of given point after the rotate.
#define OFF(i, j) ((i) == (j) ? 1 : 0)

pnt axis_rotate(const pnt &p, const pnt &ori, double ang) {
	vec v = uvec(ori);
	double pv[3] = { p.x, p.y, p.z}, val[3] = { v.x, v.y, v.z }, off[3] = { 0, -1, 1 };
	double sa = sin(ang), ca = cos(ang), rv[3];
	for (int i = 0; i < 3; ++i) for (int j = rv[i] = 0; j < 3; ++j) 
		rv[i] += pv[j] * ((1 - ca) * val[i] * val[j] + sa * val[(6-i-j)%3] * off[(3-i+j)%3] + ca * OFF(i, j));
	pnt ret = { rv[0], rv[1], rv[2] }; return ret;
}
/*  Note: the principle shows below -->
			| vx*vx, vx*vy, vx*vz |						|  0, -vz,  vy |
	A1 =	| vy*vx, vy*vy, vy*vz |				A2 = 	| vz,   0, -vx |
			| vz*vz, vz*vy, vz*vz |						|-vy,  vx,   0 |
	p' = ((1-cosa)*A1+sina*A2+cosa*I) * p;
	It's a simplified expression for axis_rotate2, but it doesn't always run faster than the latter.
*/ 

//the same as the axis_rotate. Sometimes it runs better but the code is longer.
pnt axis_rotate2(const pnt &p, const pnt &ori, double ang) {
	double ca[5], sa[5], tv1, tv2, xyv; vec v = uvec(ori); int i, j, k;
	xyv = sqrt(square(v.x)+square(v.y)); 
	if (xyv > eps) { ca[0] = v.x / xyv; sa[0] = -v.y / xyv; } 
	else { ca[0] = 1.0; sa[0] = 0.0; }
	ca[1] = v.z; sa[1] = -xyv; ca[2] = cos(ang); sa[2] = sin(ang);
	ca[3] = ca[1]; sa[3] = -sa[1]; ca[4] = ca[0]; sa[4] = -sa[0];
	double rv[3] = { p.x, p.y, p.z };
	for (i = 0; i < 5; ++i) {
		j = (3-i%2) % 3; k = (j+1)%3;
		tv1 = xmul(rv[j], rv[k], sa[i], ca[i]); tv2 = dmul(rv[j], rv[k], sa[i], ca[i]);
		rv[j] = tv1; rv[k] = tv2;
	} pnt ret = { rv[0], rv[1], rv[2] }; return ret;
}

//Transformation with matrix
//The advantage of it is to simplify the multi transformation operation. A matrix can contain the combination of the operation. If there're n points and m operation, using matrix only takes O(n+m) time.
//Caution1: right-hand coordinate system and right-hand rule in rotation only.
//Caution2: the whole transformation matrix should initially set to I.

void matmul(double a[][4], double b[][4]) {
	int i, j, k; double c[4][4]; 
	for (i = 0; i < 4; ++i) for (j = 0; j < 4; ++j) { c[i][j] = a[i][j]; a[i][j] = 0; }
	for (i = 0; i < 4; ++i) for (j = 0; j < 4; ++j) for (k = 0; k < 4; ++k) a[i][j] += c[i][k] * b[k][j];
}

pnt pnttran(const pnt &p, double a[][4]) {
	double val[4] = { p.x, p.y, p.z, 1 }, rv[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) rv[i] += val[j] * a[j][i];
	pnt ret = { rv[0], rv[1], rv[2] }; return ret;
}

void mattranslate(double a[][4], double dx, double dy, double dz) {
	int i; double b[4][4]; 
	memset(b, 0, sizeof(b)); for (i = 0; i < 4; ++i) b[i][i] = 1;
	b[3][0] = dx; b[3][1] = dy; b[3][2] = dz; matmul(a, b);
}

void matrotate(double a[][4], const vec &axis, double dlt) {
	int i, j; double b[4][4]; vec v = uvec(axis); 
	double sind = sin(dlt), cosd = cos(dlt), val[3] = { v.x, v.y, v.z }, off[3] = { 0, 1, -1 };
	memset(b, 0, sizeof(b)); for (i = 0; i < 4; ++i) b[i][i] = 1;
	for (i = 0; i < 3; ++i) for (j = 0; j < 3; ++j) 
		b[i][j] = (1-cosd) * val[i] * val[j] + sind * off[(3-i+j)%3] * val[(6-i-j)%3] + cosd * OFF(i, j);
	matmul(a, b);
}

void matscale(double a[][4], double cx, double cy, double cz) {
	int i; double b[4][4];
	memset(b, 0, sizeof(b)); for (i = 0; i < 4; ++i) b[i][i] = 1;
	b[0][0] = cx; b[1][1] = cy; b[2][2] = cz; matmul(a, b);
}
/*
						|  1,  0,  0,  0 |						| cx,  0,  0,  0 |
TRANSLATE(dx,dy,dz) = 	|  0,  1,  0,  0 |  SCALE(cx,cy,cz) =	|  0, cy,  0,  0 |  ROTATE(vx,vy,vz,delta) is decribed above.
						|  0,  0,  1,  0 |						|  0,  0, cz,  0 |
						| dx, dy, dz,  1 |						|  0,  0,  0,  1 |
*/
