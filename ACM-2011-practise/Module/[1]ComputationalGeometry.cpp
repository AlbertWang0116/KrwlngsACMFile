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
int circleline(const line &l, const pnt &ori, const double &rad, pnt *p)
{
	int ret;
	double c = sqrt(square(l.a) + square(l.b));
	double a = -(l.a * ori.x + l.b * ori.y - l.c) / c;
	if (fabs(a) - rad > eps) return 0; else if (fabs(a) - rad < -eps) ret = 2; else ret = 1;
	double b = sqrt(square(rad) - square(a));
	vec vt; vt.x = l.a * a / c; vt.y = l.b * a / c;
	vec vp; vp.x = l.b * b / c; vp.y = -l.a * b / c;
	p[0] = ori + vt + vp; p[1] = ori + vt - vp; return ret;
}

//get the circle with 3 known points
void getcircle(const pnt &p1, const pnt &p2, const pnt &p3, pnt &cen, double &r)
{
	line l1 = getmidver(p1, p2), l2 = getmidver(p2, p3);
	cen = getcrs(l1, l2); r = getdis(cen, p1);
}

//get the judgement whether ang3 is between the arc, all the ang has the constrains of [-pi, pi)
bool arcbetween(double ang1, double ang2, bool ati, double ang3) 
{ 
	if (fabs(ang1-ang3) < eps || fabs(ang2-ang3) < eps) return true;
	return (ati ^ ((ang1-ang3) * (ang2 - ang3) < -eps));
}
