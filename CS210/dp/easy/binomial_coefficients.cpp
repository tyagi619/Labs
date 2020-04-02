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

//Time complexity O(k)
    int main(){
        deathnote();
        int n,k;
        cin>>n>>k;
        ll ans=1;
        for(int i=0;i<k;i++){
            ans*=(n-i);
            ans/=(i+1);
        }

        cout<<ans<<endl;
        return 0;
    }


//Time complexity for below both methods is O(nk)
    // int main(){
    //     deathnote();
    //     int n,k;
    //     cin>>n>>k;

    //     ll c[n+1][k+1];

    //     for(int i=0;i<=n;i++){
    //         for(int j=0;j<=min(i,k);j++){
    //             if(j==0 || j==i){
    //                 c[i][j]=1;
    //             }
    //             else{
    //                 c[i][j]=c[i-1][j-1]+c[i-1][j];
    //             }
    //         }
    //     }

    //     cout<<c[n][k]<<endl;
    //     return 0;
    // }


//Space optimised method O(k)
/*
    int main(){
        deathnote();
        int n,k;
        cin>>n>>k;
        ll c[k+1];
        mem(c);
        c[0]=1;

        for(int i=1;i<=n;i++){
            for(int j=min(i,k);j>0;j--){
                c[j]=c[j]+c[j-1];
            }
        }

        cout<<c[k]<<endl;
        return 0;
    }
    
*/