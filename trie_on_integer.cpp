//http://www.spoj.com/problems/SUBXOR/


#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
#define maxn 1005
#define IN freopen("C.in","r",stdin)
#define OUT freopen("output.txt","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int a[100005] ;

class TrieOfInteger{

    int mxLen , cnt ;
    int** Trie ;
    int* dp ;

public:

    TrieOfInteger(int mxLenn , int mx)
    {
        mxLen = mxLenn ; cnt = 1 ;
        Trie = new int*[2] ;
        Trie[0] = new int[mx+2] ;
        Trie[1] = new int[mx+2] ;
        Trie[0][1] = Trie[1][1] = 0 ;
        Trie[0][0] = Trie[1][0] = 0 ;
        dp = new int[mx] ;
        dp[0] = 0 ; dp[1] = 0 ;
    }

    void insert(int x)
    {
        int cur = 1 ;
        dp[1]++ ;

        for(int i= mxLen ; i>=0 ; i--)
        {
            int f = (bool)( (1<<i)&x ) ;
            if( !Trie[f][cur] )
            {
                Trie[f][cur] = ++cnt ;
                Trie[0][cnt] = Trie[1][cnt] = 0 ;
                dp[cnt] = 0 ;
            }
            cur = Trie[f][cur] ;
            dp[cur]++ ;
        }
    //    printf("cnt %d %d\n",cnt,dp[5]) ;
    }

    int query(int x , int k)
    {
        int cur = 1,ans = 0 ;
        for( int i=mxLen ; i>=0 ; i-- )
        {
            int xBit = (bool)((1<<i)&x) , kBit = (bool)((1<<i)&k) ;
            if(kBit==1) ans += dp[Trie[xBit][cur]] ;
            cur = Trie[ xBit^kBit ][cur] ;
        }
        return ans ;
    }


};

int main()
{
    int i , j , k , l , m , t=1 , tc , n ;

    scanf("%d",&tc) ;

    while(t++<=tc)
    {
        scanf("%d %d",&n,&k) ;

        class TrieOfInteger tr(23, max(23*n, 10000) ) ;

        tr.insert(0) ;

        for(i=1 ; i<=n ; i++) scanf("%d",&a[i]) ;

        int ret = 0 ;
        i64 ans = 0 ;

        for(i=1,ret=0 ; i<=n ; i++)
        {
            ret = ret^a[i] ;
            ans = ans + tr.query(ret,k) ;
            tr.insert(ret) ;
        }
        printf("%lld\n",ans) ;
    }

    return 0 ;
}