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

#define N 1010
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

void avl_update_depth(int node) {
  tree[node].lftDep = depth(tree[node].lft);
  tree[node].ritDep = depth(tree[node].rit);
}

void avl_rotate_op(int *nodes, int **ptrs) {
  for (int i = 0; i<3; ++i) {
    *ptrs[i] = nodes[i+1];
    tree[nodes[i+1]].ptr = ptrs[i];
    tree[nodes[i+1]].pa = nodes[i];
  }
  for (int i = 2; ~i; --i) avl_update_depth(nodes[i]);
}

void avl_clock_rotate(int node) {
  int lftChd = tree[node].lft;
  int lftRitChd = tree[lftChd].rit;
  int nodes[4] = { tree[node].pa, lftChd, node, lftRitChd };
  int *ptrs[4] = { tree[node].ptr, &(tree[lftChd].rit), &(tree[node].lft), NULL };
  avl_rotate_op(nodes, ptrs);
}

void avl_aclock_rotate(int node) {
  int ritChd = tree[node].rit;
  int ritLftChd = tree[ritChd].lft;
  int nodes[4] = { tree[node].pa, ritChd, node, ritLftChd };
  int *ptrs[4] = { tree[node].ptr, &(tree[ritChd].lft), &(tree[node].rit), NULL };
  avl_rotate_op(nodes, ptrs);
}

void avl_balance(int node) {
  for (int cur = node; cur; cur = tree[cur].pa) {
    avl_update_depth(cur);
    int curBal = balance(cur);
    if (curBal > 1) {
      int chdBal = balance(tree[cur].lft);
      if (chdBal < 0) avl_aclock_rotate(tree[cur].lft);
      avl_clock_rotate(cur);
    }
    else if (curBal < -1) {
      int chdBal = balance(tree[cur].rit);
      if (chdBal > 0) avl_clock_rotate(tree[cur].rit);
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

int *avl_find(int id, int *pa) {
  int *res = &root;
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
  tree[avlCount].ptr = ptr;
  tree[avlCount].pa = pa;
  *ptr = avlCount;
  avl_balance(avlCount);
}

void avl_remove(int id) {
  int chd = *avl_find(id, &chd);
  if (!chd) return;
  while (tree[chd].lft) {
    int newChd = tree[chd].lft;
    while (tree[newChd].rit) newChd = tree[newChd].rit;
    avl_swap_node(chd, newChd); chd = newChd;
  }
  while (tree[chd].rit) {
    int newChd = tree[chd].rit;
    while (tree[newChd].lft) newChd = tree[newChd].lft;
    avl_swap_node(chd, newChd); chd = newChd;
  }
  *(tree[chd].ptr) = 0;
  avl_balance(tree[chd].pa);
}

int avl_head() {
  int res = root;
  while (tree[res].lft) res = tree[res].lft;
  return res;
}

int val[N];
char str[N];
int n;

int cmp(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i]<val[j];
}

void conduct() {
  avl_init();
  int n = 0;
  int len = strlen(str);
  for (int i = 0, j = 0; i<len; ) {
    while (j<len && str[j] == '5') j++;
    if (j<len) {
      val[n] = 0;
      while (j<len && str[j] != '5') val[n] = val[n]*10 + str[j++] - '0';
      n++;
    }
    i = j;
  }
  for (int i = 0; i<n; ++i) avl_insert(i);
  for (int i = 0; i<n; ++i) {
    int node = avl_head();
    if (i) printf(" ");
    printf("%d", val[tree[node].id]);
    avl_remove(tree[node].id);
  }
  printf("\n");
}

int main() {
  while (scanf("%s", str)!=EOF) conduct();
  return 0;
}
