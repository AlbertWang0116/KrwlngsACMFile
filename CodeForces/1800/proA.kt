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

class Looper(x: Int) {
  var i = x; var j = x; var k = x; var l = x;

  inline fun <T> loop(
      initial: Looper.() -> Unit,
      condition: Looper.() -> Boolean,
      update: Looper.() -> Unit,
      task: Looper.() -> T) {
    initial()
    while (condition()) {
      if (task() !is Unit) break;
      update()
    }
  }
  inline fun loopi(iter: Iterable<Int>, task: Looper.() -> Any) {
    for (x in iter) { i = x; if (task() !is Unit) break; }
  }
  inline fun loopj(iter: Iterable<Int>, task: Looper.() -> Any) {
    for (x in iter) { j = x; if (task() !is Unit) break; }
  }
  inline fun loopk(iter: Iterable<Int>, task: Looper.() -> Any) {
    for (x in iter) { k = x; if (task() !is Unit) break; }
  }
  inline fun loopl(iter: Iterable<Int>, task: Looper.() -> Any) {
    for (x in iter) { l = x; if (task() !is Unit) break; }
  }
}
val na = Unit
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

val low = "meow".toCharArray()
val upp = "MEOW".toCharArray()

fun work() {
  looper.apply {
    val n = readInt()
    val str = read()
    loop ({ i = 0; k = 0; }, {k < 4}, { ++k }) {
      loop ({ j = i }, { j < n }, {++j}) lj@ {
        if (str[j] != low[k] && str[j] != upp[k]) 0 else Unit
      }
      if (i == j) {
        println("NO")
        return
      }
      i = j
    }
    if (i == n && k == 4) println("YES") else println("NO")
  }
}

fun main() {
  val _t = readInt()
  for (_tt in 1.._t) {
    work()
  }
}
