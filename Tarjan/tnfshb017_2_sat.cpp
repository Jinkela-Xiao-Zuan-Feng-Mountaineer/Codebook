#include<bits/stdc++.h>
using namespace std;  
#define MAXN 8001
#define MAXN2 MAXN*4 
#define n(X) ((X)+2*N)
vector<int>  v[MAXN2];  
vector<int> rv[MAXN2];  
vector<int>  vis_t;  
int N,M;  
void addedge(int s,int e){  
    v[s].push_back(e);  
    rv[e].push_back(s);  
}  
int scc[MAXN2];  
bool vis[MAXN2]={false};  
void dfs(vector<int> *uv,int n,int k=-1){  
    vis[n]=true;  
    for(int i=0;i<uv[n].size();++i)  
        if(!vis[uv[n][i]])  
            dfs(uv,uv[n][i],k);  
    if(uv==v)vis_t.push_back(n);   
    scc[n]=k;  
}  
void solve(){  
    for(int i=1;i<=N;++i){
        if(!vis[i])dfs(v,i);
        if(!vis[n(i)])dfs(v,n(i)); 
    }
    memset(vis,0,sizeof(vis));  
    int c=0;  
    for(int i=vis_t.size()-1;i>=0;--i)  
        if(!vis[vis_t[i]])  
            dfs(rv,vis_t[i],c++);  
}  
int main(){  
    int a,b;  
    scanf("%d%d",&N,&M);  
    for(int i=1;i<=N;++i){  
        // (A or B)&(!A & !B) A^B  
        a=i*2-1;  
        b=i*2;  
        addedge(n(a),b);  
        addedge(n(b),a);  
        addedge(a,n(b));  
        addedge(b,n(a));  
    }  
    while(M--){  
        scanf("%d%d",&a,&b);  
        a = a>0?a*2-1:-a*2;    
        b = b>0?b*2-1:-b*2;  
        // A or B  
        addedge(n(a),b);  
        addedge(n(b),a);  
    }  
    solve();  
    bool check=true;  
    for(int i=1;i<=2*N;++i)  
        if(scc[i]==scc[n(i)])  
            check=false;  
    if(check){  
        printf("%d\n",N);  
        for(int i=1;i<=2*N;i+=2){  
            if(scc[i]>scc[i+2*N])  
                putchar('+');  
            else  
                putchar('-');  
        }  
        putchar('\n');  
    }else puts("0");
    return 0;  
}
