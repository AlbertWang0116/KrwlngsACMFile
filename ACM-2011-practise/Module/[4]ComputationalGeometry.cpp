//3D section. including the basical operation as well as some important method which take the important role in 3D geometry solving.


#define square(x) (x)*(x)
#define xmul(x1, y1, x2, y2) ((x1)*(y2)-(x2)*(y1))
#define dmul(x1, y1, x2, y2) ((x1)*(x2)+(y1)*(y2))
const double pi = acos(-1.0), eps = 1e-8;

struct pnt { double x, y, z; };
typedef pnt vec;


vec uvec(vec v) {
	double len = sqrt(square(v.x)+square(v.y)+square(v.z));
	vec ret; ret.x = v.x / len; ret.y = v.y / len; ret.z = v.z / len; return ret;
}

//give the rotate angle(conter-clockwise) and the normal vector for rotate, output the position of given point after the rotate.
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
