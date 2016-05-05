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
treap tree[N];
int treapCount;
typedef int (*cmpFunc)(const int &i, const int &j);

inline long long weight(int node) { return node ? tree[node].wgt : -2L; }

class treap_algo {
public:
  int root;
  cmpFunc cmp;

  void rotate_op(int *nodes, int **ptrs) {
    for (int i = 0; i<3; ++i) {
      tree[nodes[i+1]].pa = nodes[i];
      tree[nodes[i+1]].ptr = ptrs[i];
      *ptrs[i] = nodes[i+1];
    }
  }

  void clock_rotate(int node) {
    int lftChd = tree[node].lft;
    int lftRitChd = tree[lftChd].rit;
    int nodes[4] = { tree[node].pa, lftChd, node, lftRitChd };
    int *ptrs[4] = { tree[node].ptr, &(tree[lftChd].rit), &(tree[node].lft), NULL };
    rotate_op(nodes, ptrs);
  }

  void aclock_rotate(int node) {
    int ritChd = tree[node].rit;
    int ritLftChd = tree[ritChd].lft;
    int nodes[4] = { tree[node].pa, ritChd, node, ritLftChd };
    int *ptrs[4] = { tree[node].ptr, &(tree[ritChd].lft), &(tree[node].rit), NULL };
    rotate_op(nodes, ptrs);
  }

  void balance(int *node) {
    while (*node) {
      long long lftWgt = weight(tree[*node].lft), ritWgt = weight(tree[*node].rit), wgt = weight(*node);
      if (wgt < lftWgt || wgt < ritWgt)
        if (lftWgt > ritWgt) clock_rotate(*node);
        else aclock_rotate(*node);
      else break;
    }
  }

  int *find(int id, int *pa) {
    *pa = 0;
    int *res = &root;
    for (int nxtPa = *res; *res; *pa = nxtPa, nxtPa = *res)
      if (cmp(id, tree[*res].id)) res = &(tree[*res].lft);
      else if (cmp(tree[*res].id, id)) res = &(tree[*res].rit);
      else break;
    return res;
  }

  void insert(int id) {
    int pa = 0;
    int *ptr = find(id, &pa);
    if (*ptr) return;
    memset(&tree[++treapCount], 0, sizeof(treap));
    tree[treapCount].id = id;
    tree[treapCount].pa = pa;
    tree[treapCount].ptr = ptr;
    *ptr = treapCount;
    tree[treapCount].wgt = (long long)rand() % N * N + rand() % N;
    balance(&(tree[treapCount].pa));
  }

  void remove(int id) {
    int node = *find(id, &node);
    if (!node) return;
    tree[node].wgt = -1L;
    balance(&node);
    *tree[node].ptr = 0;
  }

  int head() {
    for (int res = root; ; res = tree[res].lft)
      if (!tree[res].lft) return res;
  }
};

#define M 110000
int val[M];
int n, m;

int cmpMin(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i] < val[j];
}

int cmpMax(const int &i, const int &j) {
  if (val[i] == val[j]) return i<j;
  return val[i] > val[j];
}

void conduct() {
  treapCount = 0;
  memset(&tree[0], 0, sizeof(treap));
  treap_algo minTreap;
  minTreap.root = 0;
  minTreap.cmp = &cmpMin;
  treap_algo maxTreap;
  maxTreap.root = 0;
  maxTreap.cmp = &cmpMax;
  treap_algo *stg[2] = { &minTreap, &maxTreap };
  int cur = 0;
  scanf("%d%d", &m, &n);
  long long ans = 0L;
  for (int i = 0; i<n; ++i) {
    int cmd;
    scanf("%d", &cmd);
    if (!cmd) {
      scanf("%d", &val[i]);
      if (cur == val[i]) stg[0]->insert(i);
      else if (val[i] > cur) minTreap.insert(i);
      else maxTreap.insert(i);
    }
    else {
      int node1 = stg[0]->head(), node2 = stg[1]->head();
      if (!node1 && !node2) continue;
      int dis1 = node1 ? abs(val[tree[node1].id] - cur) : M, dis2 = node2 ? abs(val[tree[node2].id] - cur) : M;
      if (dis1 <= dis2) {
        ans += dis1;
        cur = val[tree[node1].id];
        stg[0]->remove(tree[node1].id);
      }
      else {
        ans += dis2;
        cur = val[tree[node2].id];
        stg[1]->remove(tree[node2].id);
        treap_algo * tmp = stg[0]; stg[0] = stg[1]; stg[1] = tmp;
      }
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
