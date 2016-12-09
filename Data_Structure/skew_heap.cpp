template<typename T,typename _Compare=std::less<T> >
class skew_heap{
	private:
		struct node{
			T data;
			node *l,*r;
			node(const T&d):data(d),l(0),r(0){}
			~node(){delete l,delete r;}
		}*root;
		int _size;
		_Compare cmp;
		node *merge(node *a,node *b){
			if(!a||!b)return a?a:b;
			if(cmp(a->data,b->data))return merge(b,a);
			node *t=a->r;
			a->r=a->l;
			a->l=merge(b,t);
			return a;
		}
	public:
		skew_heap():root(0),_size(0){}
		~skew_heap(){delete root;}
		void clear(){delete root,root=0,_size=0;}
		void join(skew_heap &o){
			root=merge(root,o.root);
			o.root=0;
			_size+=o._size;
			o._size=0;
		}
		void swap(skew_heap &o){
			node *t=root;
			root=o.root;
			o.root=t;
			int st=_size;
			_size=o._size;
			o._size=st;
		}
		void push(const T&data){
			_size++;
			root=merge(root,new node(data));
		}
		void pop(){
			if(_size)_size--;
			node *tmd=merge(root->l,root->r);
			root->l=root->r=0;
			delete root;
			root=tmd;
		}
		const T& top(){return root->data;}
		int size(){return _size;}
		bool empty(){return !_size;}
};
