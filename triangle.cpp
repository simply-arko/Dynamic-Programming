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

void file_i_o(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
}

int dp[201][201];

int min_path_sum_TD(vector<vector<int>>& triangle, int i=0, int j=0){
	if(i>=triangle.size())
		return 0;

	if(dp[i][j]!=-1)
		return dp[i][j];

	int move_d = min_path_sum_TD(triangle, i+1, j);
	int move_dr = min_path_sum_TD(triangle, i+1, j+1);

	return dp[i][j] = min(move_d, move_dr) + triangle[i][j];
}

int min_path_sum_BU(vector<vector<int>>& triangle){
	int n = triangle.size();

	for(int i=0; i<n; i++)
		for(int j=0; j<i+1; j++)
			if(i==0 && j==0)
				dp[i][j] = triangle[i][j];
			else{
				int from_up = (i!=j)?dp[i-1][j]:INT_MAX;
				int from_up_left = (j!=0)?dp[i-1][j-1]:INT_MAX;
				dp[i][j] = min(from_up, from_up_left) + triangle[i][j];
			}

	int minE = INT_MAX;
	for(int i=0; i<n; i++)
		minE = min(minE, dp[n-1][i]);

	return minE;
}

int min_path_sum_space_optimised(vector<vector<int>>& triangle){
	int n = triangle.size();
	
	vi dp(n);
	dp[0] = triangle[0][0];

	for(int i=1; i<n; i++){
		vi curr(n);
		for(int j=0; j<i+1; j++)
			curr[j] = min((i!=j)?dp[j]:INT_MAX, (j!=0)?dp[j-1]:INT_MAX) + triangle[i][j];
		dp = curr;
	}

	int minE = INT_MAX;
	for(int i=0; i<n; i++)
		minE = min(minE, dp[i]);

	return minE;

}


int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int n;
	cin>>n;
	vector <vi> triangle(n);

	memset(dp, -1, sizeof(dp));
	for(int i=0; i<n; i++)
		for(int j=0; j<i+1; j++){
			int t;
			cin>>t;
			triangle[i].push_back(t);
		}

	int ans_TD = min_path_sum_TD(triangle);
	int ans_BU = min_path_sum_BU(triangle);
	int ans_OP = min_path_sum_space_optimised(triangle);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans OP: "<<ans_OP<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 