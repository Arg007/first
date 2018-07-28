#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 100000007LL
#define maxn 100005
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
#define sq(x)  ((x)*(x))

using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef pair<i64, i64> pii;

// you need to pass an array to the function findSCC, in which result will be returned
//every node will be given a number, for nodes of a single connected component the number will be same
// this number representing nodes will be topologically sorted

class SCC{

public:

    vector <int> *g1 , *g2 ;
    int maxNode , *vis1 , *vis2 ;
    stack <int> st ;

    SCC(int MaxNode)
    {
        maxNode = MaxNode ;
        vis1 = new int[maxNode+2] ;
        vis2 = new int[maxNode+2] ;
        g1 = new vector<int>[maxNode+2] ;
        g2 = new vector<int>[maxNode+2] ;
    }

    void addEdge(int u, int v)
    {
        g1[u].pb(v) ;
        g2[v].pb(u) ;
    }

    void dfs1(int u)
    {
        if(vis1[u]==1) return ;
        vis1[u] = 1 ;
        for(int i=0 ; i<g1[u].size() ; i++) dfs1(g1[u][i]) ;
        st.push(u) ;
        return ;
    }
    void dfs2(int u, int cnt , int *ans)
    {
        if(vis2[u]==1) return ;
        vis2[u] = 1 ;
        for(int i=0 ; i<g2[u].size() ; i++) dfs2(g2[u][i],cnt,ans) ;
        ans[u] = cnt ;
    }
    int findSCC( int *ans )
    {
        for(int i=1 ; i<=maxNode ; i++) vis1[i] = 0 ;

        for(int i=1 ; i<=maxNode ; i++)
        {
            if(vis1[i]==0) dfs1(i) ;
        }

        int cnt = 0 ;
        for(int i=1 ; i<=maxNode ; i++) vis2[i] = 0 ;
        while( !st.empty() )
        {
            int u = st.top() ;
            if(vis2[u]==0)
            {
                ++cnt ;
                dfs2( u , cnt , ans ) ;
            }
            st.pop() ;
        }

        for(int i=1 ; i<=maxNode ; i++)
        {
            g1[i].clear() ;
            g2[i].clear() ;
        }
        delete vis1 ;
        delete vis2 ;

        return cnt ;
    }

};

vector <int> g[maxn] , G[maxn] ;
int which[maxn] ;
i64 c[maxn] , C[maxn] , dp[maxn] ;

int main()
{
    int i , j , k , l , m , n , t=1 , tc ;

    scanf("%d %d",&n,&m) ;

    for(i=1 ; i<= n ; i++) scanf("%lld",&c[i]) ;

    class SCC s(n) ;

    for(i=1 ; i<=m ; i++)
    {
        int u, v ;
        scanf("%d %d",&u,&v) ;
        s.addEdge(u,v) ;
        g[u].pb(v) ;
    }

    int total = s.findSCC(which) ;

//    for(i=1 ; i<=n ; i++) printf("%d : %d %d\n",i,which[i],total) ;

    for(i=1 ; i<=total ; i++) C[i] = 0 ;
    for(i=1 ; i<=n ; i++) C[which[i]] += c[i] ;

    for( i=1 ; i<=n ; i++)
    {
        for(j=0 ; j<g[i].size() ; j++) if(which[i]!=which[ g[i][j] ]) G[ which[i] ].pb( which[ g[i][j] ] ) ;
    }

    for(i=total ; i>=1 ; i--)
    {
        dp[i] = C[i] ;
 //       printf("dp %lld\n",dp[i]) ;
        i64 ret = 0 ;
        for(j=0 ; j< (int)G[i].size() ; j++){
   //         printf("i-->%d : %d\n",i,G[i][j]) ;
            ret = max(ret , dp[ G[i][j] ] ) ;
        }
        dp[i] += ret ;
    }

    for(i=1 ; i<=n ; i++){
        printf("%lld",dp[ which[i] ]) ;
        if(i<n) printf(" ") ;
        else printf("\n") ;
    }

    return 0 ;
}