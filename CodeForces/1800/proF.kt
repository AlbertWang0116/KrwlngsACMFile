import java.io.PrintWriter
import java.util.StringTokenizer

@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out

@JvmField val _reader = INPUT.bufferedReader()
fun readLnOpt(): String? = _reader.readLine()
fun readLn() = readLnOpt()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(readLn(), " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = LongArray(n) { read().toLong() }

@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }

inline val Char.bool: Boolean get() = this.code != 0
inline val Int.bool: Boolean get() = this != 0
inline val Int.pos: Boolean get() = this > 0
inline val Int.neg: Boolean get() = this < 0

inline fun <R> IntArray.foldSub(
    initial: R,
    prog: IntProgression,
    combine: (R, Int) -> R
): R = prog.fold(initial) { value, element -> combine(value, this.get(element)) }
inline var IntArray.l: Int get() = this[0]; set(value) { this[0] = value }
inline var IntArray.r: Int get() = this[lastIndex]; set(value) { this[lastIndex] = value }
inline var IntArray.x: Int get() = this[size - 2]; set(value) { this[size - 2] = value }
inline var IntArray.y: Int get() = this[size - 3]; set(value) { this[size - 3] = value }
inline var IntArray.z: Int get() = this[size - 3]; set(value) { this[size - 3] = value }

class Breaker {}
class Looper(x: Int) {
  var i = x; var j = x; var k = x; var l = x;

  inline fun <T> loop(
      initial: Looper.() -> Unit,
      condition: Looper.() -> Boolean,
      update: Looper.() -> Unit,
      task: Looper.() -> T) {
    initial()
    while (condition()) {
      if (task() is Breaker) break;
      update()
    }
  }
  inline fun <T> loopi(iter: Iterable<Int>, task: Looper.() -> T) {
    for (x in iter) { i = x; if (task() is Breaker) break; }
  }
  inline fun <T> loopj(iter: Iterable<Int>, task: Looper.() -> T) {
    for (x in iter) { j = x; if (task() is Breaker) break; }
  }
  inline fun <T> loopk(iter: Iterable<Int>, task: Looper.() -> T) {
    for (x in iter) { k = x; if (task() is Breaker) break; }
  }
  inline fun <T> loopl(iter: Iterable<Int>, task: Looper.() -> T) {
    for (x in iter) { l = x; if (task() is Breaker) break; }
  }
}
val breaker = Breaker()
val looper  = Looper(0)

class tp1 <V1> (_x: V1) { var x = _x; }
class tp2 <V1, V2> (_x: V1, _y: V2) { var x = _x; var y = _y; }
class tp3 <V1, V2, V3> (_x: V1, _y: V2, _z: V3) { var x = _x; var y = _y; var z = _z; }

typealias int = Int
typealias char = Char
typealias long = Long
typealias ints = IntArray
typealias chars = CharArray
typealias longs = LongArray

val N = 210000
val dic = IntArray(1 shl 26)
val odd = IntArray(N)
val eve = IntArray(N)
val ext = IntArray(N)
val cnt = IntArray(N)

fun work() {
  looper.apply {
    odd.l = 0; eve.l = 0;
    val n = readInt()
    loopi(0..n-1) {
      ext[i] = 0; cnt[i] = 0;
      val str = read()
      for (c in str) {
        val bit = 1 shl (c - 'a')
        ext[i] = ext[i] or bit
        cnt[i] = cnt[i] xor bit
      }
      if (str.length and 1 == 0) eve[++eve.l] = i else odd[++odd.l] = i;
    }
    var ans = 0L
    loopk(0..25) {
      val bit = 1 shl k
      val msk = ((1 shl 26) - 1) xor bit
      loopi(1..odd.l) {
        if (ext[odd[i]] and bit == 0) dic[cnt[odd[i]]]++ else Unit;
      }
      loopi(1..eve.l) {
        if (ext[eve[i]] and bit == 0) ans += dic[msk xor cnt[eve[i]]] else Unit;
      }
      loopi(1..odd.l) {
        if (ext[odd[i]] and bit == 0) dic[cnt[odd[i]]]-- else Unit;
      }
    }
    println("$ans")
  }
}

fun main() {
  work()
}

