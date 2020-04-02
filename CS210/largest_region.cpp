	#include <bits/stdc++.h>
	using namespace std;

	//Calculate largest connected component and number of connected component in undirected graph

	/*
					  __	   ____		 __  __      __  _____   __      __       __  __         __         
					 /  \     |    \    |  ||  |    |  ||  __ \ |  |    |  |     /  \\  \      /  /                  
					/    \    |     \   |  ||  |    |  || |_/  ||  |    |  |    /    \\  \    /  /                   
				   /  /\  \   |  |\  \  |  ||  |    |  ||  _  / |  |____|  |   /  /\  \\  \  /  /                   
 				  /  /__\  \  |  | \  \ |  ||  |    |  || | \ \ |   ____   |  /  /__\  \\  \/  /                      
				 /  ______  \ |  |  \  \|  | \  \__/  / | |_/  ||  |    |  | /  ______  \\    /                       
				/__/      \__\|__|   \_____|  \______/  |_____/ |__|    |__|/__/      \__\\__/
                                                         
	*/



	typedef long long ll;
	typedef long double ld;
	typedef string str;
	typedef vector<int> vi;
	typedef vector<long long> vll;
	typedef vector<str> vs;
	typedef map<long long,long long> mll;
	typedef map<int,int> mii;
	typedef map<string,int> msi;
	typedef map<char,int> mci;
	typedef pair<int,int> pii;
	typedef pair<long long,long long> pll;
	

	#define pb 				push_back
	#define mp 				make_pair
	#define F 				first
	#define S 				second
	#define forn(i, n) 		for(ll i = 0; i < n; i++)
	#define fori(i,a,b)		for(ll i = a; i < b; i++)
	#define ford(i,a,b)		for(ll i = a; i >=b; i--)
	#define input(vec) 		for(ll i=0;i<vec.size();cin>>vec[i++]);
	#define output(vec)		for(ll i=0;i<vec.size();cout<<vec[i++]);cout<<endl;
	#define sort(vec)   	sort(vec.begin(),vec.end());
	#define sz(vec)         vec.size();
	#define ln(s)           s.length();

	#define mem(x) 			memset(x,0,sizeof(x));
	#define test int t; 	cin >> t; while(t--)
	#define debug(x) 		cout << "-->" << #x << ':' << x << "<--"<<endl;
	#define deathnote() 	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	#define maxx 			1e6+7
	#define PI 				3.1415926535897932384626433832795l
	#define sp(n) 			cout<<fixed<<setprecision(n);

	ll e;
	ll t;
	ll row,col;
	vector<ll> r={-1,-1,-1,0,0,1,1,1};
	vector<ll> c={-1,0,1,-1,1,-1,0,1};

	bool check(ll i ,ll j){
		if(i<row && i>=0 && j<col && j>=0)
			return true;

		return false;
	}

	void dfs(ll x,ll y, vector<vector<ll>> &a,vector<vector<ll>> &b){
		t++;
		b[x][y]=1;
		forn(i,8){
			if(check(x+r[i],y+c[i]) && !b[x+r[i]][y+c[i]] && a[x+r[i]][y+c[i]]){
				dfs(x+r[i],y+c[i],a,b);
				b[x+r[i]][y+c[i]]=1;
			}
		}

		b[x][y]=2;
		t++;
		e=t;

	}



	int main() {
		deathnote()

		cin>>row>>col;

		vector<vector<ll>> a(row,vector<ll> (col));
		vector<vector<ll>> b(row,vector<ll> (col));


		forn(i,row)\
			forn(j,col){
				cin>>a[i][j];
				b[i][j]=0;
			}

		ll max=0;
		ll count=0;	
		forn(i,row)
			forn(j,col){
				e=0;
				t=0;
				if(a[i][j]==1 && b[i][j]==0){
					dfs(i,j,a,b);
					count++;
				}
				if(e/2>max){
					max=e/2;
				}
			}

		cout<<max<<endl<<count<<endl;	
			

  		return 0;
	}
