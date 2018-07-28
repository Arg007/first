#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007
#define maxn 200005
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

//in this persistent segment tree every time we can add to value of some node
// and we can answer query value of index l to index r add in the interval i to j


class persistentSegTree
{

public:
    i64 *Tree ;
    int *left , *right , *root ;
    int cnt , n ;

    persistentSegTree(int _n)
    {
        n = _n ;
        Tree = new i64[21*(n+2)] ;
        left = new int[21*(n+2)] ;
        right = new int[21*(n+2)] ;
        root = new int[n+2] ;
        cnt = 1 ;
        root[0] = build(1,n) ;
    }

    int build(int b ,int e)
    {
        int cur = cnt++ ;
        if(b==e){
            Tree[cur] = 0 ;
            return cur ;
        }
        int m = (b+e)/2 ;
        left[cur] = build(b,m) ;
        right[cur] = build(m+1,e) ;
        Tree[cur] = Tree[left[cur]] + Tree[right[cur]] ;
        return cur ;
    }
    int update(int contemporary , int b, int e,int idx ,i64 val)
    {
        if( idx < b || idx > e ) return contemporary ;
        int cur = cnt++ ;
        if(b==e)
        {
            Tree[cur] = Tree[contemporary] + val ;
            return cur ;
        }
        int m = (b+e)/2 ;
        left[ cur ] = update(left[contemporary],b,m,idx,val) ;
        right[ cur ] = update(right[contemporary],m+1,e,idx,val) ;
        Tree[cur] = Tree[left[cur]] + Tree[right[cur]] ;
        return cur ;
    }

    i64 query(int i, int j ,int b, int e , int l, int r)
    {
        if(l>r) return 0 ;
        if( b>r || e<l ) return 0 ;
        if( l<=b && e<=r ) return Tree[j]-Tree[i] ;
        int m = (b+e)/2 ;
        i64 r1 = query(left[i],left[j],b,m,l,r) ;
        i64 r2 = query(right[i],right[j],m+1,e,l,r) ;
        return r1+r2 ;
    }

    i64 Query(int i, int j, int l ,int r)
    {
        if(  j<0 || i>n || i>j ||  l>r   ) return 0LL ;
        return query( root[i-1] , root[j] , 1 , n , l , r ) ;
    }

    ~persistentSegTree()
    {
        delete root ; delete left ; delete right ; delete Tree ;
    }
};

int a[200005] ;

#define Process(x1,y1,x2,y2) x.Query( x1,x2,y1,y2 )
#define process(x1,y1,x2,y2) ((Process(x1,y1,x2,y2)*( Process(x1,y1,x2,y2) - 1 ))/2)

int main()
{
    int i , j , k , l , m , n , q ;

    scanf("%d %d",&n,&q) ;

    for(i=1 ; i<=n ; i++)
    {
        int r ;
        scanf("%d",&r) ;
        a[r] = i ;
    }

    class persistentSegTree x(n) ;

    for(i=1 ; i<=n ; i++) x.root[i] = x.update(  x.root[i-1] , 1 , n , a[i] , 1LL ) ;

    for(i=1 ; i<=q ; i++)
    {
        int x1,y1,x2,y2 ;

        scanf("%d %d %d %d",&y1,&x1,&y2,&x2) ;
        i64 ret = process(1,1,n,n) ;
        ret -= process(1,1,x1-1,n) ;
        ret -= process(1,1,n,y1-1) ;
        ret -= process(x2+1,1,n,n) ;
        ret -= process(1,y2+1,n,n) ;
        ret += process(1,1,x1-1,y1-1) ;
        ret += process(x2+1,1,n,y1-1) ;
        ret += process(1,y2+1,x1-1,n) ;
        ret += process(x2+1,y2+1,n,n) ;

        printf("%lld\n",ret) ;
    }

    return 0 ;
}
