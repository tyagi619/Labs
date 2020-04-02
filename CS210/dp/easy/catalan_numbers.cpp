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
        vll a(n+1);

        a[0]=1;
        a[1]=1;

        for(int i=2;i<=n;i++){
            a[i]=0;
            for(int j=0;j<i;j++){
                a[i]+=a[j]*a[i-j-1];
            }
        }

        cout<<a[n]<<endl;
        return 0;
    }

// Below is the O(n) time complexity approach
//nth catalan number C(2n,n)/(n+1)

/*
    ll binomial_coefficient(int n,int k){
        ll res=1;

        //C(n,k)=C(n,n-k)
        if(k>n-k){
            k=n-k;
        }
        
        //Calculate the value [n*(n-1)*....*(n-k+1)]/[1*2*3*...*k]
        for(int i=0;i<k;i++){
            res*=(n-i);
            res/=i+1;
        }

        return res;
    }

    int main(){
        deathnote();
        int n;
        cin>>n;

        ll ans=binomial_coefficient(2*n,n);

        cout<<ans/(n+1)<<endl;

        return 0;
    }
*/