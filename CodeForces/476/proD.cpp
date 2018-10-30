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

#define N 110000
int a[N], b[N];
int n, m;

#define sizecal(__num, __type) __num*sizeof(__type)
inline int getmin(int x, int y) { return x<y?x:y; }

int main() {
  while (scanf("%d%d", &n, &m)!=EOF) {
    --n;
    for (int i = 0; i<n; ++i) scanf("%d", &a[i]);
    memset(b, 0, sizecal(N, int));
    for (int i = 0; i<m; ++i) b[i] = a[i];
    for (int i = m, j = 0; i<n; ++i) {
      if (j < i - m) j = i - m;
      while (j<i && b[i] < a[i]) {
        int k = getmin(a[i] - b[i], b[j]);
        b[j] -= k;
        b[i] += k;
        if (!b[j]) ++j;
      }
    }
    int ans = 0;
    for (int i = n-m; i<n; ++i) ans += b[i];
    printf("%d\n", ans);
  }
}
