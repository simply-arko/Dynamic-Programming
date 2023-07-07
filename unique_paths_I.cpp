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

int dp[101][101];

int path_finder_TD(int n, int m, int i=0, int j=0){
	if(i>n || j>m)
		return 0;
	else if(i==n-1 && j==m-1)
		return 1;

	if(dp[i][j]!=-1)
		return dp[i][j];

	int down = path_finder_TD(n, m, i+1, j);
	int right = path_finder_TD(n, m, i, j+1);

	return dp[i][j] = down + right;
}

int path_finder_BU(int n, int m){

	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(i==0 && j==0)
				dp[i][j] = 1;
			else{
				int from_up = (i>0)?dp[i-1][j]:0;
				int from_left = (j>0)?dp[i][j-1]:0;
				dp[i][j] = from_up + from_left;
			}

	return dp[n-1][m-1];

}

int path_finder_space_optimzed(int n, int m){
	vi dp(m+1, 0);

	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(i==0 && j==0)
				dp[j] = 1;
			else
				dp[j] += (j>0)?dp[j-1]:0;

	return dp[m-1];

}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	memset(dp, -1, sizeof(dp));
	int n, m;
	cin>>n>>m;

	int ans_TD = path_finder_TD(n,m);
	int ans_BU = path_finder_BU(n,m);
	int ans_OP = path_finder_space_optimzed(n,m);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans OP: "<<ans_OP<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 