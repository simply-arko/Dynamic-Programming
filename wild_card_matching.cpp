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

int dp[2001][2001];

bool match_TD(string &s, string &p, int i=0, int j=0){
    cout<<i<<", "<<j<<endl;

    if(dp[i][j]!=-1){
    	cout<<"ddaaa";
    	return dp[i][j];
    }

    if(i>=s.size() && j>=p.size()){
        return dp[i][j] = true;
    }
    else if(i>=s.size()){
        while(j<p.size()){
            if(p[j]!='*')   return dp[i][j] = false;
            ++j;
        }
        return dp[i][j] = true;
    }else if(j>=p.size()){
        return dp[i][j] = false;

    }
    else if(p[j]=='*'){
        return dp[i][j] = match_TD(s, p, i+1, j) || match_TD(s, p, i, j+1);
    }
    else if(s[i]==p[j] || p[j]=='?'){
        return dp[i][j] = match_TD(s, p, i+1, j+1);
    }
    else{
        return dp[i][j] = false;
    }
}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	memset(dp, -1, sizeof(dp));

	string s, p;
	cin>>s>>p;
	if(match_TD(s, p))
		cout<<"true\n";
	else
		cout<<"false\n";

	for(int i=0; i<7; i++){
		for(int j=0; j<7; j++)
			cout<<dp[i][j]<<", ";
		cout<<endl;
	}

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 