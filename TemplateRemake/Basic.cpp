#if defined(__GNUC__) || defined(__clang__)
const int highBit1 = __builtin_clz(1);
#define NZ(x) ((x) ? (x) : 1)
#define HIGHBITN(x) (highBit1 - __builtin_clz(NZ(x)))
#define LOWBITN(x) __builtin_ctz(NZ(x))
#endif

#define LOWBIT(x) ((x)&(-x))
#define vr vw.get()
#define vp vw->get()

template<typename V>
inline V getmin(const V &a, const V &b) { return a<b?a:b; }
template<typename V>
inline V getmax(const V &a, const V &b) { return a>b?a:b; }

template<typename V>
inline void vclear(vector<V> &v, unsigned char val) { memset(&v[0], val, sizeof(V) * v.size()); }