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

#define N 110
int a[N];
int n, m;

int main() {
  while (scanf("%d%d", &n, &m)!=EOF) {
    a[0] = -m - 1;
    for (int i = 1; i<=n; ++i) {
      int hr, mt;
      scanf("%d%d", &hr, &mt);
      a[i] = hr * 60 + mt;
    }
    int ans = -1;
    for (int i = 0; i<n; ++i) {
      if (a[i] + 2*m + 2 <= a[i+1]) {
        ans = a[i] + m + 1;
        break;
      }
    }
    if (!~ans) ans = a[n] + m + 1;
    printf("%d %d\n", ans / 60, ans % 60);
  }
}
