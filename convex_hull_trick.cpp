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
#define INF 1000000000000000000LL
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2


using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

//convex hull for maximizing
//in case of minimization, just insert(-m,-c) and negate the result for query


class Line{

public:

    i64 m , c ;
    Line(){}
    Line(i64 _m, i64 _c) { m = _m  ; c = _c ; }
    i64 get(i64 x){ return m*x + c ; }
    bool operator < (const Line &line)const
    {
        if(m==line.m) return c<line.c ;
        return m<line.m ;
    }
};

i64 ceiling(i64 a, i64 b)
{
    if(b<0) {
        a = a*(-1) ; b = b*(-1) ;
    }
    if( a<0  ) return a/b ;
    i64 ans = (a/b) ;
    if(a%b) ans++ ;
    return ans ;
}
i64 interSection(Line l1 , Line l2)
{
    return ceiling( l1.c-l2.c , l2.m-l1.m ) ;
}
inline bool isBad(Line l1, Line l2 , Line l3)
{
    return interSection(l1,l2)>=interSection(l2,l3) ;
}
//special case when lines have non_decreasing slope
class ConvexHull{

public:
    vector <Line> hull ;
    vector <i64> start ;
    i64 pointer ;

    ConvexHull(){pointer = 0 ;}

    void addLine(i64 m, i64 c)
    {
        if(hull.size()!=0 && hull.back().m==m )
        {
            if( hull.back().c < c ){
                hull.pop_back() ;
                start.pop_back() ;
            }
            else return ;
        }
        while( hull.size() >= 2 )
        {
            int sz = hull.size() ;
            if( isBad(hull[sz-2],hull[sz-1],Line(m,c)) )
            {
                hull.pop_back() ;
                start.pop_back() ;
            }
            else break ;
        }
        if(hull.empty()) start.push_back(-INF) ;
        else start.push_back( ceiling( hull.back().c - c , m - hull.back().m ) ) ; //intersection of the line added and previous last line of the hull
        hull.push_back(Line(m,c)) ;
    }
    i64 query(i64 x)
    {
        i64 idx = upper_bound(start.begin(),start.end(),x) - start.begin() ;
        idx-- ;
        return hull[idx].get(x)  ;
    }
    void print()
    {
        auto it1 = hull.begin() ; auto it2 = start.begin() ;
        while(it1!=hull.end())
        {
            printf("m:%lld c:%lld start:%lld\n",it1->m,it1->c,*it2) ;
            it1++ ; it2++ ;
        }
    }

    void clear(){ hull.clear() ; start.clear() ; pointer = 0 ; }
};
//general case (fully dynamic variant) (nlogn)
/*
class ConvexHull{
public:
    set<Line> hull ;
    multiset<i64> start ;
    map < Line , i64 > M ;
    map<i64,Line> M1 ;

    void addLine(i64 m, i64 c)
    {
        set<Line> :: iterator it = hull.lower_bound(Line(m,c)) ;
        if(it!=hull.end() && it->m==m ) return ;
        if(it!=hull.begin())
        {
            it-- ;
            if(it->m==m)
            {
                start.erase( start.lower_bound(M[*it]) ) ;
                hull.erase(it) ;
            }
        }
        Line prev , cur , nxt ;
        it = hull.upper_bound(Line(m,c)) ;
        if(it!=hull.end() && it!=hull.begin() )
        {
            nxt =  *it ;
            it-- ;
            prev = *it ;
            if( isBad(prev,Line(m,c) ,nxt)  ) return ;
        }


        while(1)
        {
            it = hull.upper_bound(Line(m,c)) ;
            nxt = Line(m,c) ;
            if(it==hull.begin()) break ;
            it-- ;
            cur = *it ;
            if(it==hull.begin()) break ;
            it-- ;
            prev = *it ;

            if( isBad(prev,cur,nxt) )
            {
                start.erase( start.lower_bound( M[cur] ) ) ;
                hull.erase(cur) ;
            }
            else break ;
        }
        hull.insert( Line(m,c) ) ;
        it = hull.lower_bound(Line(m,c)) ;
        if(it!=hull.begin())
        {
            it-- ;
            start.insert(interSection(*it,Line(m,c))) ;
            M[ Line(m,c) ] = interSection(*it,Line(m,c)) ;
            M1[ interSection(*it,Line(m,c)) ] = Line(m,c) ;
        }
        else{
            start.insert(-INF) ;
            M[Line(m,c)] = -INF ;
            M1[-INF] = Line(m,c) ;
        }
        while(1)
        {
            it = hull.lower_bound(Line(m,c)) ;
            prev = *it ;
            it++ ;
            if(it==hull.end()) break ;
            cur = *it ;
            it++ ;
            if(it==hull.end()) break ;
            nxt = *it ;

            if( isBad(prev,cur,nxt) )
            {
                start.erase( start.lower_bound( M[cur] ) ) ;
                hull.erase(cur) ;
            }
            else break ;
        }
        it = hull.upper_bound(Line(m,c)) ;
        if(it!=hull.end()){
            start.erase( start.lower_bound(M[*it]) ) ;
            start.insert( interSection(Line(m,c),*it) ) ;
            M[ *it ] = interSection(Line(m,c),*it) ;
            M1[interSection(Line(m,c),*it)] = *it ;
        }
    }

    i64 query(i64 x)
    {
        auto it = start.upper_bound(x) ;
        it-- ;
        return M1[*it].get(x) ;
    }
    void print()
    {
        auto it1 = hull.begin() ; auto it2 = start.begin() ;
        while(it1!=hull.end())
        {
            printf("m:%lld c:%lld start:%lld\n",it1->m,it1->c,*it2) ;
            it1++ ; it2++ ;
        }
    }

};
*/
int main()
{
    ConvexHull ch ;

    while(true)
    {
        i64 m , c ;
        scanf("%lld %lld",&m,&c) ;
        ch.addLine(m,c) ;
      //  ch.print() ;
    }

}