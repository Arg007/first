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
#define IN freopen("promote.in","r",stdin)
#define OUT freopen("promote.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define sq 318
#define off 15

using namespace __gnu_pbds;
using namespace std ;

typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int toAdd[maxn] , efficiency[maxn] , ans[maxn] , idx[maxn] , subTreeSize[maxn] ;
vector <int> g[maxn] ;
ordered_set st[maxn] ;

int mergeTree(int x, int y)
{
    if( st[ idx[x] ].size() < st[ idx[y] ].size() ) swap(x,y) ;
    ordered_set :: iterator it ;

    for( it = st[ idx[y] ].begin() ; it!=st[idx[y]].end() ; it++ )
    {
        st[ idx[x] ].insert(*it) ;
    }
    return idx[x] ;
}

void dfs(int u, int par)
{
    idx[u] = u ; subTreeSize[u] = 1 ;
    st[u].insert(efficiency[u]) ;

    for(int i=0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        if(v==par) continue ;
        dfs(v,u) ;
        idx[u] = mergeTree(u,v) ;
        subTreeSize[u] += subTreeSize[v] ;
    }

    ans[u] = subTreeSize[u]-1 - st[ idx[u] ].order_of_key(efficiency[u]) ;
    return ;
}

int main()
{
    int i , j , k , l , m , n ;

    IN ; OUT ;

    sf("%d",&n) ;

    for(i=1 ; i<=n ; i++) sf("%d",&efficiency[i]) ;

    for(i=2 ; i<=n ; i++)
    {
        sf("%d",&m) ;
        g[m].pb(i) ;
    }

    dfs(1,-1) ;

    for(i=1 ; i<=n ; i++) pf("%d\n",ans[i]) ;

    return 0 ;
}