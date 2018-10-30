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

#define N 610000
int a[N], seq[N];
int n, x, y;

int cmp(const int &i, const int &j) { return a[i]>a[j]; }

int findsteps(int val, int *seq) {
  for (int i = 0; i<n && ~seq[i]; i = (val-1)/a[seq[i]]) {
    if (a[seq[i]]*(i+1) >= val) return i+1;
  }
  return 0;
}

void printresult(int s1, int e1, int s2, int e2) {
  printf("Yes\n");
  printf("%d %d\n", e1-s1, e2-s2);
  for (int i = s1; i < e1; ++i) printf("%d ", seq[i]+1);
  printf("\n");
  for (int i = s2; i < e2; ++i) printf("%d ", seq[i]+1);
  printf("\n");
}

int main() {
  while (scanf("%d%d%d", &n, &x, &y)!=EOF) {
    memset(a, 0, sizeof(a));
    memset(seq, -1, sizeof(seq));
    for (int i = 0; i<n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i<n; ++i) seq[i] = i;
    sort(seq, seq+n, cmp);
    int k1, k2;
    k1 = findsteps(x, seq);
    if (k1) {
      k2 = findsteps(y, seq+k1);
      if (k2) {
        printresult(0, k1, k1, k1+k2);
        continue;
      }
    }
    k2 = findsteps(y, seq);
    if (k2) {
      k1 = findsteps(x, seq+k2);
      if (k1) {
        printresult(k2, k1+k2, 0, k2);
        continue;
      }
    }
    printf("No\n");
  }
}
