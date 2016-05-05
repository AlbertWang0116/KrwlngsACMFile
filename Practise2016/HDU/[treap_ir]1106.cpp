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

struct treap {
  int lft, rit, pa;
  int *ptr;
  int id;
  long long wgt;
};
#define N 110000
int root, treapCount;
treap tree[N];

inline int cmp(const int &i, const int &j);
inline long long weight(int node) { return node ? tree[node].wgt : -2L; }

void treap_rotate_op(int *nodes, int **ptrs) {
  for (int i = 0; i<3; ++i) {
    tree[nodes[i+1]].pa = nodes[i];
    tree[nodes[i+1]].ptr = ptrs[i];
    *ptrs[i] = nodes[i+1];
  }
}

void treap_clock_rotate(int node) {
  int lftChd = tree[node].lft;
  int lftRitChd = tree[lftChd].rit;
  int nodes[4] = { tree[node].pa, lftChd, node, lftRitChd };
  int *ptrs[4] = { tree[node].ptr, &(tree[lftChd].rit), &(tree[node].lft), NULL };
  treap_rotate_op(nodes, ptrs);
}

void treap_aclock_rotate(int node) {
  int ritChd = tree[node].rit;
  int ritLftChd = tree[ritChd].lft;
  int nodes[4] = { tree[node].pa, ritChd, node, ritLftChd };
  int *ptrs[4] = { tree[node].ptr, &(tree[ritChd].lft), &(tree[node].rit), NULL };
  treap_rotate_op(nodes, ptrs);
}

void treap_balance(int *node) {
  while (*node) {
    long long lftWgt = weight(tree[*node].lft), ritWgt = weight(tree[*node].rit), wgt = weight(*node);
    if (wgt < lftWgt || wgt < ritWgt)
      if (lftWgt > ritWgt) treap_clock_rotate(*node);
      else treap_aclock_rotate(*node);
    else break;
  }
}

int *treap_find(int id, int *pa) {
  *pa = 0;
  int *res = &root;
  for (int nxtPa = *res; *res; *pa = nxtPa, nxtPa = *res)
    if (cmp(id, tree[*res].id)) res = &(tree[*res].lft);
    else if (cmp(tree[*res].id, id)) res = &(tree[*res].rit);
    else break;
  return res;
}

void treap_insert(int id) {
  int pa = 0;
  int *ptr = treap_find(id, &pa);
  if (*ptr) return;
  memset(&tree[++treapCount], 0, sizeof(treap));
  tree[treapCount].id = id;
  tree[treapCount].ptr = ptr;
  tree[treapCount].pa = pa;
  *ptr = treapCount;
  tree[treapCount].wgt = (long long)rand() % N * N + rand() % N;
  treap_balance(&(tree[treapCount].pa));
}

void treap_remove(int id) {
  int node = *treap_find(id, &node);
  if (!node) return;
  tree[node].wgt = -1L;
  treap_balance(&node);
  *tree[node].ptr = 0;
}

int treap_head() {
  for (int res = root; ; res = tree[res].lft)
    if (!tree[res].lft) return res;
}

#define M 11000
char str[M];
int val[M];
int n;

inline int cmp(const int &i, const int &j) {
  if (val[i] == val[j]) return i < j;
  return val[i] < val[j];
}

void conduct() {
  memset(&tree[0], 0, sizeof(treap));
  root = treapCount = 0;
  n = 0; val[0] = -1;
  for (int i = 0, j = strlen(str); i <= j; ++i) {
    if (i < j && str[i] != '5') {
      if (!~val[n]) val[n] = 0;
      val[n] = val[n]*10+str[i]-'0';
    }
    else if (~val[n]) val[++n] = -1;
  }
  for (int i = 0; i<n; ++i) treap_insert(i);
  for (int i = 0; i<n; ++i) {
    int node = treap_head();
    if (i) printf(" ");
    printf("%d", val[tree[node].id]);
    treap_remove(tree[node].id);
  }
  printf("\n");
}

int main() {
  while (scanf("%s", str)!=EOF) conduct();
  return 0;
}
