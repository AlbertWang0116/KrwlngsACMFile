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

int cmp(const int &i, const int &j);
inline int getmax(int x, int y) { return x>y?x:y; }

struct avl {
  int lft, rit, pa;
  int *ptr;
  int lftDep, ritDep;
  int id, count;
};

#define K 520000
avl tree[K];
int avlCount;

void avl_global_init() {
  avlCount = 0;
  memset(&tree[0], 0, sizeof(avl));
}

class avl_tree {
public:
  int root;

  int depth(int node) {
    return node ? getmax(tree[node].lftDep, tree[node].ritDep)+1 : 0;
  }

  int balance(int node) {
    return tree[node].lftDep - tree[node].ritDep;
  }

  void avl_update_depth(int node) {
    if (!node) return;
    tree[node].lftDep = depth(tree[node].lft);
    tree[node].ritDep = depth(tree[node].rit);
    tree[node].count = tree[tree[node].lft].count+tree[tree[node].rit].count+1;
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
      int newChd = tree[chd].lft;
      while (tree[newChd].rit) newChd = tree[newChd].rit;
      avl_swap_node(chd, newChd); chd = newChd;
    }
    while (tree[chd].rit) {
      int newChd = tree[chd].rit;
      while (tree[newChd].lft) newChd = tree[newChd].lft;
      avl_swap_node(chd, newChd); chd = newChd;
    }
    *tree[chd].ptr = 0;
    avl_balance(tree[chd].pa);
  }

  int avl_head() {
    int res = root;
    while (tree[res].lft) res = tree[res].lft;
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

  int avl_find_kmin(int k) {
    if (k<=0 || k>tree[root].count) return 0;
    int res = root;
    --k;
    while (k != tree[tree[res].lft].count) {
      if (k < tree[tree[res].lft].count) res = tree[res].lft;
      else {
        k -= tree[tree[res].lft].count+1;
        res = tree[res].rit;
      }
    }
    return res;
  }
};

#define N 110000
#define M 510000
int val[N];
avl_tree graph[N];
int root[N], len[N];
int arg[M][3];
int x[N], y[N], vld[N];
int n, m;

int cmp(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i]>val[j];
}

int get_root(int x) {
  if (root[x] == x) return x;
  else {
    root[x] = get_root(root[x]);
    return root[x];
  }
}

void graph_merge(int x, int y) {
  x = get_root(x); y = get_root(y);
  if (x == y) return;
  if (len[x]<len[y]) {
    int tmp = x;
    x = y;
    y = tmp;
  }
  for (int i = graph[y].avl_head(); i; i = graph[y].avl_next(i)) {
    graph[x].avl_insert(tree[i].id);
  }
  root[y] = x;
  len[x] += len[y]; 
}

void conduct() {
  avl_global_init();
  val[0] = 0;
  for (int i = 1; i<=n; ++i) scanf("%d", &val[i]);
  for (int i = 1; i<=m; ++i) scanf("%d%d", &x[i], &y[i]);
  for (int i = 1; i<=n; ++i) {
    graph[i].root = 0;
    graph[i].avl_insert(i);
    root[i] = i;
    len[i] = 1;
  }
  memset(vld, 0, sizeof(vld));
  int q = 0;
  while (1) {
    char cmd[10];
    scanf("%s", cmd);
    if (cmd[0] == 'E') break;
    else if (cmd[0] == 'D') {
      arg[q][0] = 0;
      scanf("%d", &arg[q][1]);
      vld[arg[q][1]] = 1;
    }
    else if (cmd[0] == 'C') {
      arg[q][0] = 1;
      scanf("%d%d", &arg[q][1], &arg[q][2]);
      int tmp = arg[q][2];
      arg[q][2] = val[arg[q][1]];
      val[arg[q][1]] = tmp;
    }
    else if (cmd[0] == 'Q') {
      arg[q][0] = 2;
      scanf("%d%d", &arg[q][1], &arg[q][2]);
    }
    else while (1);
    q++;
  }
  long long tot = 0L, num = 0L;
  for (int i = 1; i<=m; ++i)
    if (!vld[i]) graph_merge(x[i], y[i]);
  for (int i = q-1; ~i; --i) {
    if (arg[i][0] == 0) {
      int id = arg[i][1];
      graph_merge(x[id], y[id]);
    }
    else if (arg[i][0] == 1) {
      int id = arg[i][1], gId = get_root(id);
      graph[gId].avl_remove(id);
      val[id] = arg[i][2];
      graph[gId].avl_insert(id);
    }
    else {
      int id = arg[i][1], gId = get_root(id);
      int nodeId = graph[gId].avl_find_kmin(arg[i][2]);
      int index = tree[nodeId].id;
      tot += val[index];
      num++;
    }
  }
  printf("%.6f\n", (double)tot/num);
}

int main() {
  int time = 0;
  while (scanf("%d%d", &n, &m)!=EOF && (n || m)) {
    printf("Case %d: ", ++time);
    conduct();
  }
  return 0;
}
