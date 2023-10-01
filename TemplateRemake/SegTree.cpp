// Practice: https://codeforces.com/contest/1295/problem/E
// [Option 1 - Not Picked] Only mid in recursion
//     * full binary tree - [0, 2^n)
//     * first mid is 2^(n-1).
//     * hlf is the lowest bit of mid; with mid, segment is [mid-hlf, mid+hlf). (hlf not need)
//     * every index appears exactly once in the branch node (id not need)
//     * every index appears exactly once in the leaf node. (id not need)
//     * depth: the reverse of the bit index of hlf.
//     * for branch node: rmid = mid | (hlf >> 1), lmid = rmid ^ hlf
//     * sibling is (mid ^ (lowbit(mid) << 1)).
//     * For range [0, r) where r != 2^n:
//         * the mid is in range [0, r) for all traversed nodes.
//         * STNode::mid is ID, the value range is (-r, r).
//         * Use vector with negative index to save data for STNode.
//
// [Option 2 - Picked] id is ordered in BFS order of the full binary tree.
//     * root is 1
//     * The i-th layer (0-based) has 2^i nodes, the first node's id is 2^i and the last node's id is 2^(i+1) - 1.
//         * The high-bit of the id in the i-th layer is i.
//     * Since it's a full binary tree, the segment length of the node at the i-th layer is 2^(k-i).
//     * The left boundary of a node in i-th layer is (id - 2^i) * 2^(k-i).
//     * Everything can be calculated through bit operation.
//     * For hbn = 18, rmax <= 262144 (2^18), idmax <= 524288 (2^19).
//
// [Decision Consideration] Constant optimization from Segment Tree:
// 1. The `id` of two siblings must be adjacent, otherwise it will be 33% slower, due to the higher missing rate of CPU cache.
// 2. Properties of a segment tree node can be fetched from several bit operations, which is faster than accessing a memory
//    block. So pre-constructed data structure is slower than calculation.
// 3. For pre-constructed segment tree, saving nodes in an array is faster than dynamic allocation. Dynamic allocation from
//    leaf nodes in reverse order (larger index to lower index) is faster than the other order. Due to 1.
// 4. Remaining overhead: function object +5%, using reference in function object +10% (reference = pointer) - Removing the
//    function object will gain 15% performance boost.
struct STNode {
  int hb, hbn, l, r, mid, id, lid, rid;
  STNode(int hbn) : hbn(hbn), hb(1<<hbn) {}
  inline STNode &fromId(int id) {
    l = id << hbn - HIGHBITN(id) ^ hb; r = l + (1 << hbn - HIGHBITN(id)); mid = (l + r) >> 1;
    this->id = id; lid = id << 1; rid = lid | 1; return *this;
  }
};

typedef function<void(const STNode &)> SegFunc;
struct SegTree {
  STNode x;
  vector<int> p, q;
  SegTree(int rmax): x(HIGHBITN(abs(rmax) - 1) + 1), p(100), q(50) {}
  void traverse(int l, int r, SegFunc pre, SegFunc pst, SegFunc ctl) {
    p[0] = p[1] = 1; q[0] = 0;
    for (int i = 1; i <= p[0]; ++i)
      if (l <= x.fromId(p[i]).l && r >= x.r) ctl(x); else {
        pre(x); q[++q[0]] = x.id;
        if (l < x.mid) p[++p[0]] = x.lid;
        if (r > x.mid) p[++p[0]] = x.rid;
      }
    for (int i = q[0]; i; --i) pst(x.fromId(q[i]));
  }
};

// More practicle template-based approach
namespace SegTree {
  struct ExampleSegNode {
    int l, r, id, mid;
    inline void pre() {}
    inline void pst() {}
    inline void cst() {}
  }

  template<typename SegNode>
  struct SegTree {
    SegNode &u;
    int &l, &r, &mid, &id, x, y;
    SegTree(int L, int R, SegNode &u): u(u), l(u.l), r(u.r), mid(u.mid), id(u.id) {
      l = L; r = R; mid = (L + R) >> 1; id = 1;
    }
    inline void traverse(int x, int y) { this->x = x; this->y = y; traverseImpl(); }
    void traverseImpl() {
      if (x <= l && y >= r) { u.ctl(); return; }
      u.pre();
      if (x < mid) {
        int tmp = r; r = mid; mid = (l+r)>>1; id <<= 1;
        traverseImpl(); r = tmp; mid = (l+r)>>1; id >>= 1;
      }
      if (y > mid) {
        int tmp = l; l = mid; mid = (l+r)>>1; id = id<<1|1;
        traverseImpl(); l = tmp; mid = (l+r)>>1; id >>= 1;
      }
      u.pst();
    }
  }
}
