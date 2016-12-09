#include<bits/stdc++.h>//POJ 2104
using namespace std;
struct node{
	int l,r;
	int data;
	node(int l,int r,int d):l(l),r(r),data(d){}
};
vector<node> nds;
inline void up(int o,int l,int r){
	nds[o].data=nds[l].data+nds[r].data;
}
inline int new_node(int l,int r,int d){
	nds.push_back(node(l,r,d));
	return nds.size()-1;
}
inline int new_node(const node &nd){
	nds.push_back(nd);
	return nds.size()-1;
}
int build_tree(int l,int r){
	int nd=new_node(-1,-1,0);
	if(l==r)return nd;
	int mid=(l+r)/2;
	int L=build_tree(l,mid);//執行時vector會被重構 
	int R=build_tree(mid+1,r);//一定要這樣寫 
	nds[nd].l=L;
	nds[nd].r=R;
	//up(nd,L,R);
	return nd;
}
int insert(int l,int r,int rt,int x,int d){
	if(x<l||r<x)return rt;
	int nd=new_node(nds[rt]);
	if(l==r&&l==x)nds[nd].data+=d;
	else{
		int mid=(l+r)/2;
		int L=insert(l,mid,nds[nd].l,x,d);
		int R=insert(mid+1,r,nds[nd].r,x,d);
		nds[nd].l=L;
		nds[nd].r=R;
		up(nd,L,R);
	}
	return nd;
}
inline int cal(int L,int R){
	return nds[R].data-nds[L].data;
}
int find(int l,int r,int L,int R,int k){
	if(l==r)return l;
	int mid=(l+r)/2;
	int add=cal(nds[L].l,nds[R].l);
	if(k<=add)return find(l,mid,nds[L].l,nds[R].l,k);
	return find(mid+1,r,nds[L].r,nds[R].r,k-add);
}
int n,m;
int s[100005];
int root[100005];
int main(){
	while(~scanf("%d%d",&n,&m)){
		nds.clear();
		vector<int> lsh;
		for(int i=1;i<=n;++i){
			scanf("%d",&s[i]);
			lsh.push_back(s[i]);
		}
		sort(lsh.begin(),lsh.end());
		lsh.resize(unique(lsh.begin(),lsh.end())-lsh.begin());
		int N=(int)lsh.size()-1;
		root[0]=build_tree(0,N);
		for(int i=1;i<=n;++i){
			s[i]=lower_bound(lsh.begin(),lsh.end(),s[i])-lsh.begin();
			root[i]=insert(0,N,root[i-1],s[i],1);
		}
		while(m--){
			int a,b,k;
			scanf("%d%d%d",&a,&b,&k);
			int res=find(0,N,root[a-1],root[b],k);
			printf("%d\n",lsh[res]);
		}
	}
	return 0;
}