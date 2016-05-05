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
inline int getmax(int x, int y) { return x>y?x:y; }
typedef int (*avl_cmp)(const int &, const int &);

struct avl {
  int lft, rit, pa;
  int *ptr;
  int id;
  int lftDep, ritDep;
};

class avl_tree {
public:
  avl *tree;
  int root, avlCount;
  avl_cmp cmp;

  inline int empty() {
    return root == 0;
  }

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
    avl_rotate_op(nodes, ptrs);
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

  void avl_swap_node(int n1, int n2) {
    int tmp = tree[n1].id;
    tree[n1].id = tree[n2].id;
    tree[n2].id = tmp;
  }

  int *avl_find(int id, int *pa) {
    *pa = 0;
    int *res = &root;
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
      avl_swap_node(chd, nxtChd); chd = nxtChd;
    }
    while (tree[chd].rit) {
      int nxtChd = tree[chd].rit;
      while (tree[nxtChd].lft) nxtChd = tree[nxtChd].lft;
      avl_swap_node(chd, nxtChd); chd = nxtChd;
    }
    *tree[chd].ptr = 0;
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

  void avl_init() {
    root = 0;
    avlCount = 0;
    memset(&tree[0], 0, sizeof(avl));
  }

  avl_tree(int size, avl_cmp cmp) {
    tree = new avl[size];
    this->cmp = cmp;
  }
};

int val[N];
int cur, n, q;
long long ans;
avl_tree *pref[2];

int cmp_min(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i]<val[j];
}

int cmp_max(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i]>val[j];
}

avl_tree lft = avl_tree(N, &cmp_max), rit = avl_tree(N, &cmp_min);

void conduct() {
  scanf("%d%d", &n, &q);
  cur = n = ans = 0;
  lft.avl_init(); rit.avl_init();
  pref[0] = &rit; pref[1] = &lft;
  while (q--) {
    int cmd;
    scanf("%d", &cmd);
    if (cmd) {
      int id1 = pref[0]->tree[pref[0]->avl_head()].id;
      int id2 = pref[1]->tree[pref[1]->avl_head()].id;
      if (!pref[0]->empty() && (abs(cur-val[id1]) <= abs(cur-val[id2]) || pref[1]->empty())) {
        ans += abs(cur-val[id1]);
        cur = val[id1];
        pref[0]->avl_remove(id1);
      }
      else if (!pref[1]->empty()) {
        ans += abs(cur-val[id2]);
        cur = val[id2];
        pref[1]->avl_remove(id2);
        avl_tree* tmp = pref[0];
        pref[0] = pref[1];
        pref[1] = tmp;
      }
    }
    else {
      int pos;
      scanf("%d", &pos);
      if (n == N-1) while (1);
      val[++n] = pos;
      if (val[n] == cur) pref[0]->avl_insert(n);
      else if (val[n] < cur) lft.avl_insert(n);
      else rit.avl_insert(n);
    }
  }
  cout << ans << endl;
}

int main() {
  int time; scanf("%d", &time);
  for (int i = 1; i<=time; ++i) {
    printf("Case %d: ", i);
    conduct();
  }
  return 0;
}
