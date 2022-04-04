template<typename V>
inline void vclear(vector<V> &v) { memset(&v[0], 0, sizeof(V) * v.size()); }

// Dependency:
//   - function: vclear
template<typename V>
struct QueueList {
  vector<int> h, t, c, l, r, dexs;
  vector<V> v;
  int top;

  QueueList(int heads, int cap, V zero): top(0),
      h(heads, 0), t(heads, 0), c(heads, 0),
      l(++cap, 0), r(cap, 0), dexs(cap, 0), v(cap, zero) {}
  inline void clear() { top = 0; vclear(h); vclear(t); vclear(c); }
  inline int append(int dex, V val) {
    v[++top] = val; dexs[top] = dex; l[top] = t[dex]; r[top] = 0; r[t[dex]] = top; 
    if (!c[dex]++) h[dex] = top; t[dex] = top; return top;
  }
  inline void remove(int id) {
    *(l[id] ? &r[l[id]] : &h[dexs[id]]) = r[id];
    *(r[id] ? &l[r[id]] : &t[dexs[id]]) = l[id];
    --c[dexs[id]];
  }
};
