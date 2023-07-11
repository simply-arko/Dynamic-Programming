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
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

template <class T>
void print_vv(vector<vector<T>> &v){ 
	for(auto x : v){
		for(auto y : x)
			cout << y << " "; 
		cout<<endl;
	}
}

void file_i_o(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
}

int dp[101][10001];

bool find_subset_TD(vector<int>arr, int sum, int i=0){
	// cout<<i<<", "<<sum<<endl;
	if(sum==0)
		return true;
	else if(i==arr.size() || sum<0)
		return false;

	if(dp[i][sum]!=-1)
		return dp[i][sum];


	return dp[i][sum] = find_subset_TD(arr, sum-arr[i], i+1) || find_subset_TD(arr, sum, i+1);
}

bool find_subset_BU(vector<int>arr, int sum){
	vector <vb> dp(arr.size(), vb(sum+1, false));

	for(int i=0; i<arr.size(); i++)
		dp[i][0] = true;
	
	if(arr[0]<=sum)
    	dp[0][arr[0]] = true;

	for(int i=1; i<arr.size(); i++)
		for(int j=1; j<=sum; j++){
			bool not_pick = dp[i-1][j];
			bool pick = (j>=arr[i])?dp[i-1][j-arr[i]]:false;
			dp[i][j] = pick || not_pick;
		}

	return dp[arr.size()-1][sum];

}

bool find_subset_space_optimised(vector<int>arr, int sum){
	vb dp(sum+1, false);
	dp[0] = true;

	if(arr[0]<=sum)
    	dp[arr[0]] = true;

	for(int i=1; i<arr.size(); i++){
		vb curr(sum+1);
		curr[0] = true;
		for(int j=1; j<=sum; j++){
			bool pick = dp[j];
			bool not_pick = (j>=arr[i])?dp[j-arr[i]]:false;
			curr[j] = pick || not_pick;
		}
		dp = curr;
	}

	return dp[sum];
}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int n, sum;
	cin>>n;
	vi arr(n);
	memset(dp, -1, sizeof(dp));

	for(int i=0; i<n; i++){
		int t;
		cin>>t;
		arr[i] = t;
	}
	cin>>sum;

	int ans_TD = find_subset_TD(arr, sum);
	int ans_BU = find_subset_BU(arr, sum);
	int ans_OP = find_subset_space_optimised(arr, sum);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans OP: "<<ans_OP<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 