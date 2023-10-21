/**
 * Resolve a solution of a * x + b * y = gcd(a, b).
 *
 * It guarantees |x| <= b, |y| <= a.
 *
 * If gcd(a, b) = 1, and a big number K is divisible by a. Then (K / a) % b equals (K % b) * ((x+b)%b) % b.
 *
 * If a number N is divisible by gcd(a, b), and denote r the smallest positive integer that a * r % b = N. r is ((x+b)%b) * (N/gcd(a,b)) % b.
 *
 * @return the result of gcd(a, b).
 */
int ExtGcd(int a, int b, int &x, int &y) {
  if (!b) { x = 1; y = 0; return a; }
  int x2, y2; int res = ExtGcd(b, a % b, x2, y2);
  x = y2; y = x2 - (a / b) * y2; return res;
}
