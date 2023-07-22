#include <bits/stdc++.h>
using namespace std;
#define ENDL '\n'
#define FOR(x, b) for(int x = 0; x <b; x++)
#define FORR(x, a, b) for(int x = a; x >= b; x--)
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
typedef vector<int> vi;

//Knapsack 2 - Problem from at coder dp educational contest 
//Classical knapsack with W up to 1e9 
//Change the the definition of dp

const ll INF = 1e18L + 5;

int main(){ _
  int n, w;
  cin >> n >> w;

  vi value(n);
  vi weight(n);
  int sum_values = 0; 

  FOR(i, n){
    cin >> weight[i] >> value[i];
    
    sum_values += value[i];
  }
  
  vector<ll> dp(sum_values + 1, INF); 
  //dp[i] - minimum total weight of items with value i
  dp[0] = 0; //if there no value there's no weight 
  FOR(i, n){ //iterate over all items n
    FORR(curr_value, sum_values - value[i], 0){//iterate from total values - value[i] to 0
      dp[curr_value + value[i]] = min(dp[curr_value + value[i]], dp[curr_value] + weight[i]);
    }
  }

  ll ans = 0;
  //search the answer on dp table
  FOR(i, sum_values + 1){
    if(dp[i] <= w){
      ans = max(ans, ll(i));
    }
  }   

  cout << ans << ENDL;
  return 0;
}