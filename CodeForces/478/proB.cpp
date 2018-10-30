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

#define N 14
int a[N], b[N];

int main() {
  while (scanf("%d", &a[0])!=EOF) {
    for (int i = 1; i<N; ++i) scanf("%d", &a[i]);
    long long ans = 0;
    for (int i = 0; i<N; ++i) {
      if (!(a[i]&1)) continue;
      memcpy(b, a, sizeof(a));
      int tot = a[i], div = a[i] / N, rem = a[i] % N;
      b[i] = 0; 
      for (int j = 0; j<N; ++j) b[j] += div;
      for (int j = 0, k = i+1; j<rem; ++j, ++k) {
        if (k == N) k = 0;
        b[k]++;
      }
      long long cur = 0L;
      for (int i = 0; i<N; ++i)
        if (!(b[i]&1)) cur += b[i];
      if (cur > ans) ans = cur;
    }
    cout << ans << endl;
  }
}
