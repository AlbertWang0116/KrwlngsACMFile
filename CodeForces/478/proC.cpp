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

#define READ_NUM(_param) {\
    char ch; \
    while ((ch = getchar()) < '0' || ch > '9'); \
    _param = ch - '0'; \
    while ((ch = getchar()) >= '0' && ch <= '9') _param = _param * 10 + ch - '0'; \
  }

#define N 210000
long long a[N];
int n, m;

int main() {
  while (scanf("%d%d", &n, &m)!=EOF) { 
    for (int i = 0; i<n; ++i) READ_NUM(a[i]);
    for (int i = 1; i<n; ++i) a[i] += a[i-1];
    long long cur = 0L, dlt;
    for (int i = 0; i<m; ++i) {
      READ_NUM(dlt);
      cur += dlt;
      if (cur >= a[n-1]) cur = 0L;
      int lft = 0, rit = n-1;
      while (lft < rit) {
        int mid = (lft+rit) >> 1;
        if (a[mid] <= cur) lft = mid+1;
        else rit = mid;
      }
      printf("%d\n", n-rit);
    }
  }
}
