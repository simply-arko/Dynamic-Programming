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
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

int dp[101][101];

int min_falling_path_TD(vector<vector<int>>& matrix, int i, int j){
	if(j==matrix.size() || j==-1)
		return INT_MAX;
	if(i==matrix.size()-1)
		return matrix[i][j];

	if(dp[i][j]!=-1)
		return dp[i][j];

	int fallD = min_falling_path_TD(matrix, i+1, j);
	int fallDR = min_falling_path_TD(matrix, i+1, j+1);
	int fallDL = min_falling_path_TD(matrix, i+1, j-1);

	return dp[i][j] = min({fallD, fallDR, fallDL}) + matrix[i][j];
}

int min_falling_path_BU(vector<vector<int>>& matrix){
	int n = matrix.size();
	int ans = INT_MAX;

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++){
			if(i==0)
				dp[i][j] = matrix[i][j];
			else{
				int fromUp = dp[i-1][j];
				int fromUpLeft = (j-1>=0)?dp[i-1][j-1]:INT_MAX;
				int fromUpRight = (j+1<n)?dp[i-1][j+1]:INT_MAX;
				dp[i][j] = min({fromUp, fromUpRight, fromUpLeft}) + matrix[i][j];
			}
			if(i==n-1)
				ans = min(ans, dp[i][j]);
		}

	return ans;
}

int min_falling_path_space_optimized(vector<vector<int>>& matrix){
	int n = matrix.size();
	int ans = INT_MAX;
	vi dp(n);

	for(int i=0; i<n; i++){
		vi curr(n);
		for(int j=0; j<n; j++){
			if(i==0)
				curr[j] = matrix[i][j];
			else{
				int fromUp = dp[j];
				int fromUpLeft = (j-1>=0)?dp[j-1]:INT_MAX;
				int fromUpRight = (j+1<n)?dp[j+1]:INT_MAX;
				curr[j] = min({fromUp, fromUpRight, fromUpLeft}) + matrix[i][j];
			}
			if(i==n-1)
				ans = min(ans, curr[j]);
		}
		dp = curr;
	}

	return ans;
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

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int n;
	cin>>n;
	vector <vi> matrix(n, vi(n));
	memset(dp, -1, sizeof(dp));

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++){
			int t;
			cin>>t;
			matrix[i][j] = t;
		}

	int ans_TD = INT_MAX;

	for(int j=0; j<n; j++){
		int curr = min_falling_path_TD(matrix, 0, j);
		ans_TD = min(ans_TD, curr);
	}

	int ans_BU = min_falling_path_BU(matrix);
	int ans_OP = min_falling_path_space_optimized(matrix);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans OP: "<<ans_OP<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 