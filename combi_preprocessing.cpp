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

const i64 N = 200000 ;

i64 fact[N+5] , invFact[N+5] ;

i64 C(i64 n, i64 r)
{
    if( n<0 || r<0 || r>n ) return 0 ;
    i64 ret = (fact[n]*invFact[r])%mod ;
    return (ret*invFact[n-r])%mod ;
}

void preprocess()
{
    numberTheory nt ;

    fact[0] = 1 ;
    for(i64 x=1 ; x<=N ; x++) fact[x] = (fact[x-1]*x)%mod ;

    invFact[N] = nt.modularInverse(fact[N],mod) ;

    for(i64 x=N-1 ; x>=0 ; x--) invFact[x] = (invFact[x+1]*(x+1) )%mod ;
}

int mulFact[N+5] , num[N+5] ;
vector <int> p ;

void sieve()
{
    int i , j ;
    for(i=2 ; i*i<=N ;i++)
    {
        if(num[i]==0) for(j=i+i ; j<=N ; j+=i) num[j] = 1 ;
    }
    for(i=2 ; i<=N ; i++) if(num[i]==0) p.pb(i) ;
}

int main()
{
    preprocess() ;
    sieve() ;

    int i , j , k , l , m , n ;

    for(i=0 ; i<p.size() ; i++)
    {
        for(j=p[i] ; j<=100000 ; j+=p[i]) mulFact[j]++ ;
    }

    for(i=2 ; (i*i)<=100000 ; i++)
    {
        for(j=(i*i) ; j<=100000 ; j+= (i*i) ) mulFact[j] = 0 ;
    }

    for(i=2 ; i<=100000 ; i++)
    {
        if(mulFact[i]==0) continue ;
        if( mulFact[i]%2==0 ) mulFact[i] =1 ;
        else mulFact[i] = -1 ;
    }

    for(i=2 ; i<=30 ; i++) printf("%d %d\n",i,mulFact[i]) ;

    return 0 ;
}
