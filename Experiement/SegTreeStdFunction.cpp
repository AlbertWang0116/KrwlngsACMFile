#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<sys/types.h>
#include<sys/time.h>
using namespace std;

#define MICROSECONDS_PER_SECOND 1000000

vector<int> csh, sum;

struct SegNode {
  int a, b, c, d, e, f;
  SegNode() {}
  SegNode(int a, int b, int c, int d, int e, int f) : a(a), b(b), c(c), d(d), e(e), f(f) {}
};
SegNode preIds[110], pstIds[110];

inline void pre(int id, int lid, int rid, int ll, int rr, int mid) {
  sum[lid] += csh[id] * (mid - ll); sum[rid] += csh[id] * (rr - mid);
  csh[lid] += csh[id]; csh[rid] += csh[id]; csh[id] = 0;
}

void add(int l, int r, int x, int y, function<void(SegNode)> pref, function<void(SegNode)> pstf, function<void(int, int, int)> ctlf) {
  int m, low=x, pres = 1, psts = 0;
  for (m = 1; m < y-x; m <<= 1);
  preIds[0] = SegNode(1, 2, 3, low, low+m, low+(m>>1));
  for (int i = 0; i < pres; ++i) {
    SegNode v = preIds[i];
    int id = v.a, lid = v.b, rid = v.c, ll = v.d, rr = v.e, mid = v.f, nxt = (mid - ll) >> 1;
    if (l<=ll && r>=rr) { ctlf(id, ll, rr); continue; }
    pref(v); pstIds[psts++] = v;
    if (l<mid) preIds[pres++] = SegNode(lid, lid<<1, lid<<1|1, ll, mid, ll+nxt);
    if (r>mid) preIds[pres++] = SegNode(rid, rid<<1, rid<<1|1, mid, rr, mid+nxt);
  }
  for (int i = psts - 1; i >= 0; --i) pstf(pstIds[i]);
}

int check(int l, int r, int x, int y, function<void(SegNode)> pref, function<int(int, int, int)> ctlf) {
  int m, low=x, pres = 1, res = 0;
  for (m = 1; m < y-x; m <<= 1);
  preIds[0] = SegNode(1, 2, 3, low, low+m, low+(m>>1));
  for (int i = 0; i < pres; ++i) {
    SegNode v = preIds[i];
    int id = v.a, lid = v.b, rid = v.c, ll = v.d, rr = v.e, mid = v.f, nxt = (mid - ll) >> 1;
    if (l<=ll && r>=rr) { res += ctlf(id, ll, rr); continue; }
    pref(v);
    if (l<mid) preIds[pres++] = SegNode(lid, lid<<1, lid<<1|1, ll, mid, ll+nxt);
    if (r>mid) preIds[pres++] = SegNode(rid, rid<<1, rid<<1|1, mid, rr, mid+nxt);
  }
  return res;
}

int main() {
  int n = 1000, ans;
  csh.resize(n*4, 0), sum.resize(n*4, 0);
  timeval st, ed;
  gettimeofday(&st, NULL);
  auto pref = [](SegNode v) { pre(v.a, v.b, v.c, v.d, v.e, v.f); };
  auto pstf = [&](SegNode v) { sum[v.a] = sum[v.b] + sum[v.c]; };
  auto addf = [&](int id, int ll, int rr) { csh[id]++; sum[id] += rr - ll; };
  auto sumf = [&](int id, int ll, int rr) -> int { return sum[id]; };
  for (int i = 0; i<n; ++i) for (int j = i+1; j<=n; ++j) add(i, j, 0, n, pref, pstf, addf);
  for (int i = 0; i<n; ++i) {
    ans = check(i, i+1, 0, n, pstf, sumf);
//    printf("i:%d ans:%d\n", i, ans);
  }
  gettimeofday(&ed, NULL);
  printf("latency: %.8f\n", (ed.tv_sec * MICROSECONDS_PER_SECOND + ed.tv_usec - st.tv_sec * MICROSECONDS_PER_SECOND - st.tv_usec) / (double)MICROSECONDS_PER_SECOND);
}
