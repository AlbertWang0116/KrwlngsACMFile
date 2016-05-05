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

#define N 11000
struct avl {
  int lft, rit, pa;
  int lftDep, ritDep;
  int id;
  int *ptr;
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
  if (!node) return;
  tree[node].lftDep = depth(tree[node].lft);
  tree[node].ritDep = depth(tree[node].rit);
}

void avl_rotate_op(int *nodes, int **ptrs) {
  for (int i = 0; i<3; ++i) {
    tree[nodes[i+1]].pa = nodes[i];
    tree[nodes[i+1]].ptr = ptrs[i];
    *ptrs[i] = nodes[i+1];
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
}

void avl_balance(int node) {
  for (int cur = node; cur; cur = tree[cur].pa) {
    avl_update_depth(cur);
    int bal = balance(cur);
    if (bal > 1) {
      int chdBal = balance(tree[cur].lft);
      if (chdBal < 0) avl_aclock_rotate(tree[cur].lft);
      avl_clock_rotate(cur);
    }
    else if (bal < -1) {
      int chdBal = balance(tree[cur].rit);
      if (chdBal > 0) avl_clock_rotate(tree[cur].rit);
      avl_aclock_rotate(cur);
    }
  }
}

int *avl_find(int id, int *pa) {
  *pa = 0;
  int *res = &root;
  for (int nxtPa = *res; *res; *pa = nxtPa, nxtPa = *res)
    if (cmp(id, tree[*res].id)) res = &(tree[*res].lft);
    else if (cmp(tree[*res].id, id)) res = &(tree[*res].rit);
    else break;
  return res;
}

void avl_insert(int id) {
  int pa = 0;
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
    tree[chd].id = tree[nxtChd].id; chd = nxtChd;
  }
  while (tree[chd].rit) {
    int nxtChd = tree[chd].rit;
    while (tree[nxtChd].lft) nxtChd = tree[nxtChd].lft;
    tree[chd].id = tree[nxtChd].id; chd = nxtChd;
  }
  *tree[chd].ptr = 0;
  avl_balance(tree[chd].pa);
}

int avl_find_least(int id) {
  int res = 0;
  for (int cur = root; cur; )
    if (cmp(id, tree[cur].id)) {
      res = cur;
      cur = tree[cur].lft;
    }
    else cur = tree[cur].rit;
  return res;
}

int val[N];
char name[N][15];
int n;

int cmp(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i]<val[j];
}

void conduct() {
  avlCount = root = 0;
  memset(&tree[0], 0, sizeof(avl));
  scanf("%d", &n);
  int tot = 0;
  for (int i = 1; i<=n; ++i) {
    char cmd[10];
    scanf("%s", cmd);
    if (cmd[0] == 'A') {
      scanf("%s%d", name[i], &val[i]);
      avl_insert(i);
      printf("%d\n", ++tot);
    }
    else {
      scanf("%d", &val[i]); --val[i];
      int node = avl_find_least(i);
      if (!node) printf("WAIT...\n");
      else {
        int index = tree[node].id;
        printf("%s\n", name[index]);
        avl_remove(index);
        --tot;
      }
    }
  }
}

int main() {
  int time; scanf("%d", &time);
  for (int i = 1; i<=time; ++i) {
    printf("Case #%d:\n", i);
    conduct();
  }
  return 0;
}
