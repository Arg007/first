//problem link- http://codeforces.com/gym/100570/problem/F
#include <bits/stdc++.h>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007
#define maxn 100005
#define DBG pf("Hi\n")
#define INF 50000000
#define infd 1000000000.0 ;
#define i64 long long int
#define eps (1e-8)
#define ff first
#define ss second
#define ln 17

using namespace std ;

int n , nn , PAR[maxn] , DEPTH[maxn] ;

bool isCentroid[maxn] ;

vector <int> GRAPH[maxn] ;
vector <i64> EDGE[maxn] ;

int PAR_LCA[ln][maxn] , SUBSIZE[maxn] ;

i64 DISTANCE[maxn] ;
// 0 based indexing is used
//all the variables declared till now is for generalized version (weighted) , for unweighted use edge cost as 1

vector <i64> st1[maxn] ;   //for this specific problem
vector <i64> st2[maxn] ;  ////for this specific problem

void DFS0(int u,int prev , int _depth , i64 _cost)
{
    PAR_LCA[0][u] = prev ;
    DEPTH[u] = _depth ;
    DISTANCE[u] = _cost ;
    int v ;
    for(int i=0 ; i<GRAPH[u].size() ; i++)
    {
        v = GRAPH[u][i] ;
        if( v==prev ) continue ;
        DFS0(v,u,_depth+1,_cost+EDGE[u][i]) ;
    }
    return ;
}

void PREPROCESS(int u)
{
    int i , j , k ;

    DFS0(u,-1,0,0) ;
    for(i=1 ; i<ln ; i++)
    {
        for(j=0 ; j<n ; j++)
        {
            if( PAR_LCA[i-1][j]!=-1 ) PAR_LCA[i][j] = PAR_LCA[i-1][ PAR_LCA[i-1][j] ] ;
        }
    }
    return ;
}

int LCA(int u, int v)
{
    if(DEPTH[u]>DEPTH[v]) swap(u,v) ;

    int dif = DEPTH[v]-DEPTH[u] , i ;
    for(i=ln-1 ; i>=0 ; i--)
    {
        if( (1<<i) <=dif ){
            v = PAR_LCA[i][v] ;
            dif -= (1<<i) ;
        }
    }
    if(u==v) return v ;

    for(i=ln-1 ; i>=0; i--)
    {
        if( PAR_LCA[i][u]!=PAR_LCA[i][v] ){
            u = PAR_LCA[i][u] ;
            v = PAR_LCA[i][v] ;
        }
    }
    return PAR_LCA[0][u] ;
}

i64 DIST(int u, int v)
{
    int lc = LCA(u,v) ;
    return (DISTANCE[u]+DISTANCE[v] - 2LL*DISTANCE[lc]) ;
}

void DFS1(int u, int prev)
{
    SUBSIZE[u] = 1 ; nn++ ;
    for(int i=0 ; i<GRAPH[u].size() ; i++)
    {
        int v = GRAPH[u][i] ;
        if( v==prev || isCentroid[v]==true ) continue ;
        DFS1(v,u) ;
        SUBSIZE[u] += SUBSIZE[v] ;
    }
    return ;
}

int DFS2(int u, int prev)
{
    for(int i=0 ; i<GRAPH[u].size() ; i++)
    {
        int v= GRAPH[u][i] ;
        if( v==prev || isCentroid[v]==true ) continue ;
        if( SUBSIZE[v] > nn/2 ) return DFS2( v , u ) ;
    }
    return u ;
}

void DECOMPOSE(int u ,int prev)
{
 //   printf("searching centroid from: %d previous node: %d\n",u+1,prev+1) ;
    nn = 0 ;

    DFS1( u , prev ) ;

    int centroid = DFS2(u,prev) ;
    PAR[centroid] = prev ;
    isCentroid[centroid] = true ;

 //   pf("found centroid : %d\n",centroid+1) ;

    for(int i=0 ; i<GRAPH[centroid].size() ; i++)
    {
        int v = GRAPH[centroid][i] ;
        if( v==prev || isCentroid[v]==true ) continue ;
//        g[v].erase(centroid) ;
        DECOMPOSE( v , centroid ) ;
    }
    GRAPH[centroid].clear() ;
}

int query(int u , i64 maxDist)
{
    int ans = 0 , par , prev ;
    int ret ;

    ans = upper_bound( st1[u].begin() , st1[u].end() , maxDist ) - st1[u].begin() ;

    par = PAR[u] ;
    prev = u ;

    while(par!=-1)
    {
        i64 d = maxDist - DIST(u,par) ;
        if(d>=0){
            ans += upper_bound( st1[par].begin() , st1[par].end() , d ) - st1[par].begin() ;
            ans -= upper_bound( st2[prev].begin() ,st2[prev].end(), d ) - st2[prev].begin() ;
        }
        prev= par ;
        par = PAR[par] ;
    }
    return ans ;
}

int main()
{
    int i , j , k , l , m , q ;
    int u , v ;


    sf("%d %d",&n,&m) ;

    for(i=1 ; i<n ; i++)
    {
        i64 c ;
        sf("%d %d %lld",&u,&v,&c) ;
        u-- ; v-- ;
        GRAPH[u].pb(v) ; GRAPH[v].pb(u) ;
        EDGE[u].pb(c) ; EDGE[v].pb(c) ;
    }

    PREPROCESS(0) ;   // for calculating distances
    DECOMPOSE(0,-1) ; // Decomposition
// now we have PAR[] , which denotes the PAR of each node in decomposed tree


//    if(n==10)  DBG ;

    for(i=0 ; i<n; i++)
    {
        int p = i ;

        while(p!=-1)
        {
            st1[p].pb( DIST(i,p) ) ;
            if(PAR[p]!=-1) st2[p].pb( DIST(i,PAR[p]) ) ;
            p = PAR[p] ;
        }
    }

    for(i=0 ; i<n ; i++)
    {
        sort( st1[i].begin() , st1[i].end() ) ;
        sort( st2[i].begin() , st2[i].end() ) ;
    }

    for(i=1 ; i<=m ; i++)
    {
        i64 maxDist ;
        sf("%d %lld",&u,&maxDist) ;
        u-- ;
        pf("%d\n",query(u,maxDist)) ;
    }

    return 0 ;
}