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

int r, c;
int dp[71][71][71];

int pickup_TD(vector<vector<int>>& grid, int i, int ja, int jb){
	if(ja<0 || jb<0 || ja>=c || jb>=c)
		return -1e8;

	if(dp[i][ja][jb]!=-1)
		return dp[i][ja][jb];

	if(i==r-1){
		if(ja==jb)
			return grid[i][ja];
		else
			return grid[i][ja] + grid[i][jb];
	}

	int max_cherry = -1e8;
	for(int da=-1; da<=1; da++)
		for(int db=-1; db<=1; db++){
			int value = 0;
			if(ja==jb)	value += grid[i][ja];
			else	value += grid[i][ja] + grid[i][jb];

			value += pickup_TD(grid, i+1, ja+da, jb+db);
			max_cherry = max(max_cherry, value);
		}

	return dp[i][ja][jb] = max_cherry;

}

int pickup_BU(vector<vector<int>>& grid){
	dp[0][0][ja] = grid[0][0];
	dp[0][0][jb] = grid[0][c-1];

	
}


int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	int rr, cc;
	cin>>rr>>cc;
	r = rr;
	c = cc;
	vector <vi>	grid(r, vi(c));
	memset(dp, -1, sizeof(dp));

	for(int i=0; i<r; i++)
		for(int j=0; j<c; j++){
			int t;
			cin>>t;
			grid[i][j] = t;
		}

	int ans_TD = pickup_TD(grid, 0, 0, c-1);

	cout<<"Ans TD: "<<ans_TD<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 