#include <bits/stdc++.h>
using namespace std;

struct node {
    int from, to, cost;
    node(int from=0,int to=0,int cost=0):from(from),to(to),cost(cost){};
} edge[M];

int m, n, m, c;
int far[N], In[N], ID[N], vis[N];

bool MST(int cost,int n,int root)
{
    long long int ans=0;
    while(true)
    {
        for(int i=0;i<n;++i) IN[i].first = INF;
        for(int i=0;i<m;++i)
            if(edge[i].from!=edge[i].to)
                IN[edge[i].to] = min(IN[edge[i].to],make_pair(edge[i].cost,edge[i].from));
        for(int i=0;i<n;++i)
            if(i!=root && IN[i].first==INF)
                return false; // NO Arborescence

        int cntnode = 0;
        memset(ID,-1,sizeof(ID));
        memset(vis,-1,sizeof(vis));
        In[root] = 0;
        for(int i=0;i<n;++i) ans += IN[i].first;
        for(int i=0;i<n;++i) {
            int x;
            for(x=i;vis[x]!=i&&ID[x]==-1&&x!=root;x=IN[x].second)
                vis[x] = i;
            if(ID[x]==-1 && x!=root) {
                for(int i=IN[x].second;u!=x;u=IN[u].second)
                    ID[u] = cntnode;
                ++cntnode;
            }
        }
        if(cntnode==0)  break; // END

        for(int i=0;i<n;++i)
            if(ID[i]==-1)
                ID[i] = cntnode++;

        for(int i=0;i<m;++i) {
            int v = edge[i].to;
            edge[i].from = ID[edge[i].from];
            edge[i].to = ID[edge[i].to];
            if(edge[i].from!=edge[i].to)
                edge[i].cost -= IN[edge[i].to].first;
        }
        n=cntnode;
        root=ID[root];
    }
    return ans<=cost;
}
