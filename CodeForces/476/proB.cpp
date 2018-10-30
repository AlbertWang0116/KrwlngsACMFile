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
#define sizecal(__type, __length) sizeof(__type)*__length
char spc[N][N], spc2[N][N], str[N];
int sum[N][N], sum2[N][N], dlt[N];
int n, m;

void counter(char spc[][N], int sum[][N]) {
  memset(sum, 0, sizecal(int, N*N));
  for (int i = 0; i<n; ++i) {
    memset(dlt, 0, sizecal(int, N));
    for (int j = 0, k = 0; j<n; ++j) {
      if (spc[i][j] == '.') {
        if (++k >= m) {
          dlt[j-m+1]++;
          dlt[j+1]--;
        }
      }
      else k = 0;
    }
    for (int j = 0, k = 0; j<n; ++j) {
      k += dlt[j];
      sum[i][j] = k;
    }
  }
}

int main() {
  while (scanf("%d%d", &n, &m)!=EOF) {
    for (int i = 0; i<n; ++i) {
      scanf("%s", str);
      for (int j = 0; j<n; ++j) {
        spc[i][j] = str[j];
        spc2[j][i] = str[j];
      }
    }
    counter(spc, sum);
    counter(spc2, sum2);
    for (int i = 0; i<n; ++i)
      for (int j = 0; j<n; ++j) sum[i][j] += sum2[j][i];
    int row = 1, col = 1, val = 0;
    for (int i = 0; i<n; ++i)
      for (int j = 0; j<n; ++j) {
        if (sum[i][j] > val) {
          val = sum[i][j];
          row = i+1;
          col = j+1;
        }
      }
    printf("%d %d\n", row, col);
  }
}
