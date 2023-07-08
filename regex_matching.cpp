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

int dp[51][51];
bool isMatch_TD(string &s, string &p, int i, int j) {
	if(i<0 && j<0)
		return true;
	else if(i<0){
        while(j>0 && p[j]=='*')
            j -= 2;
        return (j==-1);
    }
	else if(j<0)
		return false;

	if(dp[i][j]!=-1)
		return dp[i][j];

	if(p[j]=='*'){
		bool match = (p[j-1]==s[i] || p[j-1]=='.');
		return dp[i][j] = (isMatch_TD(s, p, i-1, j) && match) || isMatch_TD(s, p, i, j-2);
	}
	else if(s[i]==p[j] || p[j]=='.')
		return dp[i][j] = isMatch_TD(s, p, i-1, j-1);
	else
		return dp[i][j] = false;
}

bool isMatch_TD_up_front(string &s, string &p, int i=0, int j=0){
	if(i>=s.size() && j>=p.size())
		return true;
	else if(i>=s.size()){
		while(j+2<p.size() && p[j+1]=='*')
			j+=2;
		return (j==p.size()-2 && p[j+1]=='*');
	}
	else if(j>=p.size())
		return false;

	if(dp[i][j]!=-1)
		return dp[i][j];

	if(p[j+1]=='*'){
		bool match = (p[j]==s[i] || p[j]=='.');
		return dp[i][j] =  (match && isMatch_TD_up_front(s, p, i+1, j)) || isMatch_TD_up_front(s, p, i, j+2);
	}
	else if(s[i]==p[j] || p[j]=='.')
		return dp[i][j] =  isMatch_TD_up_front(s, p, i+1, j+1);
	else
		return dp[i][j] =  false;
}

int main(int argc, char const *argv[]){
	clock_t begin = clock();
	file_i_o();

	// write your code here...
	string s, p;
	cin>>s>>p;

	memset(dp, -1, sizeof(dp));
	bool ans_TD = isMatch_TD(s, p, s.size()-1, p.size()-1);
	bool ans_TD_up = isMatch_TD_up_front(s, p);

	cout<<"Ans TD: "<<ans_TD<<endl;
	cout<<"Ans TD UP: "<<ans_TD_up<<endl;

	#ifndef ONLINE_JUDGE
		clock_t end = clock();
		cout<<"\n\n Executed in: "<<double(end-begin)/CLOCKS_PER_SEC*1000<<" ms";
	#endif

	return EXIT_SUCCESS;
} 