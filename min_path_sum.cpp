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

int n,m;
int dp[201][201];

int min_path_finder_TD(vector<vector<int>>& grid, int i=0, int j=0){
	if(i>=n || j>=m)
		return INT_MAX;
	else if(i==n-1 && j==m-1)
		return grid[i][j];

	if(dp[i][j]!=-1)
		return dp[i][j];

	int down = min_path_finder_TD(grid, i+1, j);
	int right = min_path_finder_TD(grid, i, j+1);

	return dp[i][j] = min(down,right) + grid[i][j];
}

int min_path_finder_BU(vector<vector<int>>& grid){
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
		if(i==0 && j==0)
			dp[i][j] = grid[i][j];
		else{
			int from_up = (i-1>=0)?dp[i-1][j]:INT_MAX;
			int from_left = (j-1>=0)?dp[i][j-1]:INT_MAX;
			dp[i][j] = min(from_up, from_left) + grid[i][j];
		}

	return dp[n-1][m-1];
}

int min_path_finder_space_optimised(vector<vector<int>>& grid){
	vi dp(m, INT_MAX);

	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(i==0 && j==0)
				dp[j] = grid[i][j];
			else
				dp[j] = min((j-1>=0)?dp[j-1]:INT_MAX, dp[j]) + grid[i][j];

	return dp[m-1];
}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int x, y;
	cin>>x>>y;
	n = x;
	m = y;

	memset(dp, -1, sizeof(dp));
	vector <vi> grid(n, vi(m, 0));

	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++){
			int t;
			cin>>t;
			grid[i][j] = t;
		}

	int ans_TD = min_path_finder_TD(grid);
	int ans_BU = min_path_finder_BU(grid);
	int ans_OP = min_path_finder_space_optimised(grid);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans OP: "<<ans_OP<<endl;


	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 