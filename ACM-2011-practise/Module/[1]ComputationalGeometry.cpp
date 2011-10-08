//in this section, the operator+(pnt),-(pnt),*(double),/(double) should be overloaded in definition


//get the line which is the reflection of l1 through l0
//Caution: the line of l0 and l1 must be unified in construction, or it'll have some precision problem!
line lineref(const line &l0, const line &l1)
{
	pnt p; if (fabs(l0.a) > fabs(l0.b)) { p.x = l0.c / l0.a; p.y = 0; } else { p.x = 0; p.y = l0.c / l0.b; }
	vec v; v.x = l0.b; v.y = -l0.a; double len = sqrt(square(l0.a) + square(l0.b));
	double sa = v.y / len, ca = v.x / len;
	double a = l1.a * square(ca) - l1.a * square(sa) + 2 * l1.b * sa * ca;
	double b = l1.b * square(sa) - l1.b * square(ca) + 2 * l1.a * sa * ca;
	line ret; ret.a = a; ret.b = b; ret.c = l1.c + (a - l1.a) * p.x + (b - l1.b) * p.y;
	return ret;
}

//get the number of intersection of a circle and a line, as well as the point of intersection
int linexcircle(const line &l, const pnt &cen, double rad, pnt *p)
{
	double ver, hor; vec v1, v2;
	v1 = (vec){ l.a, l.b}; v1 = uvec(v1); v2 = (vec){ -v1.y, v1.x};
	ver = oridis(l, cen); if (fabs(ver)-rad > eps) return 0;
	if (fabs(fabs(ver)-rad)<eps) { p[0] = cen - v1 * ver; return 1; }
	hor = sqrt(square(rad)-square(ver));
	p[0] = cen - v1*ver + v2*hor; p[1] = cen - v1*ver - v2*hor; return 2;
}

//get the number of intersection of a circle and a segment, as well as the point of intersection
int segxcircle(const pnt &p1, const pnt &p2, const pnt &cen, double rad, pnt *p)
{
	int cnt, ret, i; pnt crs[2];
	cnt = linexcircle(getline(p1, p2), cen, rad, crs);
	for (ret = i = 0; i < cnt; ++i) if (nummul(p1-crs[i], p2-crs[i]) < eps) p[ret++] = crs[i]; return ret;
}

//get the enclosing circle of the triangle by the given 3 points of the vertices of triangle. return the radius of the circle and the center of the circle will be assigned to the last paremeter.
double outcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen)
{
	line l1 = getmidver(p1, p2), l2 = getmidver(p2, p3);
	cen = getcrs(l1, l2); return getdis(cen, p1);
}

//get the judgement whether ang3 is between the arc, all the ang has the constrains of [-pi, pi)
bool arcbetween(double ang1, double ang2, bool ati, double ang3) 
{ 
	if (fabs(ang1-ang3) < eps || fabs(ang2-ang3) < eps) return true;
	return (ati ^ ((ang1-ang3) * (ang2 - ang3) < -eps));
}

//get the fermat point which has the least total distance to the given n points.
#define NUM 2 //C = (NUM+1)^2
#define BD 2 //C = (BD*2+1)^2
const double ATT = 0.9, EPS = 1e-6; //when ADd = 0.9, C = log10(range/EPS) * 10

double valuate(int n, pnt *p, const pnt &tp) {
	double ret; int i;
	for (ret = i = 0; i < n; ++i) ret += getdis(tp, p[i]);
	return ret;
}

pnt fermatpoint(int n, pnt* p)
{
	double lft, rit, up, dn, stx, sty, dx, dy, lst, val, tv, ttv;
	pnt ret, vp, tp, ttp; int i, j, k, l;
	lft = dn = inf; rit = up = -inf;
	for (i = 0; i < n; ++i) { 
		lft = getmin(lft, p[i].x); rit = getmax(rit, p[i].x);
		dn = getmin(dn, p[i].y); up = getmax(up, p[i].y);
	} stx = rit-lft; sty = up-dn; lst = inf;
	for (i = 0; i <= NUM; ++i) for (j = 0; j <= NUM; ++j) {
		vp = (pnt){ lft+stx/NUM*i, dn+sty/NUM*j }; val = valuate(n, p, vp);
		for (dx = stx/NUM/BD, dy = sty/NUM/BD; dx > EPS || dy > EPS; dx *= ATT, dy *= ATT) {
			for (tp = vp, tv = val, k = -BD; k <= BD; ++k) for (l = -BD; l <= BD; ++l) {
				ttp = (pnt){vp.x+dx*k, vp.y+dy*l}; ttv = valuate(n, p, ttp);
				if (ttv < tv) { tv = ttv; tp = ttp; }
			} vp = tp; val = tv;
		} if (val < lst) { lst = val; ret = vp; }
	} return vp;
}

//get the common point of three verticle line of a triangle.
pnt orthocenter(const pnt &p1, const pnt &p2, const pnt &p3) 
{
	vec v1, v2, ret; line l1, l2;
	v1 = uvec(p3-p2); l1 = (line){ v1.x, v1.y, nummul(v1, p1) };
	v2 = uvec(p3-p1); l2 = (line){ v2.x, v2.y, nummul(v2, p2) };
	ret = getcrs(l1, l2); return ret;
}

//get the barycenter of a polygon given in clockwise
pnt barycenter(int n, pnt *p) 
{
	int i; double tot, ta; pnt ret;
	p[n] = p[0]; ret = (pnt){ 0, 0};
	for (tot = i = 0; i < n; ++i) {
		ta = submul(p[i], p[i+1]);
		tot += ta; ret.x += (p[i].x+p[i+1].x)*ta/3; ret.y += (p[i].y+p[i+1].y)*ta/3;
	} ret.x /= tot; ret.y /= tot; return ret;
}

//get the internal tangent circle of the triangle. return the radius of the circle and the center of the circle will be assigned to the last paremeter.
double incircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen)
{
	vec v1, v2; line l1, l2;
	v1 = uvec(p2-p1); v2 = uvec(p3-p1); l1 = getline(p1, v1+v2);
	v1 = uvec(p3-p2); v2 = uvec(p1-p2); l2 = getline(p2, v1+v2);
	cen = getcrs(l1, l2); return fabs(submul(v2, cen-p2));
}

//get the cross points of two circle.
int circlecrs(const pnt &p1, const pnt &p2, double r1, double r2, pnt *p) {
	double len = getdis(p1, p2); vec v = uvec(p2-p1);
	if (len + r1 - r2 < -eps ||  len + r2 - r1 < -eps || r1 + r2 - len < -eps) return 0;
	if (fabs(len+r1-r2) < eps) { p[0] = p1 - v * r1; return 1; }
	if (fabs(len+r2-r1) < eps || fabs(r1+r2-len) < eps) { p[0] = p1 + v * r1; return 1; }
	double ang1 = atan2(v.y, v.x), ang2 = acos((square(len)+square(r1)-square(r2))/(2*len*r1));
	v = (vec){ cos(ang1+ang2), sin(ang1+ang2) }; p[0] = p1 + v * r1;
	v = (vec){ cos(ang1-ang2), sin(ang1-ang2) }; p[1] = p1 + v * r1;
	return 2;
}
