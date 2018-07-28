#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007
#define maxn 100005
#define IN freopen("nocross.in","r",stdin)
#define OUT freopen("nocross.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 2000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

//range update(addition) , range query(summation)
//0 based, 0 to n

class segmentTree{
public:

    i64 *tr  , *lazy ;
    int n ;

    segmentTree(){}
    void init( int _n )
    {
        tr = new i64[4*(_n+1)] ;
        lazy = new i64[4*(_n+1)] ;
        n = _n ;
        build(1,0,n) ;
    }
    void build(int cn, int b, int e)
    {
        lazy[cn] = 0 ;
        if( b>e ) return ;
        if( b==e )
        {
            tr[cn] = 0 ;
            return ;
        }
        int l = cn*2 , r = cn*2+1 , m = (b+e)/2 ;
        build(l,b,m) ;
        build(r,m+1,e) ;
        tr[cn] = tr[l]+tr[r] ;
    }
    void relax( int cn, int b, int e )
    {
        tr[cn] += (long)(e-b+1)*lazy[cn] ;
        if( b!=e )
        {
            int l = cn*2 , r = cn*2+1 ;
            lazy[l] += lazy[cn] ;
            lazy[r] += lazy[cn] ;
        }
        lazy[cn] = 0 ;
    }
    void update(int cn, int b, int e ,int left , int right, i64 val)
    {
     //   printf("%d %d %d\n",cn,b,e) ;
        if( b>e ) return ;
        relax(cn,b,e) ;
        if( e<left || b>right ) return ;
        if( b>= left && e<=right )
        {
            lazy[cn] += val ;
            relax(cn,b,e) ;
            return ;
        }
        int l = cn*2 , r = cn*2+1 , m = (b+e)/2 ;
        update(l,b,m,left,right,val) ;
        update(r,m+1,e,left,right,val) ;
        tr[cn] = tr[l]+tr[r] ;
    }
    i64 query(int cn, int b, int e ,int left,int right)
    {
        if(b>e) return 0LL ;
        relax(cn,b,e) ;
        if( b>right || e<left ) return 0 ;
        if( b>= left && e<=right ) return tr[cn] ;
        int l = cn*2 , r = cn*2+1 , m = (b+e)/2 ;
        return query(l,b,m,left,right) + query(r,m+1,e,left,right) ;
    }
    void Update(int left, int right, i64 val){update(1,0,n,left,right,val) ;}
    i64 Query(int left, int right){ return query(1,0,n,left,right) ; } ;
}sg[maxn] ;

int par[maxn] , level[maxn] , sub[maxn] ;
vector <int> g[maxn] ;
void dfs( int u, int p , int pa , int l)
{
    par[u] = pa ;
    sub[u] = 1 ;
    level[u] = l ;
    for(int i=0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        if( v!=p )
        {
            dfs(v,u,pa,l+1) ;
            sub[u] += sub[v] ;
        }
    }
    return ;
}

int main()
{
    int i , j , k , l , m , n , u , v , q ;

    scanf("%d %d",&n,&q) ;

    for(i=1 ; i<n ; i++)
    {
        scanf("%d %d",&u,&v) ;
        g[u].pb(v) ; g[v].pb(u) ;
    }

    level[1] = 0 ;
    for(i=0 ; i<g[1].size() ; i++)
    {
        int u = g[1][i] ;
        dfs(u,1,u,1) ;
        sg[u].init(sub[u]) ;
    }
    sg[0].init(n) ;

    for(i=1 ; i<=q ; i++)
    {
        int qtype ;
        scanf("%d",&qtype) ;
        if(qtype==0)
        {
            int x, d ;
            scanf("%d %d %d",&v,&x,&d) ;
            if(v==1)
            {
                sg[0].Update(0,d,(i64)x) ;
            }
            else{

                int p = par[v] ;

                sg[p].Update(level[v],min(level[v]+d,sub[p]),x ) ;
                if( level[v]<=d )
                {
                    sg[p].Update(1,level[v]-1,x) ;
                    sg[0].Update(0,d-level[v],x) ;
                    sg[p].Update(1,d-level[v],-x) ;
                }
                else sg[p].Update(level[v]-d,level[v]-1,x) ;
            }
        }
        else
        {
            scanf("%d",&v) ;
            int p = par[v] ;
            i64 ans = sg[0].Query(level[v],level[v]) ;
            if(v!=1) ans += sg[p].Query(level[v],level[v]) ;
            printf("%lld\n",ans) ;
        }
    }

    return 0 ;
}
