struct Rule{
	vector<vector<Rule*> > p;
	void add(const vector<Rule*> &l){
		p.push_back(l);
	}
};
map<string,Rule*> NameRule;
map<Rule*,string> RuleName;
inline void init_Rule(){
	for(auto r:RuleName)delete r.first;
	RuleName.clear();
	NameRule.clear();
}
inline Rule *add_rule(const string &s){
	if(NameRule.find(s)!=NameRule.end())return NameRule[s];
	Rule *r=new Rule();
	RuleName[r]=s;
	NameRule[s]=r;
	return r;
}
typedef vector<Rule*> production;
struct State{
	Rule *r;
	int rid,dot_id,start,end;
	State(Rule *r,int rid,int dot,int start):r(r),rid(rid),dot_id(dot),start(start),end(-1){}
	State(Rule *r=0,int col=0):r(r),rid(-1),dot_id(-1),start(-1),end(col){}
	bool completed()const{
		return rid==-1||dot_id>=(int)r->p[rid].size();
	}
	Rule *next_term()const{
		if(completed())return 0;
		return r->p[rid][dot_id];
	}
	bool operator<(const State& b)const{
		if(start!=b.start)return start<b.start;
		if(dot_id!=b.dot_id)return dot_id<b.dot_id;
		if(r!=b.r)return r<b.r;
		return rid<b.rid;
	}
	void print()const{
		cout<<RuleName[r]<<"->";
		if(rid!=-1)for(size_t i=0;;++i){
			if((int)i==dot_id)cout<<" "<<"$";
			if(i>=r->p[rid].size())break;
			cout<<" "<<RuleName[r->p[rid][i]];
		}
		cout<<" "<<"["<<start<<","<<end<<"]"<<endl;
	}
};
struct Column{
	Rule *term;
	string value;
	vector<State> s;
	map<State,set<pair<State,State> > > div;
	//div比較像一棵 左兄右子的樹 
	Column(Rule *r,const string &s):term(r),value(s){}
	Column(){}
	bool add(const State &st,int col){
		if(div.find(st)==div.end()){
			div[st];
			s.push_back(st);
			s.back().end=col;
			return true;
		}else return false;
	}
};
inline vector<Column> lexer(string text){
	//tokenize，要自己寫，以下為範例 
	//他會把 input stream 變成 token stream，就是(terminal,value)pair
	vector<Column> token;
	replace(text.begin(),text.end(),',',' ');
	stringstream ss(text);
	while(ss>>text){
		if(text=="a"||text=="of")continue;
		if(text=="list"){
			token.push_back(Column(NameRule["("],"("));
		}else if(text=="and"){
			token.push_back(Column(NameRule[")"],")"));
		}else token.push_back(Column(NameRule["T"],text));
	}
	return token;
}
vector<Column> table;
inline void predict(int col,Rule *rul){
	for(size_t i=0;i<rul->p.size();++i){
		table[col].add(State(rul,i,0,col),col);
	}
}
inline void scan(int col,const State &s,Rule *r){
	if(r!=table[col].term)return;
	State ns(s.r,s.rid,s.dot_id+1,s.start);
	table[col].add(ns,col);
	table[col].div[ns].insert(make_pair(s,State(r,col)));
}
inline void complete(int col,const State &s){
	for(size_t i=0;i<table[s.start].s.size();++i){
		State &st=table[s.start].s[i];
		Rule *term=st.next_term();
		if(!term||term->p.size()==0)continue;
		if(term==s.r){
			State nst(st.r,st.rid,st.dot_id+1,st.start);
			table[col].add(nst,col);
			table[col].div[nst].insert(make_pair(st,s));
		}
	}
}
inline pair<bool,State> parse(Rule *GAMMA,const vector<Column > &token){
	table.resize(token.size()+1);
	for(size_t i=0;i<token.size();++i)table[i+1]=Column(token[i]);
	table[0]=Column();
	table[0].add(State(GAMMA,0,0,0),0);
	for(size_t i=0;i<table.size();++i){
		for(size_t j=0;j<table[i].s.size();++j){
			State state=table[i].s[j];
			if(state.completed())complete(i,state);
			else{
				Rule *term=state.next_term();
				if(term->p.size())predict(i,term);
				else if(i+1<table.size())scan(i+1,state,term);
			}
		}
	}
	for(size_t i=0;i<table.back().s.size();++i){
		if(table.back().s[i].r==GAMMA&&table.back().s[i].completed()){
			return make_pair(true,table.back().s[i]);
		}
	}
	return make_pair(false,State(0,-1));
}
struct node{//語法樹的節點 
	State s;
	vector<vector<node*> > child;//vector<node*>.size()>1表示ambiguous 
	node(const State &s):s(s){}
	node(){}
};
struct State_end_cmp{
	bool operator()(const State &a,const State &b)const{
		return a.end<b.end||(a.end==b.end&&a<b);
	}
};
map<State,node*,State_end_cmp> cache;
vector<node*> node_set;
inline void init_cache(){
	for(auto d:node_set)delete d;
	cache.clear();
	node_set.clear();
}
void _build_tree(const State &s,node *pa,bool amb=0){
	if(cache.find(s)!=cache.end()){
		pa->child.push_back(vector<node*>(1,cache[s]));
		return;
	}
	node *o;
	if(s.completed()){
		o=new node(s);
		if(amb)pa->child.back().push_back(o);
		else pa->child.push_back(vector<node*>(1,o));
	}else o=pa->child.back().back();
	amb=0;
	for(auto div:table[s.end].div[s]){
		if(!amb)_build_tree(div.first,pa);
		_build_tree(div.second,o,amb);
		amb=1;
	}
	if(s.completed())cache[s]=o;
}
inline node *build_tree(const State &s){
	init_cache();
	node o;
	_build_tree(s,&o);
	assert(o.child.size()==1);
	assert(o.child.back().size()==1);
	return o.child.back().back();
}
void print_tree(node *o,int dep=0){
	cout<<string(dep,' '),o->s.print();
	for(auto div:o->child){
		for(auto nd:div){
			print_tree(nd,dep+2);
		}
	}
}
//開始寫code:以下為加入語法的範例 
inline Rule *get_my_Rule(){
	Rule *S=add_rule("S"),*E=add_rule("E"),*L=add_rule("L");
	Rule *list=add_rule("("),*AND=add_rule(")"),*T=add_rule("T");
	S->add({list,E});
	S->add({list,L});
	L->add({E,L});
	L->add({E,AND,E});
	E->add({T});
	E->add({S});
	Rule *GAMMA=add_rule("GAMMA");//一定要有gamma rule當作是最上層的語法 
	GAMMA->add({S});
	return GAMMA;
}
