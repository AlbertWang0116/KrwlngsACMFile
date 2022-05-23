#define LOWBIT(X) ((X)&(-X))

// Practice: https://codeforces.com/contest/1295/problem/E
// Only mid in recursion
//       * full binary tree - [0, 2^n)
//       * first mid is 2^(n-1).
//       * hlf is the lowest bit of mid; with mid, segment is [mid-hlf, mid+hlf). (hlf not need)
//       * every index appears exactly once in non-leaf node (id not need)
//       * every index appears exactly once in the leaf node. (id not need)
//       * depth: the reverse of the bit index of hlf.
//       * for hlf > 1: rmid = mid | (hlf >> 1), lmid = rmid ^ hlf
typedef function<void(int)> SegFunc;
struct SegTree {
  int len;
  vector<int> preMids, pstMids;

  SegTree(int effLen) {
    if (LOWBIT(effLen) == effLen) len = effLen;
    else for (len = effLen << 1; LOWBIT(len) != len; len ^= LOWBIT(len));
  }

  void traverse(int l, int r, SegFunc pre, SegFunc pst, SegFunc ctl) {
    preMids.clear(); pstMids.clear(); preMids.push_back(root());
    for (int i = 0, mid = preMids[0]; i < preMids.size(); mid = preMids[++i]) {
      if (mid&len || (l<=ll(mid) && r>=rr(mid))) { ctl(mid); continue; }
      pre(mid); pstMids.push_back(mid);
      if (l<mid) preMids.push_back(lmid(mid));
      if (r>mid) preMids.push_back(rmid(mid));
    }
    for (auto it = pstMids.rbegin(); it != pstMids.rend(); ++it) pst(*it);
  }

  // non-leaf(!) helpers.
  inline int ll(int mid) { return mid - LOWBIT(mid); }
  inline int rr(int mid) { return mid + LOWBIT(mid); }
  inline int span(int mid) { return LOWBIT(mid) << 1; }
  inline int lmid(int mid) { return mid & 1 ? len + mid - 1 : mid - (LOWBIT(mid) >> 1); }
  inline int rmid(int mid) { return mid & 1 ? len + mid : mid | (LOWBIT(mid) >> 1); }
  inline int root() { return len >> 1; }
};
