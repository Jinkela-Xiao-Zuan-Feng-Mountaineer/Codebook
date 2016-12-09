#include<vector>
struct splay_tree{
	int ch[2],pa;/*子節點跟父母*/ 
	bool rev;/*反轉的懶惰標記*/ 
	splay_tree():pa(0),rev(0){ch[0]=ch[1]=0;}
};
std::vector<splay_tree> node;
/*
有的時候用vector會TLE，要注意 
這邊以node[0]作為null節點 
*/
inline bool isroot(int x){/*判斷是否為這棵splay tree的根*/ 
	return node[node[x].pa].ch[0]!=x&&node[node[x].pa].ch[1]!=x;
}
inline void down(int x){/*懶惰標記下推*/ 
	if(node[x].rev){
		if(node[x].ch[0])node[node[x].ch[0]].rev^=1;
		if(node[x].ch[1])node[node[x].ch[1]].rev^=1;
		std::swap(node[x].ch[0],node[x].ch[1]);
		node[x].rev^=1;
	}
}
void push_down(int x){/*將所有祖先的懶惰標記下推*/ 
	if(!isroot(x))push_down(node[x].pa);
	down(x);
}
inline void up(int x){}/*將子節點的資訊向上更新*/ 
inline void rotate(int x){/*旋轉，會自行判斷轉的方向*/ 
	int y=node[x].pa,z=node[y].pa,d=(node[y].ch[1]==x);
	node[x].pa=z;
	if(!isroot(y))node[z].ch[node[z].ch[1]==y]=x;
	node[y].ch[d]=node[x].ch[d^1];
	node[node[y].ch[d]].pa=y;
	node[y].pa=x,node[x].ch[d^1]=y;
	up(y);
	up(x);
}
inline void splay(int x){/*將節點x伸展到所在splay tree的根*/ 
	push_down(x);
	while(!isroot(x)){
		int y=node[x].pa;
		if(!isroot(y)){
			int z=node[y].pa;
			if((node[z].ch[0]==y)^(node[y].ch[0]==x))rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
}
inline int access(int x){
	int last=0;
	while(x){
		splay(x);
		node[x].ch[1]=last;
		up(x);
		last=x;
		x=node[x].pa;
	}
	return last;/*回傳access後splay tree的根*/
}
inline void access(int x,bool is=0){/*is=0就是一般的access*/
	int last=0;
	while(x){
		splay(x);
		if(is&&!node[x].pa){
			//printf("%d\n",max(node[last].ma,node[node[x].ch[1]].ma));
		}
		node[x].ch[1]=last;
		up(x);
		last=x;
		x=node[x].pa;
	}
}
inline void query_edge(int u,int v){
	access(u);
	access(v,1);
}
inline void make_root(int x){
	access(x),splay(x);
	node[x].rev^=1;
}
inline void make_root(int x){
	node[access(x)].rev^=1;
	splay(x);
}
inline void cut(int x,int y){
	make_root(x);
	access(y);
	splay(y);
	node[y].ch[0]=0;
	node[x].pa=0;
}
inline void cut_parents(int x){
	access(x);
	splay(x);
	node[node[x].ch[0]].pa=0;
	node[x].ch[0]=0;
}
inline void link(int x,int y){
	make_root(x); 
	node[x].pa=y;
}
inline int find_root(int x){
	x=access(x);
	while(node[x].ch[0])x=node[x].ch[0];
	splay(x);
	return x;
}
inline int query(int u,int v){
/*
傳回uv路徑splay tree的根結點
這種寫法無法求LCA
*/
	make_root(u);
	return access(v);
}
inline int query_lca(int u,int v){
/*假設求鏈上點權的總和，sum是子樹的權重和，data是節點的權重*/
	access(u);
	int lca=access(v);
	splay(u);
	if(u==lca){
		//return node[lca].data+node[node[lca].ch[1]].sum;
	}else{
		//return node[lca].data+node[node[lca].ch[1]].sum+node[u].sum;
	}
}
struct EDGE{
	int a,b,w;
}e[10005]; 
int n;
std::vector<std::pair<int ,int > >G[10005];
/*first表示子節點，second表示邊的編號*/
int pa[10005],edge_node[10005];
/*pa是父母節點，暫存用的，edge_node是每個編被存在哪個點裡面的陣列*/ 
inline void bfs(int root){
/*在建構的時候把每個點都設成一個splay tree，不會壞掉*/ 
	std::queue<int > q;
	for(int i=1;i<=n;++i)pa[i]=0;
	q.push(root);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<(int)G[u].size();++i){
			int v=G[u][i].first;
			if(v!=pa[u]){
				pa[v]=u;
				node[v].pa=u;
				node[v].data=e[G[u][i].second].w;
				edge_node[G[u][i].second]=v;
				up(v);
				q.push(v);
			}
		}
	}
}
inline void change(int x,int b){
	splay(x);
	//node[x].data=b;
	up(x);
}
