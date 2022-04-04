template<typename V>
inline void lshift(V &a, V &b, V value) { a = b; b = value; }

template<typename V>
inline int isequal(V a, V b) { return !(a<b) && !(b<a); }

template<typename V>
inline int cmpassign(V &a, V &b) { int res = a < b ? -1 : b < a ? 1 : 0; a = b; return res; }

template<typename Q, typename W>
struct Tuple2 {
  Q q; W w;
  Tuple2(Q q, W w): q(q), w(w) {}
};

// Practice: https://codeforces.com/contest/1561/problem/F
// Dependency:
//   - function: lshift
//   - function: isequal
//   - function: cmpassign
//   - type: Tuple2
typedef Tuple2<int, int> TreapRes;
template<typename K>
struct Treap {
  vector<int> pa, lft, rit, wt, cnts, rpts;
  vector<K> keys, incs;
  int root, top;
  K zero;

  Treap(int cap, K zero) : root(0), top(0), zero(zero),
      pa(++cap, 0), lft(cap, 0), rit(cap, 0), wt(cap, 0),
      cnts(cap, 0), rpts(cap, 0), keys(cap, zero), incs(cap, zero) {}

  inline int f5(int id) {
    if (!id || !incs[id]) return id;
    keys[id] += incs[id]; incs[lft[id]] += incs[id]; incs[rit[id]] += incs[id];
    incs[id] = zero; return id;
  }
  inline int maxcid(int id) { return wt[lft[id]] > wt[rit[id]] ? lft[id] : rit[id]; }
  inline void addcnts(int id, int val) { for (int pid = pa[id]; pid; pid = pa[pid]) cnts[pid] += val; }
  inline void clear() { root = top = 0; }
  inline int search(K key) { return getkey(key).q; }

  int index(int k) {
    for (int id = root, l = k; f5(id); id = !cmpassign(k, l) ? lft[id] : rit[id])
      if (cmpassign(l, cnts[lft[id]]) < 0) l = k; else if (k - l < rpts[id]) return id; else l = k - l - rpts[id];
    exit(-1);
  }

  int insert(K key) {
    TreapRes res = getkey(key);
    if (res.q) { ++rpts[res.q]; ++cnts[res.q]; addcnts(res.q, 1); return res.q; }
    *(res.w ? (key < keys[res.w] ? &lft[res.w] : &rit[res.w]) : &root) = ++top;
    pa[top] = res.w; lft[top] = rit[top] = 0; keys[top] = key;
    wt[top] = rand() % 1000000 + 1; cnts[top] = rpts[top] = 1;
    addcnts(top, 1); for (int pid = pa[top]; pid && wt[pid] < wt[top]; pid = pa[top]) rotate(top);
    return top;
  }

  void remove(K key) {
    int id = getkey(key).q; if (!id) return;
    --cnts[id]; addcnts(id, -1); if (--rpts[id]) return;
    for (int cid = maxcid(id); f5(cid); cid = maxcid(id)) rotate(cid);
    *(pa[id] ? (keys[id] < keys[pa[id]] ? &lft[pa[id]] : &rit[pa[id]]) : &root) = 0;
  }

  int next(int id) {
    if (rit[id]) for (int cid = rit[id]; f5(cid); cid = lft[cid]) if (!lft[cid]) return cid;
    for (int pid = pa[id]; pid; pid = pa[pid]) if (keys[id] < keys[pid]) return pid;
    return 0;
  }

  int prev(int id) {
    if (lft[id]) for (int cid = lft[id]; f5(cid); cid = rit[cid]) if (!rit[cid]) return cid;
    for (int pid = pa[id]; pid; pid = pa[pid]) if (keys[pid] < keys[id]) return pid;
    return 0;
  }

  void addsuf(int id, K val) {
    for (int pid = pa[id]; pid; pid = pa[pid])
      if (keys[id] < keys[pid]) { keys[pid] += val; incs[rit[pid]] += val; }
    keys[id] += val; incs[rit[id]] += val;
  }
  
  // c++11
  void traverse(int id, function<void(int)> func) {
    if (!f5(id)) return;
    traverse(lft[id], func); func(id); traverse(rit[id], func);
  }

  TreapRes getkey(K key) {
    int id = root, pa = 0;
    while (f5(id) && !isequal(key, keys[id])) lshift(pa, id, key < keys[id] ? lft[id] : rit[id]);
    return TreapRes(id, pa);
  }

  void rotate(int id) {
    int pid = pa[id];
    int *pptr = pa[pid] ? (keys[pid] < keys[pa[pid]] ? &lft[pa[pid]] : &rit[pa[pid]]) : &root;
    int *ptr = keys[id] < keys[pid] ? &lft[pid] : &rit[pid];
    int *cptr = keys[id] < keys[pid] ? &rit[id] : &lft[id];
    *pptr = id; *ptr = *cptr; *cptr = pid;
    pa[id] = pa[pid]; pa[pid] = id; pa[*ptr] = pid;
    cnts[id] = cnts[pid]; cnts[pid] = cnts[lft[pid]] + cnts[rit[pid]] + rpts[pid];
  }
};
