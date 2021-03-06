#include<bits/stdc++.h>
using namespace std;
#define MAX 105
#define EPS 1e-8
#define INF INT_MAX
typedef vector<double> VD;

double Eqns[MAX][MAX];
vector<int>Par[MAX];
vector<int>Child[MAX];

//Gaussian Elimination Template collected from Morris
double sol[MAX];
int nosol[MAX];

void Gauss(int n) {
    int i,j;
    for(i=1;i<=n;i++) {
        int k=i;
        for(j=i+1;j<=n;j++) if(fabs(Eqns[k][i])<fabs(Eqns[j][i])) k=j;
        if(fabs(Eqns[k][i])<EPS) continue;
        if(k!=i) for(j=1;j<=n+1;j++) swap(Eqns[k][j],Eqns[i][j]);

        for(j=1;j<=n;j++){
            if(i==j) continue;
            for(k=n+1;k>=i;k--){
                Eqns[j][k]-=Eqns[j][i]/Eqns[i][i]*Eqns[i][k];
            }
        }
    }
    memset(nosol,0,sizeof(nosol));
    for(i=n;i>=1;i--){
        if(fabs(Eqns[i][n+1])>EPS && fabs(Eqns[i][i])<EPS) nosol[i]=1;
        else{
            if(fabs(Eqns[i][n+1])<EPS) sol[i]=0;
            else sol[i]=Eqns[i][n+1]/Eqns[i][i];
        }
        for(j=i+1;j<=n;j++) if(fabs(Eqns[i][j])>EPS && nosol[j]) nosol[i] = 1;
    }
}

int main(){
    int n,q,p;
    int cs=0;
    while(scanf("%d",&n)==1 && n){
        printf("Case #%d:\n",++cs);
        for(int i=1;i<=n;i++) {Par[i].clear(); Child[i].clear();}
        memset(Eqns,0,sizeof(Eqns));

        int a,b;
        while(scanf("%d %d",&a,&b)==2 && a){
            Par[b].push_back(a);
            Child[a].push_back(b);
        }

        for(int i=1;i<=n;i++){
            Eqns[i][i]=1;
            for(int j=0;j<Par[i].size();j++) Eqns[i][Par[i][j]]-=1.0/Child[Par[i][j]].size();
            if(i==1) Eqns[i][n+1]=1;
        }

        Gauss(n);
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%d",&p);
            if(nosol[p]) printf("infinity\n");
            else printf("%.3lf\n",sol[p]);
        }
    }
}