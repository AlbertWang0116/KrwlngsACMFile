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
struct avl {
  int lft, rit, pa;
  int *ptr;
  int lftDep, ritDep;
  int id;
};
int root, avlCount;
avl tree[N];
int cmp(const int &i, const int &j);

inline int getmax(int x, int y) { return x>y?x:y; }

inline int depth(int node) {
  return node ? getmax(tree[node].lftDep, tree[node].ritDep)+1 : 0;
}

inline int balance(int node) {
  return tree[node].lftDep - tree[node].ritDep;
}

void update_depth(int node) {
  tree[node].lftDep = depth(tree[node].lft);
  tree[node].ritDep = depth(tree[node].rit);
}

void avl_rotate_op(int* nodes, int** ptrs) {
  for (int i = 0; i<3; ++i) {
    *ptrs[i] = nodes[i+1];
    tree[nodes[i+1]].pa = nodes[i];
    tree[nodes[i+1]].ptr = ptrs[i];
  }
  for (int i = 2; ~i; --i) update_depth(nodes[i]);
}

void avl_clock_rotate(int node) {
  int lftChd = tree[node].lft;
  int lftRitChd = tree[lftChd].rit;
  int nodes[4] = { tree[node].pa, lftChd, node, lftRitChd };
  int* ptrs[4] = { tree[node].ptr, &(tree[lftChd].rit), &(tree[node].lft), NULL };
  avl_rotate_op(nodes, ptrs);
}

void avl_aclock_rotate(int node) {
  int ritChd = tree[node].rit;
  int ritLftChd = tree[ritChd].lft;
  int nodes[4] = { tree[node].pa, ritChd, node, ritLftChd };
  int* ptrs[4] = { tree[node].ptr, &(tree[ritChd].lft), &(tree[node].rit), NULL };
  avl_rotate_op(nodes, ptrs);
}

void avl_balance(int node) {
  for (int cur = node; cur; cur = tree[cur].pa) {
    update_depth(cur);
    int curBal = balance(cur);
    if (curBal > 1) {
      int subBal = balance(tree[cur].lft);
      if (subBal < 0) avl_aclock_rotate(tree[cur].lft);
      avl_clock_rotate(cur);
    }
    else if (curBal < -1) {
      int subBal = balance(tree[cur].rit);
      if (subBal > 0) avl_clock_rotate(tree[cur].rit);
      avl_aclock_rotate(cur);
    }
  }
}

void avl_swap_node(int n1, int n2) {
  int tmp = tree[n1].id;
  tree[n1].id = tree[n2].id;
  tree[n2].id = tmp;
}

void avl_init() {
  root = 0;
  avlCount = 0;
  memset(&tree[0], 0, sizeof(avl));
}

int* avl_find(int id, int *pa) {
  int* res = &root;
  *pa = 0;
  for (int nxtPa = *res; *res; *pa = nxtPa, nxtPa = *res) {
    if (cmp(id, tree[*res].id)) res = &(tree[*res].lft);
    else if (cmp(tree[*res].id, id)) res = &(tree[*res].rit);
    else break;
  }
  return res;
}

void avl_insert(int id) {
  int pa;
  int *ptr = avl_find(id, &pa);
  if (*ptr) return;
  memset(&tree[++avlCount], 0, sizeof(avl));
  tree[avlCount].id = id;
  tree[avlCount].pa = pa;
  tree[avlCount].ptr = ptr;
  *ptr = avlCount;
  avl_balance(avlCount);
}

void avl_remove(int id) {
  int chd = *avl_find(id, &chd);
  if (!chd) return;
  while (tree[chd].lft) {
    int nxtChd = tree[chd].lft;
    while (tree[nxtChd].rit) nxtChd = tree[nxtChd].rit;
    avl_swap_node(chd, nxtChd);
    chd = nxtChd;
  }
  while (tree[chd].rit) {
    int nxtChd = tree[chd].rit;
    while (tree[nxtChd].lft) nxtChd = tree[nxtChd].lft;
    avl_swap_node(chd, nxtChd);
    chd = nxtChd;
  }
  *(tree[chd].ptr) = 0;
  avl_balance(tree[chd].pa);
}

int avl_head() {
  int res = root;
  while (tree[res].lft) res = tree[res].lft;
  return res;
}

int avl_tail() {
  int res = root;
  while (tree[res].rit) res = tree[res].rit;
  return res;
}

int avl_next(int node) {
  if (tree[node].rit) {
    int res = tree[node].rit;
    while (tree[res].lft) res = tree[res].lft;
    return res;
  }
  else {
    int res = tree[node].pa;
    while (res && cmp(tree[res].id, tree[node].id)) res = tree[res].pa;
    return res;
  }
}

int avl_prev(int node) {
  if (tree[node].lft) {
    int res = tree[node].lft;
    while (tree[res].rit) res = tree[res].rit;
    return res;
  }
  else {
    int res = tree[node].pa;
    while (res && cmp(tree[node].id, tree[res].id)) res = tree[res].pa;
    return res;
  }
}

char b[N];
double a[N];
int n, m, q;
const double eps = 1e-6;

int cmp(const int &i, const int &j) {
  if (fabs(a[i]-a[j])<eps) return i<j;
  return a[i]-a[j]>eps;
}

void conduct() {
  for (int i = 0; i<m; ++i) a[i] = 0.0;
  memset(b, 0, sizeof(b));
  for (int i = 0; i<n; ++i) {
    for (int j = 0; j<m; ++j) {
      double tmp;
      scanf("%lf", &tmp);
      a[j] += tmp;
    }
  }
  avl_init();
  for (int i = 0; i<m; ++i) avl_insert(i);
  for (int cur = avl_head(), i = 0; i<q; cur = avl_head(), ++i) {
    b[tree[cur].id]++;
    avl_remove(tree[cur].id);
  }
  for (int i = m-1, j = 0; ~i; --i)
    if (b[i]) {
      if (j) printf(" ");
      printf("%d", i+1);
      j++;
    }
  printf("\n");
}

int main() {
  while (scanf("%d%d%d", &n, &m, &q)!=EOF) conduct();
  return 0;
}
