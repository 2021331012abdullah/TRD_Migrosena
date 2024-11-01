struct Congruence {
    long long a, m;
};

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}


#define __int128 lll
/*A CRT solver which works even when moduli are not pairwise
coprime Call CRT(k) to get {x, N} pair, where x is the 
unique solution modulo N. O(n*Log L) L=LCM(p1,p2,....) 
Assumptions: 1. LCM of all mods will fit into long long.*/
pll CRT(ll n){
  ll r1,r2,p1,p2,x,y,ans,g,mod;  r1=r[0],p1=p[0];
  for(int i=1; i<n; i++){
    r2=r[i],p2=p[i];  g=__gcd(p1,p2);
    if(r1%g != r2%g) return {-1, -1}; //no solution
    EGCD(p1/g, p2/g, x, y);  mod=p1/g*p2;
ans=((lll)r1*(p2/g)%mod*y%mod+(lll)r2*(p1/g)%mod*x%mod)%mod;
    r1=ans;  if(r1<0) r1+=mod;  p1=mod;
  }  return {r1,mod};  }
