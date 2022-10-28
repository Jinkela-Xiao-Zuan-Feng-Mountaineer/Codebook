template<typename T,size_t kd>//有kd個維度 
struct kd_tree{
	struct point{
		T d[kd];
		T dist(const point &x)const{
			T ret=0;
			for(size_t i=0;i<kd;++i)ret+=abs(d[i]-x.d[i]);
			return ret;
		}
		bool operator==(const point &p){
			for(size_t i=0;i<kd;++i)
				if(d[i]!=p.d[i])return 0;
			return 1;
		}
		bool operator<(const point &b)const{
			return d[0]<b.d[0];
		}
	};
private:
	struct node{
		node *l,*r;
		point pid;
		int s;
		node(const point &p):l(0),r(0),pid(p),s(1){}
		~node(){delete l,delete r;}
		void up(){s=(l?l->s:0)+1+(r?r->s:0);}
	}*root;
	const double alpha,loga;
	const T INF;//記得要給INF，表示極大值 
	int maxn;
	struct __cmp{
		int sort_id;
		bool operator()(const node*x,const node*y)const{
			return operator()(x->pid,y->pid);
		}
		bool operator()(const point &x,const point &y)const{
			if(x.d[sort_id]!=y.d[sort_id])
				return x.d[sort_id]<y.d[sort_id];
			for(size_t i=0;i<kd;++i)
				if(x.d[i]!=y.d[i])return x.d[i]<y.d[i];
			return 0;
		}
	}cmp;
	int size(node *o){return o?o->s:0;}
	vector<node*> A;
	node* build(int k,int l,int r){
		if(l>r) return 0;
		if(k==kd) k=0;
		int mid=(l+r)/2;
		cmp.sort_id = k;
		nth_element(A.begin()+l,A.begin()+mid,A.begin()+r+1,cmp);
		node *ret=A[mid];
		ret->l = build(k+1,l,mid-1);
		ret->r = build(k+1,mid+1,r);
		ret->up();
		return ret;
	}
	bool isbad(node*o){
		return size(o->l)>alpha*o->s||size(o->r)>alpha*o->s;
	}
	void flatten(node *u,typename vector<node*>::iterator &it){
		if(!u)return;
		flatten(u->l,it);
		*it=u;
		flatten(u->r,++it);
	}
	void rebuild(node*&u,int k){
		if((int)A.size()<u->s)A.resize(u->s);
		auto it=A.begin();
		flatten(u,it);
		u=build(k,0,u->s-1);
	}
	bool insert(node*&u,int k,const point &x,int dep){
		if(!u) return u=new node(x), dep<=0;
		++u->s;
		cmp.sort_id=k;
		if(insert(cmp(x,u->pid)?u->l:u->r,(k+1)%kd,x,dep-1)){
			if(!isbad(u))return 1;
			rebuild(u,k);
		}
		return 0;
	}
	node *findmin(node*o,int k){
		if(!o)return 0; 
		if(cmp.sort_id==k)return o->l?findmin(o->l,(k+1)%kd):o;
		node *l=findmin(o->l,(k+1)%kd);
		node *r=findmin(o->r,(k+1)%kd);
		if(l&&!r)return cmp(l,o)?l:o;
		if(!l&&r)return cmp(r,o)?r:o;
		if(!l&&!r)return o;
		if(cmp(l,r))return cmp(l,o)?l:o;
		return cmp(r,o)?r:o;
	}
	bool erase(node *&u,int k,const point &x){
		if(!u)return 0;
		if(u->pid==x){
			if(u->r);
			else if(u->l) u->r=u->l, u->l=0;
			else return delete(u),u=0, 1;
			--u->s;
			cmp.sort_id=k;
			u->pid=findmin(u->r,(k+1)%kd)->pid;
			return erase(u->r,(k+1)%kd,u->pid);
		}
		cmp.sort_id=k;
		if(erase(cmp(x,u->pid)?u->l:u->r,(k+1)%kd,x))
			return --u->s, 1;
		return 0;
	}
	T heuristic(const T h[])const{
		T ret=0;
		for(size_t i=0;i<kd;++i)ret+=h[i];
		return ret;
	}
	int qM;
	priority_queue<pair<T,point>> pQ;
	void nearest(node *u,int k,const point &x,T *h,T &mndist){
		if(u==0||heuristic(h)>=mndist)return;
		T dist=u->pid.dist(x),old=h[k];
		/*mndist=std::min(mndist,dist);*/
		if(dist<mndist){
			pQ.push(std::make_pair(dist,u->pid));
			if((int)pQ.size()==qM+1)
				mndist=pQ.top().first,pQ.pop();
		}
		if(x.d[k]<u->pid.d[k]){
			nearest(u->l,(k+1)%kd,x,h,mndist);
			h[k] = abs(x.d[k]-u->pid.d[k]);
			nearest(u->r,(k+1)%kd,x,h,mndist);
		}else{
			nearest(u->r,(k+1)%kd,x,h,mndist);
			h[k] = abs(x.d[k]-u->pid.d[k]);
			nearest(u->l,(k+1)%kd,x,h,mndist);
		}
		h[k]=old;
	}
	vector<point>in_range;
	void range(node *u,int k,const point&mi,const point&ma){
		if(!u)return;
		bool is=1;
		for(int i=0;i<kd;++i)
			if(u->pid.d[i]<mi.d[i]||ma.d[i]<u->pid.d[i])
				{ is=0;break; }
		if(is) in_range.push_back(u->pid);
		if(mi.d[k]<=u->pid.d[k])range(u->l,(k+1)%kd,mi,ma);
		if(ma.d[k]>=u->pid.d[k])range(u->r,(k+1)%kd,mi,ma);
	}
public:
	kd_tree(const T &INF,double a=0.75):
	root(0),alpha(a),loga(log2(1.0/a)),INF(INF),maxn(1){}
	~kd_tree(){delete root;}
	void clear(){delete root,root=0,maxn=1;}
	void build(int n,const point *p){
		delete root,A.resize(maxn=n);
		for(int i=0;i<n;++i)A[i]=new node(p[i]);
		root=build(0,0,n-1);
	}
	void insert(const point &x){
		insert(root,0,x,__lg(size(root))/loga);
		if(root->s>maxn)maxn=root->s;
	}
	bool erase(const point &p){
		bool d=erase(root,0,p);
		if(root&&root->s<alpha*maxn)rebuild();
		return d;
	}
	void rebuild(){
		if(root)rebuild(root,0);
		maxn=root->s;
	}
	T nearest(const point &x,int k){
		qM=k;
		T mndist=INF,h[kd]={};
		nearest(root,0,x,h,mndist);
		mndist=pQ.top().first;
		pQ = priority_queue<pair<T,point>>();
		return mndist;//回傳離x第k近的點的距離 
	}
	const vector<point> &range(const point&mi,const point&ma){
		in_range.clear();
		range(root,0,mi,ma);
		return in_range;//回傳介於mi到ma之間的點vector 
	}
	int size(){return root?root->s:0;}
};
