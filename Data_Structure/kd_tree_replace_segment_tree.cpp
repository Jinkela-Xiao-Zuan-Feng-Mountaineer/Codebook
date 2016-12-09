/*kd樹代替高維線段樹*/
struct node{
	node *l,*r;
	point pid,mi,ma;
	int s;
	int data;
	node(const point &p,int d):l(0),r(0),pid(p),mi(p),ma(p),s(1),data(d),dmin(d),dmax(d){}
	void up(){
		mi=ma=pid;
		s=1;
		if(l){
			for(int i=0;i<kd;++i){
				mi.d[i]=min(mi.d[i],l->mi.d[i]);
				ma.d[i]=max(ma.d[i],l->ma.d[i]);
			}
			s+=l->s;
		}
		if(r){
			for(int i=0;i<kd;++i){
				mi.d[i]=min(mi.d[i],r->mi.d[i]);
				ma.d[i]=max(ma.d[i],r->ma.d[i]);
			}
			s+=r->s;
		}
	}
	void up2(){
		//其他懶惰標記向上更新 
	}
	void down(){
		//其他懶惰標記下推 
	}
}*root;

/*檢查區間包含用的函數*/
inline bool range_include(node *o,const point &L,const point &R){
	for(int i=0;i<kd;++i){ 
		if(L.d[i]>o->ma.d[i]||R.d[i]<o->mi.d[i])return 0;
	}//只要(L,R)區間有和o的區間有交集就回傳true
	return 1;
}
inline bool range_in_range(node *o,const point &L,const point &R){
	for(int i=0;i<kd;++i){
		if(L.d[i]>o->mi.d[i]||o->ma.d[i]>R.d[i])return 0;
	}//如果(L,R)區間完全包含o的區間就回傳true
	return 1;
}
inline bool point_in_range(node *o,const point &L,const point &R){
	for(int i=0;i<kd;++i){
		if(L.d[i]>o->pid.d[i]||R.d[i]<o->pid.d[i])return 0;
	}//如果(L,R)區間完全包含o->pid這個點就回傳true
	return 1;
}

/*單點修改，以單點改值為例*/
void update(node *u,const point &x,int data,int k=0){
	if(!u)return;
	u->down();
	if(u->pid==x){
		u->data=data;
		u->up2();
		return;
	}
	cmp.sort_id=k;
	update(cmp(x,u->pid)?u->l:u->r,x,data,(k+1)%kd);
	u->up2();
}

/*區間修改*/ 
void update(node *o,const point &L,const point &R,int data){
	if(!o)return;
	o->down();
	if(range_in_range(o,L,R)){
		//區間懶惰標記修改 
		o->down();
		return;
	}
	if(point_in_range(o,L,R)){
		//這個點在(L,R)區間，但是他的左右子樹不一定在區間中
		//單點懶惰標記修改 
	}
	if(o->l&&range_include(o->l,L,R))update(o->l,L,R,data);
	if(o->r&&range_include(o->r,L,R))update(o->r,L,R,data);
	o->up2();
}

/*區間查詢，以總和為例*/ 
int query(node *o,const point &L,const point &R){
	if(!o)return 0;
	o->down();
	if(range_in_range(o,L,R))return o->sum;
	int ans=0;
	if(point_in_range(o,L,R))ans+=o->data;
	if(o->l&&range_include(o->l,L,R))ans+=query(o->l,L,R);
	if(o->r&&range_include(o->r,L,R))ans+=query(o->r,L,R);
	return ans;
}
