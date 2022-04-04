#define FOR_INC_0D(X, ED) for (int X = 0; X < ED; ++X) 
#define FOR_DEC_0D(X, ED) for (int X = ED-1; ~X; --X)

// id, lid, rid, ll, rr, hlf
typedef Tuple6<int, int, int, int, int, int> SegNode;
struct SegTree {
  int len;
  vector<SegNode> preIds, pstIds;
  SegTree(int l, int r) {
    int i, j;
    for (i = j = 1; i < r-l; i <<= 1, j++);
    pstIds.resize(j*4); preIds.resize(j*4);
    preIds[0] = SegNode(1, 2, 3, l, l+i, i>>1); len = i<<1;
  }
  void traverse(int l, int r, function<void(SegNode)> pre, function<void(SegNode)> pst, function<void(int, int, int)> ctl) {
    int pres = 1, psts = 0;
    FOR_INC_0D(i, pres) {
      SegNode v = preIds[i];
      int id = v.a, lid = v.b, rid = v.c, ll = v.d, rr = v.e, hlf = v.f, mid = ll+hlf;
      if (l<=ll && r>=rr) { if (ctl) ctl(id, ll, rr); continue; }
      if (pre) pre(v); if (pst) pstIds[psts++] = v;
      if (l<mid) preIds[pres++] = SegNode(lid, lid<<1, lid<<1|1, ll, mid, hlf>>1);
      if (r>mid) preIds[pres++] = SegNode(rid, rid<<1, rid<<1|1, mid, rr, hlf>>1);
    }
    FOR_DEC_0D(i, psts) pst(pstIds[i]);
  }
};
