//This section is about the incremental method


//calculate the convex of the combine of several half plane, output the number of distinct point at the border of the answer, as well as each point and line in counter-clockwise order.
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
		if (ang[seq[i]] > eps) break;
	} p[bot] = getcrs(l[seq[top]], l[seq[bot]]);
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
