/*
 * 解题报告：
 * 结论：对于每个bit位i，最高位是i的数字的个数小于最高位不是i但i位为1的数字的个数+1。
 * 构造方法：每次基于当前的a值，找到a最小未被置为1的bit位，在未被使用的数中若存在一个数，其最高位为i，则该数是下一个b；
 *           否则找次小的未被置为1的bit位，以此类推。
 * 根据构造方法的推论：若某次选出的数b将当前a的一个非其最高位的bit位j置为1，则剩余数中不存在未被使用的、最高位为j的数。
 *                     （否则b会被该数取代）
 * 结论证明：
 *     =>：选出的数b的最高位i在当前a中必须为0，否则异或后结果变小。因此当a的位i被b置为1后，a需要被一个最高位大于i、且
           i位为1的数b'将第i位重新置为0 - 否则a无法与下一个最高位是i的数b"进行异或。
 *     <=：若上述构造方法无法用完所有的数，则找到剩余数中最高位最大的一个数，设其bit位为i。已知bit位高于i的所有数已经
           用尽，最高bit位为i的数已使用了x个(x>=1，因为此时a的i位为1)。根据构造方法的推论可知，bit位高于i且i位为1的数
           字个数为x-1，然而最高bit位为i的数至少有x+1个（已使用x个和剩余至少1个）。
 */
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

#define BIT 63
#define N 110000
struct {
  long long val;
  int next;
} node[N];
long long bit[BIT];
int a[BIT], b[BIT], head[BIT];
int n, cnt;
char str[BIT];

void init() {
  for (long long i = 0, j = 1; i < BIT; ++i, j <<= 1) bit[(int)i] = j;
}

void clear() {
  cnt = 0;
}

void insert(int x, long long val) {
  ++cnt;
  node[cnt].val = val;
  node[cnt].next = head[x];
  head[x] = cnt;
}

bool empty(int x) { return !head[x]; }

long long consume(int x) {
  long long ret = node[head[x]].val;
  head[x] = node[head[x]].next;
  return ret;
}

void work() {
  for (int i = 0; i<BIT; ++i)
    if (a[i] > b[i]+1) {
      printf("No\n");
      return;
    }
  printf("Yes\n");
  long long val = 0;
  while (1) {
    for (int i = 0; i<BIT; ++i) {
      if (i == BIT-1) {
        printf("\n");
        return;
      }
      if (!empty(i) && !(val&bit[i])) {
        long long next = consume(i);
        cout << next << " ";
        val ^= next;
        break;
      }
    }
  }
}

int main() {
  init();
  while (scanf("%d", &n)!=EOF) {
    clear();
    memset(head, 0, sizeof(head));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    long long val;
    for (int i = 0; i<n; ++i) {
      scanf("%s", str);
      val = 0;
      for (int i = 0, j = strlen(str); i<j; ++i) val = val * 10 + str[i] - '0';
      for (int i = 0; i<BIT; ++i)
        if (val&bit[i]) {
          if (val-bit[i] > bit[i]) b[i]++;
          else {
            a[i]++;
            insert(i, val);
            break;
          }
        }
    }
    work();
  }
}
