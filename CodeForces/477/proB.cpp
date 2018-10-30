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
int a[N];
int n, tot, des;

int main() {
  while (scanf("%d%d%d", &n, &tot, &des)!=EOF) {
    for (int i = 0; i<n; ++i) scanf("%d", &a[i]);
    int sum = 0;
    for (int i = 0; i<n; ++i) sum += a[i];
    int bar = a[0] * tot / des;
    sort(a+1, a+n);
    int ans = 0;
    for (int i = n-1; i && sum > bar; --i, ++ans) {
      sum -= a[i];
    }
    printf("%d\n", ans);
  }
}
