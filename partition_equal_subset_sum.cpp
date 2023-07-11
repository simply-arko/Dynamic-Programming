#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vb vector<bool>
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

int dp[201][10001];

bool subset_sum_TD(vector<int>& nums, int sum, int i=0){
	if(sum==0)
		return true;
	if(i==nums.size() || sum<0)
		return false;

	if(dp[i][sum]!=-1)
		return dp[i][sum];

	return dp[i][sum] = subset_sum_TD(nums, sum-nums[i], i+1) || subset_sum_TD(nums, sum, i+1);

}

bool subset_sum_BU(vector<int>& nums, int sum){
    vector <vector<bool>> dp(nums.size(), vector<bool>(sum+1, false));
    for(int i=0; i<nums.size(); i++)
        dp[i][0] = true;
    if(nums[0]<=sum)
        dp[0][nums[0]] = true;
    
    for(int i=1; i<nums.size(); i++)
        for(int tar=1; tar<=sum; tar++){
            bool not_take = dp[i-1][tar];
            bool take = (tar>=nums[i])?dp[i-1][tar-nums[i]]:false;
            dp[i][tar] = not_take || take;
        }
    
    return dp[nums.size()-1][sum];
}

bool subset_sum_space_optimised(vector<int>& nums, int sum){
	vb dp(sum+1, false);
	dp[0] = true;
	if(nums[0]<=sum)
		dp[nums[0]] = true;

	for(int i=1; i<nums.size(); i++){
		vb curr(sum+1);
		curr[0] = true;
        for(int tar=1; tar<=sum; tar++){
        	bool not_take = dp[tar];
            bool take = (tar>=nums[i])?dp[tar-nums[i]]:false;
            curr[tar] = not_take || take;
        }
        dp = curr;
        // print_v(dp);
    }

    return dp[sum];
}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int n;
	cin>>n;
	vi nums(n);
	memset(dp, -1, sizeof(dp));
	for(int i=0; i<n; i++){
		int t;
		cin>>t;
		nums[i] = t;
	}

	int sum = 0;
	for_each(nums.begin(), nums.end(), [&](auto it){
		sum += it;
	});

	bool ans_TD = (sum&1)?false:subset_sum_TD(nums, sum/2);
	bool ans_BU = (sum&1)?false:subset_sum_BU(nums, sum/2);
	bool ans_OP = (sum&1)?false:subset_sum_space_optimised(nums, sum/2);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans OP: "<<ans_OP<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 