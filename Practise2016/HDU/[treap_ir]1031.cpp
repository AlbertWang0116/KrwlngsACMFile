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
  int lft, rit, id;
  long long wgt;
  int *ptr;
  int pa;
};

#define N 110000
treap tree[N];
int root, treapCount;
int cmp(const int &i, const int &j);

inline long long weight(int node) { return node ? tree[node].wgt : (long long)-N; }

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
    long long lftWgt = weight(tree[*node].lft), ritWgt = weight(tree[*node].rit);
    if (tree[*node].wgt < lftWgt || tree[*node].wgt < ritWgt) {
      if (lftWgt > ritWgt) treap_clock_rotate(*node);
      else treap_aclock_rotate(*node);
    }
    else break;
  }
}

int *treap_find(int id, int *pa) {
  int *res = &root;
  *pa = 0;
  for (int nxtPa = *res; *res; *pa = nxtPa, nxtPa = *res) {
    if (cmp(id, tree[*res].id)) res = &(tree[*res].lft);
    else if (cmp(tree[*res].id, id)) res = &(tree[*res].rit);
    else break;
  }
  return res;
}

void treap_insert(int id) {
  int pa;
  int *ptr = treap_find(id, &pa);
  if (*ptr) return;
  memset(&tree[++treapCount], 0, sizeof(treap));
  tree[treapCount].id = id;
  tree[treapCount].pa = pa;
  tree[treapCount].ptr = ptr;
  tree[treapCount].wgt = (long long)rand() % N * N + rand() % N;
  *ptr = treapCount;
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

double val[N];
char tag[N];
int n, m, q;

int cmp(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i]>val[j];
}

void conduct() {
  root = 0; treapCount = 0;
  memset(&tree[0], 0, sizeof(treap));
  for (int i = 0; i<m; ++i) val[i] = 0.0;
  for (int i = 0; i<n; ++i)
    for (int j = 0; j<m; ++j) {
      double tmp; scanf("%lf", &tmp);
      val[j] += tmp;
    }
  memset(tag, 0, sizeof(tag));
  for (int i = 0; i<m; ++i) treap_insert(i);
  for (int i = 0; i<q; ++i) {
    int node = treap_head();
    tag[tree[node].id]++;
    treap_remove(tree[node].id);
  }
  for (int i = m-1, j = 0; ~i; --i) {
    if (tag[i]) {
      if (j) printf(" ");
      printf("%d", i+1);
      j++;
    }
  }
  printf("\n");
}

int main() {
  while (scanf("%d%d%d", &n, &m, &q)!=EOF) conduct();
  return 0;
}
