node *merge(node *a,node *b){
	if(!a||!b) return a?a:b;
	if(b->data<a->data) swap(a,b);
	swap(a->l,a->r);
	a->l=merge(b,a->l);
	return a;
}
