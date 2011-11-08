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
void segxcircle(const pnt &p1, const pnt &p2, const pnt &cen, double rad, int &top, pnt *p) {
	vec v1, v2; pnt tp; double ver, hor;
	v1 = uvec(p2-p1); v2 = (vec){ -v1.y, v1.x }; 
	ver = nummul(cen, v2) - nummul(p1, v2); if (fabs(ver)-rad > eps) return;
	hor = sqrt(square(rad)-square(ver));
	tp = cen - v2 * ver - v1 * hor; if (nummul(tp-p1, tp-p2) < eps) p[top++] = tp;
	if (hor > eps) { tp = tp + v1 * hor * 2; if (nummul(tp-p1, tp-p2) < eps) p[top++] = tp; }
}

//check if the circle is totaly in the given convex.
bool circleincvx(int n, pnt *p, const pnt &cen, double rad) {
	for (int i = 0; i < n; ++i) if (submul(p[i]-cen, p[i+1]-cen)<-eps) return false;
	for (int i = 0; i < n; ++i) if (fabs(oridis(getline(p[i], p[i+1]), cen))-rad<-eps) return false;
	return true;
}

//check if the point is in the circle or on the border of the circle
bool pntincircle(const pnt &p, const pnt &cen, double rad) { return getdis(p, cen)-rad < eps; }

//get the intersection of a circle and a convex, return the number of the points.
//description: the array evt reflects the condition of the same postion at q. If evt[i] equals 1, it means the part of ret from q[i] to q[i+1] is an arc, otherwise it's a segment.
//caution: the length of arc exists in the ret must be larger than 0(means the condition that the ret is a entire circle can be expressed valid), but the degeneration should take extra O(n) time at last four lines of code.
int circlexcvx(int n, pnt *p, const pnt &cen, double rad, pnt *q, bool *evt) {
	int i, j, k, l, ret; pnt tp[4];
	if (circleincvx(n, p, cen, rad)) { q[0] = q[1] = (pnt){ cen.x + rad, cen.y }; evt[0] = 1; return 1; }
	for (ret = i = 0; i < n; ++i) {
		tp[0] = p[i]; l = 1; segxcircle(p[i], p[i+1], cen, rad, l, tp);
		for (k = j = 1; j < l; ++j) if (tp[j] != p[i] && tp[j] != p[i+1]) tp[k++] = tp[j];
		for (j = 0; j < k; ++j) if (incircle(tp[j], cen, rad)) { evt[ret] = 0; q[ret++] = tp[j]; }
		if (!incircle(p[i+1], cen, rad) && incircle(tp[k-1], cen, rad)) evt[ret-1] = 1;
	} q[ret] = q[0]; evt[ret] = evt[0]; l = ret; if (!ret) return 0;
	for (ret = i = 0; i < l; ++i) {
		if (!evt[i] || q[i] != q[i+1]) { q[ret] = q[i]; evt[ret] = evt[i]; ret++; }
	} if (!ret) { ret = 1; evt[0] = 0; }
	q[ret] = q[0]; evt[ret] = evt[0]; return ret;
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

//get the judgement whether ang3 is between the arc, all the ang has the constrains of [-pi, pi)
bool arcbetween(double ang1, double ang2, bool ati, double ang3) 
{ 
	if (fabs(ang1-ang3) < eps || fabs(ang2-ang3) < eps) return true;
	return (ati ^ ((ang1-ang3) * (ang2 - ang3) < -eps));
}

//get the enclosing circle of the triangle by the given 3 points of the vertices of triangle. return the radius of the circle and the center of the circle will be assigned to the last paremeter.
double outcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen)
{
	line l1 = getmidver(p1, p2), l2 = getmidver(p2, p3);
	cen = getcrs(l1, l2); return getdis(cen, p1);
}

//get the internal tangent circle of the triangle. return the radius of the circle and the center of the circle will be assigned to the last paremeter.
double incircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen)
{
	vec v1, v2; line l1, l2;
	v1 = uvec(p2-p1); v2 = uvec(p3-p1); l1 = getline(p1, v1+v2);
	v1 = uvec(p3-p2); v2 = uvec(p1-p2); l2 = getline(p2, v1+v2);
	cen = getcrs(l1, l2); return fabs(submul(v2, cen-p2));
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

//check whether the given point is in the polygon, no matter the order of points about polygon is clockwise or conter-clockwise
bool pntinpoly(int n, pnt *p, const pnt &p1) {
	int i, cnt; pnt p2 = { -inf, p1.y }; p[n] = p[0];
	for (cnt = i = 0; i < n; ++i) {
		if (fabs(submul(p[i+1]-p1, p[i]-p1))<eps && nummul(p[i+1]-p1, p[i]-p1)<eps) return true;
		if (fabs(p[i+1].y-p[i].y)<eps) continue;
		if (fabs(p[i+1].y-p1.y)<eps && p[i+1].x-p1.x<eps) { if (p[i+1].y-p[i].y<eps) cnt++; continue; }
		if (fabs(p[i].y-p1.y) < eps && p[i].x-p1.x < eps) { if (p[i].y-p[i+1].y<eps) cnt++; continue; }
		if (submul(p2-p1, p[i]-p1)*submul(p2-p1, p[i+1]-p1)<eps &&
			submul(p[i+1]-p[i], p1-p[i])*submul(p[i+1]-p[i], p2-p[i])<eps) cnt++;
	} return cnt % 2;
}

//get the distance of nearest pair of points.
//the ret can be saved in the global variable, in order to record the index of two points. 
int seq[N], que[N];

int cmpx(const int &i, const int &j) {
	if (fabs(p[i].x-p[j].x)<eps) return p[i].y-p[j].y < -eps;
	return p[i].x-p[j].x < -eps;
}
int cmpy(const int &i, const int &j) {
	if (fabs(p[i].y-p[j].y)<eps) return p[i].x-p[j].x < -eps;
	return p[i].y-p[j].y < -eps;
}

double lstpair(pnt *p, int lft, int rit) {
	int i, j, cnt, mid; double ret;
	if (lft >= rit) return inf;
	mid = (lft+rit) / 2; ret = getmin(lstpair(p, lft, mid), lstpair(p, mid+1, rit));
	for (cnt = 0, i = lft; i <= rit; ++i) if (fabs(p[seq[i]].x-p[seq[mid]].x)-ret<eps) que[cnt++] = seq[i];
	sort(que, que+cnt, cmpy);
	for (i = 0; i < cnt; ++i) for (j = i+1; j < cnt && j < i+8; ++j) ret = getmin(ret, getdis(p[que[i]], p[que[j]]));
	return ret;
}
double nrstpair(int n, pnt *p) {
	for (int i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmpx);
	return lstpair(p, 0, n-1);
}
