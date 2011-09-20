//this section is about the typical sweepline algorithm


//-------------------------------Unhandled------------------------------//
//get all the intersection for the n segment, uses O((m+n)logn) time.
//the operation "<" of the struct pnt must be overload.
//Caution: The segments overlap each other may be found out more than once, it must be dealed with specifically. One way to solve this is to handle the overlap only at the tail of one segment, they're adjacent in the map "seg".
//Caution: If both endpoints of a segment are the same, it'll be handled in the link "info.s" but not be added in the state.
struct evpinfo { int s, c; };
struct scmp { 
	static pnt pre[N], p[N], q[N]; static line l[N];
    bool operator()(const int &i, const int &j) {
        double y1, y2, ang1, ang2; pnt pos;
        ang1 = atan2(q[i].y - p[i].y, q[i].x - p[i].x); ang2 = atan2(q[j].y - p[j].y, q[j].x - p[j].x);
        if (pre[i] < pre[j]) pos = pre[j]; else pos = pre[i];
        if (fabs(ang1-pi/2)<eps) y1 = pos.y; else y1 = p[i].y + (q[i].y-p[i].y)/(q[i].x-p[i].x) * (pos.x-p[i].x);
        if (fabs(ang2-pi/2)<eps) y2 = pos.y; else y2 = p[j].y + (q[j].y-p[j].y)/(q[j].x-p[j].x) * (pos.x-p[j].x);
        if (fabs(y1-y2)<eps && fabs(ang1-ang2)<eps) return i < j; if (fabs(y1-y2)<eps) return ang1-ang2<-eps; return y1-y2<-eps;
    }
};
pnt scmp::pre[N] = {0, 0}, scmp::p[N] = {0, 0}, scmp::q[N] = {0, 0};
line scmp::l[N] = {0, 0, 0};
const evpinfo dft = {0, 0};
map<pnt, evpinfo> evt;
map<int, int, scmp> seg;
int hd[N], tl[N], snext[N];

int cmpl(pnt *p, pnt *q, int i, int j) {
    double val = submul(getvec(p[i], q[i]), getvec(p[j], q[j]));
	if (fabs(val)<eps) if (i > j) return 1; else return -1;
    if (val > eps) return -1; if (val < -eps) return 1; 
}

void evtinsert(const pnt &p, const int id) {
	map<pnt, evpinfo>::iterator pos;
	pos = evt.find(p); if (pos == evt.end()) pos = evt.insert(pair<pnt, evpinfo>(p, dft)).first;
	if (!pos->second.c) pos->second.c = id;
}

void line_intersection(int n, pnt* p, pnt* q)
{
    int i, lst, mst, lb, rb;
    pnt np, evp;
    evpinfo info;
    map<pnt, evpinfo>::iterator pos, ipos;
    map<int, int, scmp>::iterator cur, lft, rit;
	bool empty;
    evt.clear(); seg.clear();
    for (i = 1; i <= n; ++i) if (q[i] < p[i]) { evp = p[i]; p[i] = q[i]; q[i] = evp; }
	for (i = 1; i <= n; ++i) { scmp::p[i] = p[i]; scmp::q[i] = q[i]; scmp::l[i] = getline(p[i], q[i]); }
    for (i = 1; i <= n; ++i) {
        pos = evt.find(p[i]); if (pos == evt.end()) pos = evt.insert(pair<pnt, evpinfo>(p[i], dft)).first;
        snext[i] = pos->second.s; pos->second.s = i; if (!equal(p[i], q[i])) evtinsert(q[i], i);
    }
    while (evt.size()) {
        pos = evt.begin(); info = pos->second; evp = pos->first; hd[0] = 0; tl[0] = 0;
        if (info.c) {
            cur = seg.find(info.c); lft = rit = cur;
            while (lft != seg.begin() && fabs(oridis(scmp::l[(--lft)->first], evp))<eps)  
				if (!equal(q[lft->first], evp)) hd[++hd[0]] = lft->first; else tl[++tl[0]] = lft->first;
			while (rit != seg.end() && fabs(oridis(scmp::l[rit->first], evp))<eps) 
				if (!equal(q[rit->first], evp)) hd[++hd[0]] = (rit++)->first; else tl[++tl[0]] = (rit++)->first;
			if (fabs(oridis(scmp::l[lft->first], evp))>eps) { lb = lft->first; lft++; } else lb = 0;
            if (rit != seg.end()) rb = rit->first; else rb = 0;
        }
		//handle the intersection.
		printf("intersection:[%.3f][%.3f]\n", evp.x, evp.y);
		printf("insert point:"); for (i = info.s; i; i = snext[i]) printf("%d ", i); printf("\n");
		printf("cross point:"); for (i = 1; i <= hd[0]; ++i) printf("%d ", hd[i]); printf("\n");
		printf("remove point:"); for (i = 1; i <= tl[0]; ++i) printf("%d ", tl[i]); printf("\n");
		//handle ended.
        if (info.c) for (; lft != rit; ) { cur = lft; lft++; seg.erase(cur); }
		for (i = info.s; i; i = snext[i]) hd[++hd[0]] = i;
        if (hd[0]) {
            for (empty = true, i = 1; i <= hd[0]; ++i) if (!equal(p[hd[i]], q[hd[i]])) {
				if (empty) { empty = false; mst = hd[i]; lst = hd[i]; }
                if (cmpl(p, q, mst, hd[i]) < 0) mst = hd[i]; if (cmpl(p, q, lst, hd[i]) > 0) lst = hd[i];
                scmp::pre[hd[i]] = evp; seg.insert(pair<int, int>(hd[i], 0));
            } if (!empty) { 
			if ((lft = seg.find(lst)) != seg.begin()) { cur = lft--; if (checkcrs(p, q, scmp::l, cur->first, lft->first, np) && evp < np) evtinsert(np, lst); }
            cur = rit = seg.find(mst); rit++; if (rit != seg.end()) if (checkcrs(p, q, scmp::l, cur->first, rit->first, np) && evp < np) evtinsert(np, mst);
			}
        } if ((!hd[0] || empty) && info.c && lb && rb) {
            lft = seg.find(lb); rit = seg.find(rb);
            if (checkcrs(p, q, scmp::l, lft->first, rit->first, np) && evp < np) evtinsert(np, lb);
        } evt.erase(pos);
    }
}


//Rotate Caliper
//Be sure that the input must be a convex, and the order is anti-clockwise.
//Return value is the number of the state, the calculation means that between the angle evt[i-1] to evt[i](0 to evt[0]), the anti-polar is fst[i] and snd[i].

double next[N];

int rotate_caliper(int n, pnt* p, double *evt, int *fst, int *snd)
{
	int i, lst, mst, ret;
	double ang, ang1, ang2, dlt;
	p[n] = p[0]; p[n+1] = p[1];
	for (lst = mst = 0, i = 1; i < n; ++i) {
		if (lessver(p[i], p[lst])) lst = i;
		if (lessver(p[mst], p[i])) mst = i;
	} for (i = 0; i < n; ++i) {
		ang1 = atan2(p[i+1].y-p[i].y, p[i+1].x-p[i].x);
		ang2 = atan2(p[i+2].y-p[i+1].y, p[i+2].x-p[i+1].x);
		while (ang2-ang1<-eps) ang2 += 2*pi; next[i] = ang2 - ang1;
	} ang1 = atan2(p[lst+1].y-p[lst].y, p[lst+1].x-p[lst].x);
	ang2 = atan2(p[mst].y-p[mst+1].y, p[mst].x-p[mst+1].x);
	for (ret = 0, ang = 0; ang - pi < -eps; ) {
		dlt = getmin(ang1, ang2); ang += dlt;
		ret++; evt[ret] = ang; fst[ret] = lst; snd[ret] = mst;
		ang1 -= dlt; if (fabs(ang1)<eps) { ang1 = next[lst]; lst = (lst+1) % n; }
		ang2 -= dlt; if (fabs(ang2)<eps) { ang2 = next[mst]; mst = (mst+1) % n; }
	} return ret;
}

void get_anti_polar(int n, double *evt, int *fst, int *snd, double ang, int &ret1, int &ret2) {
	int lst = 1, mst = n, mid;
	while (mst > lst) { mid = (mst+lst)/2; if (ang-evt[mid]>eps) lst = mid+1; else mst = mid; }
	ret1 = fst[lst]; ret2 = snd[mst];
}
