#include <bits/stdc++.h>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007
#define maxn 10105
#define DBG pf("Hi\n")
#define INF 500000000
#define infd 1000000000.0 ;
#define i64 long long int
#define eps (1e-8)
#define ln 14

using namespace std ;

vector <int> g[maxn] , cost[maxn] , indexx[maxn] ;
int subsize[maxn] , n ;
int tr[maxn*4] ;

int baseArray[maxn] , ptr , otherEnd[maxn] , depth[maxn] , par[ln+2][maxn] ;
int chainNo , chainInd[maxn] , chainHead[maxn] , posInBase[maxn] ;

void build_tree(int cn, int b, int e)
{
    if(b==e){
        tr[cn] = baseArray[b] ;
        return ;
    }
    int l=cn*2 , r= cn*2+1 , m=(b+e)/2 ;

    build_tree(l,b,m) ;
    build_tree(r,m+1,e) ;

    tr[cn] = max(tr[l],tr[r]) ;
    return ;
}
void update_tree(int cn, int b, int e, int idx, int val)
{
    if( b>idx || e<idx ) return ;
    if(b==e && b==idx )
    {
        tr[cn] = val ;
        return ;
    }
    int l = cn*2 , r= cn*2+1 , m=(b+e)/2 ;
    update_tree(l,b,m,idx,val) ;
    update_tree(r,m+1,e,idx,val) ;

    tr[cn] = max(tr[l],tr[r]) ;
    return ;
}
int query_tree(int cn, int b, int e, int le, int ri)
{
    if( b>ri || e<le ) return -1 ;
    if( le<=b && e<=ri ) return tr[cn] ;

    int l = cn*2 , r= cn*2+1 , m=(b+e)/2 , r1 , r2  ;

    r1 = query_tree(l,b,m,le,ri) ;
    r2 = query_tree(r,m+1,e,le,ri) ;
    return max(r1,r2) ;
}

void dfs(int u, int prev , int _depth)
{
    subsize[u] = 1 ;
    depth[u] = _depth ;
    par[0][u] = prev ;

    for(int i=0 ; i<g[u].size() ; i++)
    {
        int v = g[u][i] ;
        if(v==prev) continue ;
        otherEnd[ indexx[u][i] ] = v ;
        dfs(v,u,_depth+1) ;
        subsize[u] += subsize[v] ;
    }
    return ;
}

void HLD(int cn , int c , int prev)
{
    if( chainHead[chainNo]==-1  ) chainHead[chainNo] = cn ;
    chainInd[cn] = chainNo ;

    baseArray[ptr] = c ;
    posInBase[cn] = ptr++ ;

    int sc = -1 , ncost , i , v ;

    for(i=0 ; i<g[cn].size() ; i++)
    {
        v = g[cn][i] ;
        if( v==prev ) continue ;
        if( sc==-1 || subsize[v] > subsize[sc] ){
            sc = v ;
            ncost = cost[cn][i] ;
        }
    }

    if(sc!=-1) HLD(sc,ncost,cn) ;

    for(i=0 ; i<g[cn].size() ; i++)
    {
        v = g[cn][i] ;
        if( v==prev || v==sc ) continue ;
        chainNo++ ;
        HLD(v,cost[cn][i],cn) ;
    }

}

int query_up(int u , int v)
{
    if(u==v) return 0 ;

    int uChain=chainInd[u] , vChain , ans=-1 , ret ;

    while(1)
    {
        if(u==v) return ans ;
        vChain = chainInd[v] ;
        if( uChain==vChain )
        {
            int ret = query_tree(1,0,ptr-1,posInBase[u]+1,posInBase[v]) ;
            ans = max(ret,ans) ;
            break ;
        }
        ret = query_tree( 1 , 0 , ptr-1 , posInBase[ chainHead[vChain] ],posInBase[v] ) ;
        ans = max(ret,ans) ;
        v = chainHead[vChain] ;
        v = par[0][v] ;
    }
    return ans ;
}

int query_lca(int u, int v)
{
    if(depth[u]>depth[v]) swap(u,v) ;

    int dif = depth[v]-depth[u] , i ;
    for(i=ln-1 ; i>=0 ; i--)
    {
        if( (1<<i) <=dif ){
            v = par[i][v] ;
            dif -= (1<<i) ;
        }
    }
    if(u==v) return v ;

    for(i=ln-1 ; i>=0; i--)
    {
        if( par[i][u]!=par[i][v] ){
            u = par[i][u] ;
            v = par[i][v] ;
        }
    }
    return par[0][u] ;
}

int query( int u , int v )
{
    int lca ;
    lca = query_lca(u,v) ;
    return max( query_up(lca,u) , query_up(lca,v) ) ;
}

void change(int edge, int c)
{
    int v= otherEnd[edge] ;
    update_tree( 1,0,ptr-1,posInBase[v],c ) ;
    return ;
}



int main()
{
    int i , j , k , l , m , t=1 , tc , u , v , c  , n , a , b;

    sf("%d",&tc) ;

    while(t<=tc)
    {
        sf("%d",&n) ;

        for(i=0 ; i<n ; i++)
        {
            g[i].clear() ; cost[i].clear() ; indexx[i].clear() ;
        }
        ptr = 0 ;
        chainNo = 0 ;
        memset(par,-1,sizeof(par)) ;
        memset(chainHead,-1,sizeof(chainHead)) ;

        for(i=1 ; i<n ; i++ )
        {
            sf("%d %d %d",&u,&v,&c) ;
            u-- ; v-- ;
            g[u].pb(v) ; cost[u].pb(c) ; indexx[u].pb(i-1) ;
            g[v].pb(u) ; cost[v].pb(c) ; indexx[v].pb(i-1) ;
        }

        dfs(0,-1,0) ;

        for(i=1; i<ln ; i++)
        {
            for(j=0 ; j<n ; j++)
            {
                if( par[i-1][j]!=-1 ) par[i][j] = par[i-1][ par[i-1][j] ] ;
            }
        }
        chainNo = 0 ;
        HLD(0,-1,-1) ;
        build_tree(1,0,ptr-1) ;

        while(1)
        {
            char s[10] ;
            sf("%s",s) ;
            if(s[0]=='Q'){
                sf("%d %d",&a,&b) ;
                pf("%d\n",query(a-1,b-1)) ;
            }
            else if(s[0]=='C'){
                sf("%d %d",&a,&b) ;
                change(a-1,b) ;
            }
            else break ;
        }
        if(t<tc) pf("\n") ;
        t++ ;
    }

    return 0 ;
}