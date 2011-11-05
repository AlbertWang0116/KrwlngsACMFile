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
