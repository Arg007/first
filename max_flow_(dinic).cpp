#include <bits/stdc++.h>
#define pf printf
#define sf scanf
#define INF 2000000000
#define PI (acos(-1.0))
#define DBG printf("Hi\n")
#define loop(i,n) for(i =1 ; i<=n; i++)
#define mp make_pair
#define pb push_back
#define mod 1000000007
#define maxn 100005
#define ff first
#define ss second
#define sq(x) ((x)*(x))
#define eps 0.0000000001
#define i64 long long int
#define ui64 unsigned long long int

using namespace std ;

struct dinic_maxflow
{
    int infi ;

    struct edge
    {
        int a, b, cap, flow ;
        edge(int _a, int _b, int _c, int _d)
        {
            a = _a, b = _b, cap = _c, flow = _d;
        }
    } ;


    int n, s, t, d [ 30001 ] , ptr [ 30001 ] , q [ 30001 * 10 ] ;
    vector < edge > e ;
    vector < int > g [ 30001 ] ;

    void add_edge ( int a, int b, int cap )
    {
        edge e1 = edge( a, b, cap, 0 ) ;
        edge e2 = edge( b, a, 0 , 0 ) ;
        g [ a ] . push_back ( ( int ) e. size ( ) ) ;
        e. push_back ( e1 ) ;
        g [ b ] . push_back ( ( int ) e. size ( ) ) ;
        e. push_back ( e2 ) ;
    }

    bool bfs ( )
    {
        int qh = 0 , qt = 0 ;
        q [ qt ++ ] = s ;
        memset ( d, -1 , sizeof d ) ;
        d [ s ] = 0 ;
        while ( qh < qt && d [ t ] == - 1 )
        {
            int v = q [ qh ++ ] ;
            for ( size_t i = 0 ; i < g [ v ] . size ( ) ; ++ i )
            {
                int id = g [ v ] [ i ] ,
                    to = e [ id ] . b ;
                if ( d [ to ] == - 1 && e [ id ] . flow < e [ id ] . cap )
                {
                    q [ qt ++ ] = to ;
                    d [ to ] = d [ v ] + 1 ;
                }
            }
        }
        return d [ t ] != - 1 ;
    }

    int dfs ( int v, int flow )
    {
        if ( ! flow )  return 0 ;
        if ( v == t )  return flow ;
        for ( ; ptr [ v ] < ( int ) g [ v ] . size ( ) ; ++ ptr [ v ] )
        {
            int id = g [ v ] [ ptr [ v ] ] ,
                to = e [ id ] . b ;
            if ( d [ to ] != d [ v ] + 1 )  continue ;
            int pushed = dfs ( to, min ( flow, e [ id ] . cap - e [ id ] . flow ) ) ;
            if ( pushed )
            {
                e [ id ] . flow += pushed ;
                e [ id ^ 1 ] . flow -= pushed ;
                return pushed ;
            }
        }
        return 0 ;
    }

    int dinic ( )
    {
        int flow = 0 ;
        for ( ;; )
        {
            if ( !bfs () )  break ;
            memset ( ptr, 0 , sizeof ptr ) ;
            while ( int pushed = dfs ( s, infi ) )
            {
                flow += pushed ;
                if(pushed == 0)break;
            }
        }
        return flow ;
    }

    dinic_maxflow( int _n, int _s, int _t , int infinity )
    {
        n = _n;
        s = _s;
        t = _t;
        infi = infinity ;
    }
};


int stickers[12][30] ;

int main()
{
    int i , j , k , l , m , n , t=1 , tc , x , ans ;

    sf("%d",&tc) ;

    while(t<=tc)
    {
        sf("%d %d",&n,&m) ;

        memset( stickers , 0 , sizeof(stickers) ) ;

        for(i=1 ; i<=n ; i++)
        {
            sf("%d",&k) ;
            for(j=1 ; j<=k ; j++)
            {
                sf("%d",&x) ;
                stickers[i][x]++ ;
            }
        }
        dinic_maxflow dm = dinic_maxflow(n*m+2 , 0,n*m+1,1500000001); //n*m+2 = total edge , 0 = source , n*m+1 = sink, 1500000001=setting the value of infinity

        for(i=1 ; i<=m ; i++)
        {
            dm.add_edge(0,i,stickers[1][i]) ;
            dm.add_edge(i,n*m+1,1) ;

            for(j=2 ; j<=n ; j++)
            {
                if( stickers[j][i]>1 ) dm.add_edge( (j-1)*m+i , i ,stickers[j][i]-1  ) ;
                if( stickers[j][i]==0) dm.add_edge( i , (j-1)*m+i, 1 ) ;
            }
        }
        for(i=2 ; i<=n ; i++)
        {
            for(j=1 ; j<=m ; j++)
            {
                for(k=1 ; k<=m ; k++)
                {
                    if(k==j) continue ;
                    if( stickers[i][j]!=0 || stickers[i][k]<=1 ) continue ;
                    dm.add_edge( (i-1)*m+j , (i-1)*m+k , 1 ) ;
                }
            }
        }
    //    DBG ;
        ans = dm.dinic() ;

        pf("Case #%d: %d\n",t++,ans) ;
    }


    return 0 ;
}