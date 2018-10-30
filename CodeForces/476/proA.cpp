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

int main() {
  int k, n, s, p;
  while (scanf("%d%d%d%d", &k, &n, &s, &p) != EOF) {
    int ans = (((n-1)/s+1)*k-1)/p+1;
    printf("%d\n", ans);
  }
}
