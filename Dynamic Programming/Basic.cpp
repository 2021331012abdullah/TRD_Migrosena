#1. SOS dp; O(N*2^N)
void SOS_DP(){
  for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
  for(int i = 0;i < N; ++i)
    for(int mask = 0; mask < (1<<N); ++mask){
      if(mask&(1<<i)) F[mask]+=F[mask^(1<<i)];}}
#2. LIS
int n,a[N],B[N],len[N];
int find_lis(){  int ans=0;
  for(int i=1; i<=n; i++){
    len[i]=lower_bound(B+1, B+ans+1, a[i])-B;//Incresing
  //len[i]=upper_bound(B+1, B+ans+1, a[i])-B;//Non-decresing
    ans=max(ans, len[i]);  B[len[i]]=a[i];  }  return ans; }
void print_lis(int ans){ vector<int> seq;
  for(int i=n; i>=1; i--){
    if(len[i]==ans){  seq.push_back(a[i]);  ans--; }  }
  int i=(int)seq.size();
  while(i--)  cout<<seq[i]<<" \n"[!i];  }
void init(){ clean(B,-1);  clean(len,0); }
#3. Digit DP
vector<int> A,B; ll dp[20][150][2][2];
//dp[curPos][sum][a is smaller than R][a is bigger than L]
ll call(int pos, int sum, int small, int big){
  if(pos==(int)B.size()) return (ll)sum;
  ll &res = dp[pos][sum][small][big];
  if(~res) return res;   res = 0;
  int start=A[pos], stop=B[pos];
  if(big) start=0; if(small) stop=9;
  for(int dgt=start; dgt<=stop; dgt++)
   res+=call(pos+1,sum+dgt,small|dgt<B[pos],big|dgt>A[pos]);
  return res; }
ll solve(ll a, ll b){
  A.clear();B.clear();
  while(b>0){  B.push_back(b%10);  b/=10; }
  while(a>0){  A.push_back(a%10);  a/=10; }
  while(A.size()<B.size())  A.push_back(0);
  reverse(A.begin(), A.end()); reverse(B.begin(), B.end());
  memset(dp, -1, sizeof(dp)); return call(0, 0, 0, 0);  }

#4. knapsack with high capacity; //O(N * sum profit)
ll dp[maxN*maxV+5]; vector<ll> wt,profit;
for(i=0; i<n; i++){ w=wt[i]; v=profit[i]; sum+=v;
  for(j=sum; j>=v; j--){
		dp[j] = min(dp[j], w+dp[j-v]);
		if(dp[j]<=cap) ans=max(ans, j); } }
#5. knapsack with bitset
bitset<MAX> possible; possible.reset(); possible[0] = 1;
for(int coin : coins){auto new_poss = possible << coin;
   possible |= new_poss; }