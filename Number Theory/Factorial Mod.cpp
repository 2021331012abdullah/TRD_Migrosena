//n! % p =?,O(plogp n).
int factmod(int n, int p) {
  int res = 1;
  while (n > 1) {
    res = (res * ((n / p) % 2 ?  p - 1 : 1)) % p;
    for (int i = 2; i <= n % p; ++i)
      res = (res * i) % p;
    n /= p;
  }  return res % p;
}
