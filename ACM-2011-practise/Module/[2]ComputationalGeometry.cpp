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
		p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		if (ang[seq[i]] > -eps) break;
	} p[bot] = (pnt){ -inf*2, -inf*2 };
	for (++i; i < n; ++i) {
		if (oridis(l[seq[i]], p[bot]) > -eps) continue;
		while (top - bot && oridis(l[seq[i]], p[top]) < -eps) --top;
		if (top == bot) break; p[top+1] = getcrs(l[seq[i]], l[seq[top]]); seq[++top] = seq[i];
		while (oridis(l[seq[top]], p[bot+1]) < -eps) ++bot; p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
	} if (i < n) return 0;
	for (ret = 0, i = bot; i < top; ++i) if (fabs(p[i].x-p[i+1].x)>eps || fabs(p[i].y-p[i+1].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} if (!ret || fabs(p[i].x-p[0].x)>eps || fabs(p[i].y-p[0].y)>eps) {
		seq[ret] = seq[i]; p[ret] = p[i]; ret++;
	} return ret;
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
