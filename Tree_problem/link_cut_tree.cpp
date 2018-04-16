struct splay_tree{
	int ch[2],pa;//子節點跟父母
	bool rev;//反轉的懶惰標記
	splay_tree():pa(0),rev(0){ch[0]=ch[1]=0;}
};
vector<splay_tree> nd;
//有的時候用vector會TLE，要注意 
//這邊以node[0]作為null節點 
bool isroot(int x){//判斷是否為這棵splay tree的根 
	return nd[nd[x].pa].ch[0]!=x&&nd[nd[x].pa].ch[1]!=x;
}
void down(int x){//懶惰標記下推
	if(nd[x].rev){
		if(nd[x].ch[0])nd[nd[x].ch[0]].rev^=1;
		if(nd[x].ch[1])nd[nd[x].ch[1]].rev^=1;
		swap(nd[x].ch[0],nd[x].ch[1]);
		nd[x].rev=0;
	}
}
void push_down(int x){//所有祖先懶惰標記下推
	if(!isroot(x))push_down(nd[x].pa);
	down(x);
}
void up(int x){}//將子節點的資訊向上更新
void rotate(int x){//旋轉，會自行判斷轉的方向
	int y=nd[x].pa,z=nd[y].pa,d=(nd[y].ch[1]==x);
	nd[x].pa=z;
	if(!isroot(y))nd[z].ch[nd[z].ch[1]==y]=x;
	nd[y].ch[d]=nd[x].ch[d^1];
	nd[nd[y].ch[d]].pa=y;
	nd[y].pa=x,nd[x].ch[d^1]=y;
	up(y),up(x);
}
void splay(int x){//將x伸展到splay tree的根
	push_down(x);
	while(!isroot(x)){
		int y=nd[x].pa;
		if(!isroot(y)){
			int z=nd[y].pa;
			if((nd[z].ch[0]==y)^(nd[y].ch[0]==x))rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
}
int access(int x){
	int last=0;
	while(x){
		splay(x);
		nd[x].ch[1]=last;
		up(x);
		last=x;
		x=nd[x].pa;
	}
	return last;//access後splay tree的根
}
void access(int x,bool is=0){//is=0就是一般的access
	int last=0;
	while(x){
		splay(x);
		if(is&&!nd[x].pa){
			//printf("%d\n",max(nd[last].ma,nd[nd[x].ch[1]].ma));
		}
		nd[x].ch[1]=last;
		up(x);
		last=x;
		x=nd[x].pa;
	}
}
void query_edge(int u,int v){
	access(u);
	access(v,1);
}
void make_root(int x){
	access(x),splay(x);
	nd[x].rev^=1;
}
void make_root(int x){
	nd[access(x)].rev^=1;
	splay(x);
}
void cut(int x,int y){
	make_root(x);
	access(y);
	splay(y);
	nd[y].ch[0]=0;
	nd[x].pa=0;
}
void cut_parents(int x){
	access(x);
	splay(x);
	nd[nd[x].ch[0]].pa=0;
	nd[x].ch[0]=0;
}
void link(int x,int y){
	make_root(x); 
	nd[x].pa=y;
}
int find_root(int x){
	x=access(x);
	while(nd[x].ch[0])x=nd[x].ch[0];
	splay(x);
	return x;
}
int query(int u,int v){
//傳回uv路徑splay tree的根結點
//這種寫法無法求LCA
	make_root(u);
	return access(v);
}
int query_lca(int u,int v){
//假設求鏈上點權的總和，sum是子樹的權重和，data是節點的權重
	access(u);
	int lca=access(v);
	splay(u);
	if(u==lca){
		//return nd[lca].data+nd[nd[lca].ch[1]].sum
	}else{
		//return nd[lca].data+nd[nd[lca].ch[1]].sum+nd[u].sum
	}
}
struct EDGE{
	int a,b,w;
}e[10005]; 
int n;
vector<pair<int,int>> G[10005];
//first表示子節點，second表示邊的編號
int pa[10005],edge_node[10005];
//pa是父母節點，暫存用的，edge_node是每個編被存在哪個點裡面的陣列
void bfs(int root){
//在建構的時候把每個點都設成一個splay tree
	queue<int > q;
	for(int i=1;i<=n;++i)pa[i]=0;
	q.push(root);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(auto P:G[u]){
			int v=P.first;
			if(v!=pa[u]){
				pa[v]=u;
				nd[v].pa=u;
				nd[v].data=e[P.second].w;
				edge_node[P.second]=v;
				up(v);
				q.push(v);
			}
		}
	}
}
void change(int x,int b){
	splay(x);
	//nd[x].data=b;
	up(x);
}
