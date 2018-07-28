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


using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef pair<i64, i64> pii;

i64 discreteLog(i64 a, i64 b, i64 m) // returns smallest non-negative x , where , a^x mod m = b
{
    i64 n = sqrt(m+0.0) + 2 , i ;

    map <i64,i64> M ;

    i64 r1 = b ;

    for(i=1 ; i<=n ; i++ )
    {
        r1 = (r1*a)%m ;
        M[r1] = i ;
    }

    i64 r = 1 ;
    for(i=1 ; i<=n ; i++ ) r = (r*a)%m ;

    r1 = r ;

    for(i=1 ; i<=n ; i++ , r1 = (r1*r)%m )
    {
        if( M.find( r1 )!=M.end() ) return i*n - M[ r1 ] ;
    }

    return -1 ;
}


class numberTheory{

public:
    numberTheory(){}

    pii extendedEuclid(i64 a, i64 b) { // returns x, y | ax + by = gcd(a,b)

        if(b == 0) return pii(1LL, 0LL);
        else {
            pii d = extendedEuclid(b, a % b);
            return pii(d.yy, d.xx - d.yy * (a / b));
        }

    }

    i64 modularInverse(i64 a, i64 n) {
        pair<i64,i64> ret = extendedEuclid(a, n);
        return ((ret.xx % n) + n) % n;
    }


    i64 bigMod(i64 a, i64 n , i64 m)
    {
        if(n==0) return 1 ;
        i64 ret = bigMod(a,n/2,m) ;
        ret = (ret*ret)%m ;
        if(n%2) ret = (ret*a)%m ;
        return ret ;
    }
};