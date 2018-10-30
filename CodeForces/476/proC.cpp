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

const long long N = 1000000000000000000L;
long long tot, k, up, ans;
int m;

inline long long getmin(long long x, long long y) { return x<y?x:y; }
inline long long getmax(long long x, long long y) { return x>y?x:y; }

long long divide(int rep) {
  if (N / rep < k) return 0L;
  return tot / (rep * k + 1);
}

long long cal(int rep) {
  long long st = divide(rep) + 1;
  long long ed;
  if (rep == 1) ed = up; else ed = getmin(up, divide(rep-1));
  if (st <= ed) return ed * rep;
  else return 0L;
}

int main() {
  while (cin >> tot >> k >> up >> m) {
    ans = 0L;
    for (int i = 1; i<=m; ++i) ans = getmax(ans, cal(i));
    cout << ans << endl;
  }
}
