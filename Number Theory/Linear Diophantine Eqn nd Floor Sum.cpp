void shift_solution(int &x, int &y, int a, int b, int cnt) {
  x += cnt * b; y -= cnt * a;
}
void findPosSol(int a, int b, int &x, int &y, int g) {
  a /= g; b /= g; int mov;
  if (x < 0) {mov = (0 - x + b - 1) / b; shift_solution(x, y, a, b, mov);}
  if (y < 0) {
    mov = (-y) / a; if ((-y) % a) mov++;
    shift_solution(x, y, a, b, -mov);
  }
}
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
  g = egcd(abs(a), abs(b), x0, y0); if (c % g) return 0;
  x0 *= c / g; y0 *= c / g; if (a < 0) x0 *= -1; if (b < 0) y0 *= -1;
  /*findPosSol(a,b,x0,y0,g);*/ return 1;
}
int find_all_solutions(int a, int b, int c, int minX, int maxX, int minY, int maxY) {
  if (!a && !b) {
    if (c) return 0LL;
    return (maxX - minX + 1LL) * (maxY - minY + 1LL);
  }
  if (!a) {
    if (c % b) return 0LL; int y = c / b;
    if (minY <= y && y <= maxY) return (maxX - minX + 1LL);
    return 0LL;
  }
  if (!b) {
    if (c % a) return 0LL; int x = c / a;
    if (minX <= x && x <= maxX) return (maxY - minY + 1LL);
    return 0LL;
  }
  int x, y, g;
  if (!find_any_solution(a, b, c, x, y, g)) return 0;
  a /= g; b /= g;
  int sign_a = a > 0 ? +1 : -1;
  int sign_b = b > 0 ? +1 : -1;
  shift_solution(x, y, a, b, (minX - x) / b);
  if (x < minX) shift_solution(x, y, a, b, sign_b);
  if (x > maxX)  return 0;
  int lx1 = x; shift_solution(x, y, a, b, (maxX - x) / b);
  if (x > maxX) shift_solution(x, y, a, b, -sign_b);
  int rx1 = x; shift_solution(x, y, a, b, -(minY - y) / a);
  if (y < minY) shift_solution(x, y, a, b, -sign_a);
  if (y > maxY)  return 0; int lx2 = x;
  shift_solution(x, y, a, b, -(maxY - y) / a);
  int rx2 = x; if (lx2 > rx2) swap(lx2, rx2);
  int lx = max(lx1, lx2), rx = min(rx1, rx2);
  if (lx > rx) return 0; return (rx - lx) / abs(b) + 1;
}
/** LD Less or Equal: ax+by <= c **/
ll sumsq(ll n) { return n / 2 * ((n - 1) | 1);}
//\sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
ll floor_sum(ll a, ll d, ll m, ll n) {
  if (d < 0) { //if d<0, reversing the series
    a = a + (n - 1) * d; d = -d;
  }
  ll res = d / m * sumsq(n) + a / m * n;
  d %= m; a %= m; if (!d) return res;
  ll to = (n * d + a) / m;
  return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// number of integer solutions to ax + by <= c s.t. x, y >= 0
ll lattice_cnt(ll a, ll b, ll c) { // log(a)
  if (a == 0 or b == 0) { // infinite solutions
    return -1;
  }
  ll terms = 1 + c / b;
  return terms + floor_sum(c, -b, a , terms);
}