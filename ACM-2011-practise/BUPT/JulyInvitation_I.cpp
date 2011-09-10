#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

struct pnt { long long x, y; };
typedef pnt vec;
#define N 500010
pnt p[N], tmp[N], tp[N], bp[N];
int n;

int cmd(const pnt &p1, const pnt &p2)
{
	if (p1.x < p2.x) return 1; if (p1.x > p2.x) return 0;
	if (p1.y > p2.y) return 1; return 0;
}

vec getvec(const pnt &p1,const pnt &p2)
{
	vec ret;
	ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y;
	return ret;
}

long long submul(const vec &v1, const vec &v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

long long gcd(long long x, long long y) { 
	if (x == 0 || y == 0) return 1;
	if (x % y == 0) return y; else return gcd(y, x % y); }

void input()
{
	int i;
	for (i = 0; i < n; ++i) scanf("%lld %lld", &p[i].x, &p[i].y);
}

void getsort(int x, int y)
{
	if (x >= y) return;
	int i, j;
	pnt k;
	i = rand() % (y-x) + x;
	k = p[i]; p[i] = p[x];
	i = x; j = y;
	while (i < j)
	{
		while (i < j && cmd(p[j], k) == 0) --j;
		p[i] = p[j];
		while (i < j && cmd(k, p[i]) == 0) ++i;
		p[j] = p[i];
	}
	p[i] = k;
	getsort(x, i-1);
	getsort(j+1, y);
}

void getconvex()
{
	int i, top, bot;
	top = 0; tmp[0] = p[0];
	for (i = 1; i < n; ++i)
	{
		while (top > 0 && submul(getvec(tmp[top-1], tmp[top]), getvec(tmp[top], p[i])) <= 0) --top;
		tmp[++top] = p[i];
	}
	bot = top;
	for (i = n-2; i >= 0; --i)
	{
		while (top > bot && submul(getvec(tmp[top-1], tmp[top]), getvec(tmp[top], p[i])) <= 0) --top;
		tmp[++top] = p[i];
	}
	n = top;
	for (i = 0; i <= n; ++i) p[i] = tmp[i];
}

pnt lpart(long long lh, long long rh, long long l)
{
	pnt ret; long long cm;
	ret.x = llabs(lh - l); ret.y = llabs(lh - l) + llabs(rh - l);
	cm = gcd(ret.x, ret.y); ret.x /= cm; ret.y /= cm; return ret;
}

pnt rpart(long long lh, long long rh, long long l)
{
	pnt ret; long long cm;
	ret.x = llabs(rh - l); ret.y = llabs(lh - l) + llabs(rh - l);
	cm = gcd(ret.x, ret.y); ret.x /= cm; ret.y /= cm; return ret;
}

pnt uparea(long long th, long long nth, long long tl, long long bl, long long tx)
{
	pnt tmp1, tmp2;
	long long cm;
	bool col1, col2;
	pnt ret; ret.x = 0; ret.y = 1;
	if (th > tl && nth > tl) return ret;
	if (th > tl) { tmp1 = rpart(th, nth, tl); col1 = 1; }
	else if (th < bl) { tmp1 = lpart(th, nth, bl); col1 = 1; }
	else { tmp1.x = tl - th; tmp1.y = tx; col1 = 0;}	
	if (nth > tl) { tmp2 = lpart(th, nth, tl); col2 = 1; }
	else if (nth < bl) { tmp2 = rpart(th, nth, bl); col2 = 1; }
	else { tmp2.x = tl - nth; tmp2.y = tx; col2 = 0; }
	if ((col1 ^ col2)) { ret.x = tmp1.x * tmp2.x; ret.y = tmp1.y * tmp2.y; }
	else { ret.x = tmp1.x * tmp2.y + tmp2.x * tmp1.y; ret.y = tmp1.y * tmp2.y; }
	cm = gcd(ret.x, ret.y); ret.x /= cm; ret.y /= cm; return ret;
}

pnt dnarea(long long bh, long long nbh, long long tl, long long bl, long long bx)
{
	pnt tmp1, tmp2;
	long long cm;
	bool col1, col2;
	pnt ret; ret.x = 0; ret.y = 1;
	if (bh < bl && nbh < bl) return ret;
	if (bh > tl) { tmp1 = lpart(bh, nbh, tl); col1 = 1; }
	else if (bh < bl) { tmp1 = rpart(bh, nbh, bl); col1 = 1; }
	else { tmp1.x = bh - bl; tmp1.y = bx; col1 = 0; }
	if (nbh > tl) { tmp2 = rpart(bh, nbh, tl); col2 = 1; }
	else if (nbh < bl) { tmp2 = lpart(bh, nbh, bl); col2 = 1; }
	else { tmp2.x = nbh - bl; tmp2.y = bx; col2 = 0; }
	if ((col1 ^ col2)) { ret.x = tmp1.x * tmp2.x; ret.y = tmp1.y * tmp2.y; }
	else { ret.x = tmp1.x * tmp2.y + tmp2.x * tmp1.y; ret.y = tmp1.y * tmp2.y; }
	cm = gcd(ret.x, ret.y); ret.x /= cm; ret.y /= cm; return ret;
}

void conduct()
{
	int i, ti, bi, tn, bn, l, r;
	long long th, te, tx, ty, tl, bh, be, bx, by, bl, ans;
	long long nbh, nbe, nth, nte;
	pnt pnt1, pnt2, tot;
	getsort(0, n-1);
//	for (i = 0; i < n; ++i) printf("[%lld %lld] ", p[i].x, p[i].y); printf("\n");
	getconvex();
//	for (i = 0; i < n; ++i) printf("[%lld %lld] ", p[i].x, p[i].y); printf("\n");
	if (n <= 2) { printf("0\n"); return; }
	tn = 0; bn = 0; ans = 0;
	for (i = 0; i <= n; ++i) if (p[i].x < p[i+1].x) break;
	for (; p[i].x < p[i+1].x; ++i) bp[bn++] = p[i]; bp[bn++] = p[i];
	for (i = n; p[i].x < p[i-1].x; --i) tp[tn++] = p[i]; tp[tn++] = p[i];
//	for (i = 0; i < tn; ++i) printf("[%lld %lld] ", tp[i].x, tp[i].y); printf("\n");
//	for (i = 0; i < bn; ++i) printf("[%lld %lld] ", bp[i].x, bp[i].y); printf("\n");
	ti = 1; th = tp[0].y; tl = th; te = 0; tx = tp[1].x - tp[0].x; ty = tp[1].y - tp[0].y; l = tp[0].x;
	bi = 1; bh = bp[0].y; bl = bh; be = 0; bx = bp[1].x - bp[0].x; by = bp[1].y - bp[0].y; r = bp[bn-1].x;
	for (i = l+1; i <= r; ++i)
	{
		nth = th + (te+ty) / tx; nte = (te+ty) % tx;
		nbh = bh + (be+by) / bx; nbe = (be+by) % bx;
		tl = ((th + nth) * tx + te + nte + tx) / (tx * 2);
		bl = ((bh + nbh) * bx + be + nbe + bx - 1) / (bx * 2);
		while (tl > bl)
		{
			pnt1 = uparea(th * tx + te, nth * tx + nte, tl * tx, (tl-1) * tx, tx);
			pnt2 = dnarea(bh * bx + be, nbh * bx + nbe, tl * bx, (tl-1) * bx, bx);
			tot.x = pnt1.x * pnt2.y + pnt2.x * pnt1.y; tot.y = pnt1.y * pnt2.y;
			if (tot.x > tot.y) tl--; else break;
//			printf("pnt1:%lld/%lld, pnt2:%lld/%lld\n", pnt1.x, pnt1.y, pnt2.x, pnt2.y);
		}
		while (tl > bl)
		{
			pnt1 = uparea(th * tx + te, nth * tx + nte, (bl+1) * tx, bl * tx, tx);
			pnt2 = dnarea(bh * bx + be, nbh * bx + nbe, (bl+1) * bx, bl * bx, bx);
			tot.x = pnt1.x * pnt2.y + pnt2.x * pnt1.y; tot.y = pnt1.y * pnt2.y;
			if (tot.x > tot.y) bl++; else break;
//			printf("pnt1:%lld/%lld, pnt2:%lld/%lld\n", pnt1.x, pnt1.y, pnt2.x, pnt2.y);
		}
		ans += tl - bl; th = nth; te = nte; bh = nbh; be = nbe;
//		printf("[%d][th:%lld][te:%lld][bh:%lld][be:%lld][tl:%lld][bl:%lld]\n", i, th, te, bh, be, tl, bl);
		if (i == tp[ti].x) { ++ti; tx = tp[ti].x - tp[ti-1].x; ty = tp[ti].y - tp[ti-1].y; }
		if (i == bp[bi].x) { ++bi; bx = bp[bi].x - bp[bi-1].x; by = bp[bi].y - bp[bi-1].y; }
	}
	printf("%lld\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

