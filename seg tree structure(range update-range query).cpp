#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
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

using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef pair<i64, i64> pii;

#define maxn 100000

int tr[4*maxn+5] , idx[4*maxn] , lazy[4*maxn+5] ;

void build(int cn, int b, int e)
{
    lazy[cn] = ; //add what you need

    if(b==e)
    {
        tr[cn] = ; //add what you need
        return ;
    }
    int l = cn*2 , r = cn*2+1 , m = (b+e)/2 ;

    build(l,b,m) ; build(r,m+1,e) ;

    tr[cn] = ; //add what you need
}

void relax(int cn, int b,int e)
{
    tr[cn] = ; // add what you need

    if(b!=e)
    {
        int l =cn*2 , r= cn*2 + 1 ;
        lazy[l] = ; // add what you need
        lazy[r] = ; // add what you need
    }
    lazy[cn] = ; // add what you need
}

void update(int cn, int b, int e, int left, int right, int val)
{
    if( lazy[cn]!=0 ) relax(cn,b,e) ;
    if( b>right || e<left  ) return ;
    if( b >=left && e<=right )
    {

        return ;
    }

    int l = cn*2 , r = cn*2+1 , m = (b+e)/2 ;

    update(l,b,m,left,right,val) ; update(r,m+1,e,left,right,val) ;

    tr[cn] =  ;
}

int query(int cn, int b, int e , int left, int right)
{
    if( lazy[cn]!=0 ) relax(cn,b,e) ;
    if( b>right || e<left  ) return ;  // add what you need
    if( b >=left && e<=right )
    {

        return ; // what you need
    }

    int l = cn*2 , r = cn*2+1 , m = (b+e)/2 ;

    int r1 = query(l,b,m,left,right) ;
    int r2 = query(r,m+1,e,left,right) ;

    return  ; // add what you need
}

