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

#define N 210000

// symmetric
int id[N], sym[N];
// trie nest map
int tri[N];
map<int, int> key[N];
// edge
vector<int> edg[N];
// temp
int que[N];
int n, u, v;

inline void nextNode(int &node, int id) {
  auto it = key[node].insert({id, tri[0]+1});
  if (it.second) tri[++tri[0]] = 0;
  node = it.first->second;
}

void dfs(int x, int pa) {
  vector<int> &to = edg[x];
  for (auto it = to.begin(); it != to.end(); ++it) if (*it != pa) dfs(*it, x);
  que[0] = 0;
  for (auto it = to.begin(); it != to.end(); ++it) if (*it != pa) que[++que[0]] = id[*it];
  sort(que+1, que+que[0]+1);
  int node = 1;
  for (int i = 1; i <= que[0]; ++i) nextNode(node, que[i]);
  if (!tri[node]) {
    int chance = 1;
    tri[node] = ++sym[0]; sym[sym[0]] = 1;
    for (int i = 1; i <= que[0]; i += 2) {
      if (i < que[0])
        if (que[i] != que[i+1])
          if (chance && sym[que[i]]) { chance = 0; i -= 1; }
          else { sym[sym[0]] = 0; break; }
        else;
      else if (chance) sym[sym[0]] = sym[que[i]]; else sym[sym[0]] = 0;
    }
  }
  id[x] = tri[node];
//  printf("debug: id[%d]=%d sym:%d\n", x, id[x], sym[id[x]]);
}

int main() {
  int kase; scanf("%d", &kase);
  while (kase--) {
    sym[0] = sym[1] = 1; tri[0] = tri[1] = 1;
    scanf("%d", &n);
    for (int i = 1; i<n; ++i) {
      scanf("%d%d", &u, &v);
      edg[u].push_back(v);
      edg[v].push_back(u);
    }
    dfs(1, 0);
    if (sym[id[1]]) printf("YES\n"); else printf("NO\n");
    // clean up 
    for (int i = 1; i<=n; ++i) {
      edg[i].clear();
      edg[i].shrink_to_fit();
    }
    for (int i = 1; i <= tri[0]; ++i) key[i].clear();
  }
  return 0;
}
