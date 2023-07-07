#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

template <class T>
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}\n"; }

void file_i_o(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
}

int dp[100001];
int jump_bro_TD(vector<int>& height, int k, int j){
    if(j==0)
        return 0;
    
    // cout<<j<<", ";
    if(dp[j]!=-1)
    	return dp[j];

    int min_cost = INT_MAX;
    for(int i=1; i<=k; i++){
        int k_jump_cost = INT_MAX;
        if(j-i>=0)
            k_jump_cost = jump_bro_TD(height, k, j-i) + abs(height[j-i]-height[j]);
        min_cost = min(min_cost, k_jump_cost);
    }
    
    // cout<<min_cost<<endl;

    return dp[j] = min_cost;
}

int jump_bro_BU(vector<int>& height, int n, int k){
	dp[0] = 0;
        
    for(int i=1; i<n; i++){
        int min_cost = INT_MAX;
        for(int j=1; j<=k; j++)
            if(i-j>=0){
                int k_jump_cost = dp[i-j] + abs(height[i-j]-height[i]);
                min_cost = min(min_cost, k_jump_cost);
            }else
                break;
        dp[i] = min_cost;
    }
    
    // for(int i=0; i<n; i++)
    // 	cout<<dp[i]<<", ";
    return dp[n-1];
}

int minimizeCost(vector<int>& height, int n, int k) {
    memset(dp, -1, sizeof(dp));
    // return jump_bro_TD(height, k, n-1);
    return jump_bro_BU(height, n, k);
}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int n, k;
	cin>>n>>k;
	vi nums;
	for(int i=0; i<n; i++){
		int t;
		cin>>t;
		nums.push_back(t);
	}
	print_v(nums);

	int j = minimizeCost(nums, n, k);
	cout<<"\nMin Jumps: "<<j;


	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 