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

#define N 1100
int a[N];
char str[N];
int n;

int main() {
  while (scanf("%d", &n)!=EOF) {
    for (int i = 0; i<n; ++i) {
      scanf("%s", str);
      int flag = 0;
      for (int i = 0, j = strlen(str); i<j; ++i) {
        flag |= 1<<(str[i]-'a');
      }
      a[i] = flag;
    }
    sort(a, a+n);
    int ans = 1;
    for (int i = 1; i<n; ++i)
      if (a[i] != a[i-1]) ans++;
    printf("%d\n", ans);
  }
}
