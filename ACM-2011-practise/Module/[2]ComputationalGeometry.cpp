//This section is about the incremental method


//calculate the convex of the combine of several half plane, output the number of distinct point at the border, as well as each point and line in counter-clockwise order.
//the answer of lines is in the seq array, the endpoint of line seq[i] is p[i] and p[i+1].
//Caution: the line here must be unified before calculation.
line bdr1 = { 1.0, 0.0, -inf }, bdr2 = { -1.0, 0.0, -inf }, bdr3 = { 0.0, 1.0, -inf }, bdr4 = { 0.0, -1.0, -inf };

int hfpcmp(const int &x, const int &y) {
	if (fabs(ang[x]-ang[y])<eps) return l[x].c - l[y].c > eps;
	return ang[x] - ang[y] < -eps;
}

int hfplane(int n, line *l, pnt *p, int *seq, double *ang)
{
	int i, j, top, bot, ret;
	l[n++] = bdr1; l[n++] = bdr2; l[n++] = bdr3; l[n++] = bdr4;
	for (i = 0; i < n; ++i) { ang[i] = atan2(l[i].b, l[i].a); if (fabs(ang[i]-pi)<eps) ang[i] = -pi; }
	for (i = 0; i < n; ++i) seq[i] = i; std::sort(seq, seq+n, hfpcmp);
	for (i = j = 1; i < n; ++i) if (fabs(ang[seq[i]]-ang[seq[j-1]])>eps) seq[j++] = seq[i]; n = j;
	for (i = 1, top = bot = 0; i < n; ++i) {
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (ang[seq[i]] > -eps && top == bot) return 0;
		p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		if (ang[seq[i]] > -eps) break;
	} p[bot] = (pnt){ -inf*2, -inf*2 };
	for (++i; i < n; ++i) {
		if (oridis(l[seq[i]], p[bot]) > -eps) continue;
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (top == bot) return 0; p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		while (oridis(l[seq[top]], p[bot+1]) < -eps) ++bot; p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
	} for (ret = 0, i = bot; i < top; ++i) if (fabs(p[i].x-p[i+1].x)>eps || fabs(p[i].y-p[i+1].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} if (!ret || fabs(p[i].x-p[0].x)>eps || fabs(p[i].y-p[0].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} p[ret] = p[0]; return ret;
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

//Randomize method to get smallest enclosing circle for N given points
int tmp[N], seq[N];
double enclosng_circle(int n, pnt *p, pnt &cen) {
	int i, j, k, l; double rad;
	for (i = 0; i < n; ++i) seq[i] = i; cen = p[0]; rad = 0.0;
	for (i = 2; i < n; ++i) {
		j = rand()%(n-i) + i; k = seq[j]; seq[j] = seq[i]; seq[i] = k;
		if (getdis(cen, p[seq[i]])-rad < eps) continue;
		tmp[0] = seq[i]; tmp[1] = seq[1]; seq[i] = seq[0];	
		cen = (p[tmp[0]]+p[tmp[1]]) / 2.0; rad = getdis(cen, p[tmp[0]]);
		for (j = 2; j <= i; ++j) {
			if (getdis(cen, p[seq[j]])-rad < eps) { tmp[j] = seq[j]; continue; }
			tmp[j] = tmp[1]; tmp[1] = seq[j]; 
			cen = (p[tmp[0]]+p[tmp[1]]) / 2.0; rad = getdis(cen, p[tmp[0]]);
			for (k = 2; k <= j; ++k) if (getdis(cen, p[tmp[k]])-rad > eps) {
				l = tmp[k]; tmp[k] = tmp[2]; tmp[2] = l;
				rad = outcircle(p[tmp[0]], p[tmp[1]], p[tmp[2]], cen);
			} 
		} for (j = 0; j <= i; ++j) seq[j] = tmp[j];
	} return rad;
}

//get the farthest point for each given point in convex, store in array ati(i's farthest point is at index ati[i])
//Caution:	1. 	The order of convex must be counter-clockwise
//			2. 	The length of array(N) should be 3 times larger than the data region.(The same for array p)
//			3.	The line construct function here has no need to unify.
int pre[N], pro[N], pos[N];
bool vst[N]; line ll[N];

void farestpair(int n, pnt *p, int *ati) {
	int i, j, k, l, st, ed;
	for (i = 0; i < n; ++i) { p[i].x *= 2; p[i].y *= 2; }
	for (i = 0; i < n; ++i) { pre[i] = i-1; pro[i] = i+1; } pre[0] = n-1; pro[n-1] = 0;
	for (i = 0; i < n; ++i) p[i+n] = p[i+2*n] = p[i];
	for (l = st = i = 0; l <= n; i = pro[i], ++l) {
		ll[i] = getline(p[i], p[pro[i]]);
		while ((i != st || l == n) && submul(p[pro[i]]-p[i], p[pos[pre[i]]]-p[i]) >= 0 && oridis(ll[i], p[pos[pre[i]]])+(l!=n-1?0:1) > 0) {	//h-l-1:a?b:c
			if (l == n && i == st) { st = pro[i]; l = n-1; }
			pro[pre[i]] = pro[i]; pre[pro[i]] = pre[i]; i = pre[i];
			ll[i] = getline(p[i], p[pro[i]]);
		} if (i == st && l != n) ed = pro[i]; else ed = pos[pre[i]];
		while (submul(p[pro[i]]-p[i], p[ed]-p[i]) < 0 || oridis(ll[i], p[ed])-(l!=n-1?1:0) < 0) ++ed; pos[i] = ed;				//h-l-1:a?b:c
	} memset(vst, 0, sizeof(vst));
	for (i = st; !vst[i]; i = pro[i]) {
		j = pos[i]; k = pos[pro[i]]; vst[i] = 1; while (k < j) k += n;
		for (l = j; l < k; ++l) ati[l%n] = pro[i];
	}
}
/*Hi-light-expression-1:	(A?B:C)
						1.If the input is float, change the B and C to the 2*eps if its value equals 1 below.
						2.For the same farthest, A is diffierent according to the requirement to choose the index:
							1).the smallest index: A <- l==n-1
							2).the largest index : A <- l!=n-1
							3).arbitrary: A <- l==n-1, l!=n-1, 1, 0 are all ok. 
 *Trick Note:	1.after erase of mid-point, the terminal of new seg's previous seg may before the endpoint pro[i], even on the left side of judge line.
		  In this condition, the erase operation should be stopped. And when calculate terminal, the points before pro[i] should be ignored.
		  The farthest points to them will not be determined by both ends of the current seg. using submul to judge such kind of point.
		2.originally I set the l=n to l=n-1 after the erase operation. But the state l become n-1 since the st point has erased.
		  There's a trick data in requirement of 2) if this small error is ignored.
 *Optimize Note: The operation of calculate the terminal can be optimized using dichonomy(from ed->i*k[k is least positive integer to make ed<i*k]). 
*/
