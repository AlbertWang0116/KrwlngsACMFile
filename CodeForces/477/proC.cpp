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
using namespace std;

#define M 2000000001
#define N 110000
int a[N], b[N];
int unused, n, m, vlo, q, sr, sc, er, ec;

inline int getmin(int x, int y) { return x<y?x:y; }

int bsearch(int x, int *a, int len) {
  int st = 0, ed = len;
  while (st<ed) {
    int mid = ((st+ed) >> 1)+1;
    if (x>=a[mid]) st = mid;
    else ed = mid-1;
  }
  return st;
}

int main() {
  while (scanf("%d%d%d%d%d", &unused, &unused, &n, &m, &vlo)!=EOF) {
    a[0] = b[0] = 0;
    for (int i = 1; i<=n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i<=m; ++i) scanf("%d", &b[i]);
    scanf("%d", &q);
    while (q--) {
      scanf("%d%d%d%d", &sr, &sc, &er, &ec);
      if (sr == er) {
        printf("%d\n", abs(sc-ec));
        continue;
      }
      int ta = abs(sr-er);
      int tb = (ta-1)/vlo + 1;
      int ans = M;
      int pa = bsearch(sc, a, n);
      if (pa>0) ans = getmin(ans, abs(sc-a[pa])+ta+abs(ec-a[pa]));
      if (pa<n) ans = getmin(ans, abs(sc-a[pa+1])+ta+abs(ec-a[pa+1]));
      int pb = bsearch(sc, b, m);
      if (pb>0) ans = getmin(ans, abs(sc-b[pb])+tb+abs(ec-b[pb]));
      if (pb<m) ans = getmin(ans, abs(sc-b[pb+1])+tb+abs(ec-b[pb+1]));
      printf("%d\n", ans);
    }
  }
}
