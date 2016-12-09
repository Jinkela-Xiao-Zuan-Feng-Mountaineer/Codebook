//平面曼哈頓最小生成樹構造圖(去除非必要邊) 
#include<vector>
#include<algorithm>
#define T int
#define INF 0x3f3f3f3f
struct point{
	T x,y;
	int id;//每個點的編號都要不一樣，從0開始編號 
	point(){}
	T dist(const point &p)const{
		return std::abs(x-p.x)+std::abs(y-p.y);
	}
};
inline bool cmpx(const point &a,const point &b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
struct edge{
	int u,v;
	T cost;
	edge(int u,int v,const T&c):u(u),v(v),cost(c){}
	bool operator<(const edge&e)const{
		return cost<e.cost;
	}
};
struct bit_node{
	T mi;
	int id;
	bit_node(const T&mi=INF,int id=-1):mi(mi),id(id){}
};
std::vector<bit_node> bit;
inline void bit_update(int i,const T&data,int id){
	for(;i;i-=i&(-i)){
		if(data<bit[i].mi)bit[i]=bit_node(data,id);
	}
}
inline int bit_find(int i,int m){
	bit_node x;
	for(;i<=m;i+=i&(-i)){
		if(bit[i].mi<x.mi)x=bit[i];
	}
	return x.id;
}
inline std::vector<edge> build_graph(int n,point p[]){
	std::vector<edge> e;//回傳的邊就可以用來求最小生成樹 
	for(int dir=0;dir<4;++dir){//4種座標變換 
		if(dir%2){
			for(int i=0;i<n;++i)std::swap(p[i].x,p[i].y);
		}else if(dir==2){
			for(int i=0;i<n;++i)p[i].x=-p[i].x;
		}
		std::sort(p,p+n,cmpx);
		std::vector<T>ga(n),gb;
		for(int i=0;i<n;++i)ga[i]=p[i].y-p[i].x;
		gb=ga;
		std::sort(gb.begin(),gb.end());
		gb.resize(std::unique(gb.begin(),gb.end())-gb.begin());
		int m=gb.size();
		bit=std::vector<bit_node>(m+1);
		for(int i=n-1;i>=0;--i){
			int pos=std::lower_bound(gb.begin(),gb.end(),ga[i])-gb.begin()+1;
			int ans=bit_find(pos,m);
			if(~ans)e.push_back(edge(p[i].id,p[ans].id,p[i].dist(p[ans])));
			bit_update(pos,p[i].x+p[i].y,i);
		}
	}
	return e;
}
