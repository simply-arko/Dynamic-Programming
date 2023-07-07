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

int dp[100001][3];
int max_points_TD(vector<vector<int>>& points, int n, int day=0, int prev_act=-1){
    if(day==n)
        return 0;
    
    if(prev_act!=-1 && dp[day][prev_act]!=-1)
        return dp[day][prev_act];
    
    int max_act = 0;
    for(int i=0; i<3; i++)
        if(i!=prev_act){
            int curr_act = max_points_TD(points, n, day+1, i) + points[day][i];
            max_act = max(max_act, curr_act);
        }
    
    if(prev_act==-1)
        return max_act;
        
    return dp[day][prev_act] = max_act;
}

int max_points_BU(vector<vector<int>>& points, int n){
	dp[0][0] = points[0][0];
    dp[0][1] = points[0][1];
    dp[0][2] = points[0][2];
    
    for(int day=1; day<n; day++){
        for(int act=0; act<3; act++){
            int curr_act = max (dp[day-1][(act+1)%3] + points[day][act], 
                                dp[day-1][(act+2)%3] + points[day][act]);
            dp[day][act] = curr_act;
        }
    }
    // for(int i=0; i<n; i++){
    // 	for(int j=0; j<3; j++)
    // 		cout<<dp[i][j]<<", ";
    // 	cout<<endl;
    // }

    return max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});

}

int max_points_Space_optimized(vector<vector<int>>& points, int n){
	int optimal[3] = {points[0][0], points[0][1], points[0][2]};

	// cout<<optimal[0]<<", "<<optimal[1]<<", "<<optimal[2]<<endl;

	for(int day=1; day<n; day++){
		int temp[3] = {optimal[0], optimal[1], optimal[2]};
        for(int act=0; act<3; act++){
            int curr_act = max (temp[(act+1)%3] + points[day][act], 
                                temp[(act+2)%3] + points[day][act]);
            optimal[act] = curr_act;
        }
        // cout<<optimal[0]<<", "<<optimal[1]<<", "<<optimal[2]<<endl;
    }

    return max({optimal[0], optimal[1], optimal[2]});

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
	vector<vector<int>> points(n, vi(3,0));
	int k=0;
	while(k<n){
		for(int i=0; i<3; i++){
			int t;
			cin>>t;
			points[k][i] = t;
		}
		++k;
	}
	memset(dp, -1, sizeof(dp));

	int ans_TD = max_points_TD(points, points.size());
	int ans_BU = max_points_BU(points, points.size());
	int ans_opt = max_points_Space_optimized(points, points.size());

	cout<<"\nAns TD: "<<ans_TD<<endl;
	cout<<"Ans BU: "<<ans_BU<<endl;
	cout<<"Ans optimal: "<<ans_opt<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 