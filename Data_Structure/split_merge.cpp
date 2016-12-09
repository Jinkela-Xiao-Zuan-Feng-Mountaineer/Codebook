void split(node *o,node *&a,node *&b,int k){
	if(!o)a=b=0;
	else{
		//o=new node(*o);
		o->down();
		if(k<=size(o->l)){
			b=o;
			split(o->l,a,b->l,k);
		}else{
			a=o;
			split(o->r,a->r,b,k-size(o->l)-1);
		}
		o->up();
	}
}
node *merge(node *a,node *b){
	if(!a||!b)return a?a:b;
	static int x;
	if(x++%(a->s+b->s)<a->s){
		//a=new node(*a);
		a->down();
		a->r=merge(a->r,b);
		a->up();
		return a;
	}else{
		//b=new node(*b);
		b->down();
		b->l=merge(a,b->l);
		b->up();
		return b;
	}
}
