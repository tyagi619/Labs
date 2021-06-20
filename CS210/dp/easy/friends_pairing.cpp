#include <bits/stdc++.h>
    using namespace std;

    /*
                      __       ____      __  __      __  _____   __      __       __ __         __         
                     /  \     |    \    |  ||  |    |  ||  __ \ |  |    |  |     /  \  \      /  /                  
                    /    \    |     \   |  ||  |    |  || |_/  ||  |    |  |    /    \  \    /  /                   
                   /  /\  \   |  |\  \  |  ||  |    |  ||  _  / |  |____|  |   /  /\  \  \  /  /                   
                  /  /__\  \  |  | \  \ |  ||  |    |  || | \ \ |   ____   |  /  /__\  \  \/  /                      
                 /  ______  \ |  |  \  \|  | \  \__/  / | |_/  ||  |    |  | /  ______  \    /                       
                /__/      \__\|__|   \_____|  \______/  |_____/ |__|    |__|/__/      \__\__/
                                                         
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
    

    #define pb                 push_back
    #define mp                 make_pair
    #define F                 first
    #define S                 second
    #define forn(i, n)         for(ll i = 0; i < n; i++)
    #define fori(i,a,b)        for(ll i = a; i < b; i++)
    #define ford(i,a,b)        for(ll i = a; i >=b; i--)
    #define input(vec)         for(ll i=0;i<vec.size();cin>>vec[i++]);
    #define output(vec)        for(ll i=0;i<vec.size();cout<<vec[i++]);cout<<endl;
    #define sort(vec)       sort(vec.begin(),vec.end());
    #define sz(vec)         vec.size();
    #define ln(s)           s.length();

    #define mem(x)             memset(x,0,sizeof(x));
    #define test int t;     cin >> t; while(t--)
    #define debug(x)         cout << "-->" << #x << ':' << x << "<--"<<endl;
    #define deathnote()     ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #define maxx             1e6+7
    #define PI                 3.1415926535897932384626433832795l
    #define sp(n)             cout<<fixed<<setprecision(n);

    int main(){
        deathnote();
        int n;
        cin>>n;

        vi f(n+1);
        f[0]=0;
        f[1]=1;
        f[2]=2;

        for(int i=3;i<=n;i++){
        	f[i]=f[i-1]+(i-1)*f[i-2];
        }

        cout<<f[n]<<endl;
        return 0;
    }