template<char L='a',char R='z'>
class ac_automaton{
	private:
		struct joe{
			int next[R-L+1],fail,efl,ed,cnt_dp,vis;
			joe():ed(0),cnt_dp(0),vis(0){
				for(int i=0;i<=R-L;++i)next[i]=0;
			}
		};
	public:
		std::vector<joe> S;
		std::vector<int> q;
		int qs,qe,vt;
		ac_automaton():S(1),qs(0),qe(0),vt(0){}
		void clear(){
			q.clear();
			S.resize(1);
			for(int i=0;i<=R-L;++i)S[0].next[i]=0;
			S[0].cnt_dp=S[0].vis=qs=qe=vt=0;
		}
		void insert(const char *s){
			int o=0;
			for(int i=0,id;s[i];++i){
				id=s[i]-L;
				if(!S[o].next[id]){
					S.push_back(joe());
					S[o].next[id]=S.size()-1;
				}
				o=S[o].next[id];
			}
			++S[o].ed;
		}
		void build_fail(){
			S[0].fail=S[0].efl=-1;
			q.clear();
			q.push_back(0);
			++qe;
			while(qs!=qe){
				int pa=q[qs++],id,t;
				for(int i=0;i<=R-L;++i){
					t=S[pa].next[i];
					if(!t)continue;
					id=S[pa].fail;
					while(~id&&!S[id].next[i])id=S[id].fail;
					S[t].fail=~id?S[id].next[i]:0;
					S[t].efl=S[S[t].fail].ed?S[t].fail:S[S[t].fail].efl;
					q.push_back(t);
					++qe;
				}
			}
		}
		/*DP出每個前綴在字串s出現的次數並傳回所有字串被s匹配成功的次數O(N+M)*/
		int match_0(const char *s){
			int ans=0,id,p=0,i;
			for(i=0;s[i];++i){
				id=s[i]-L;
				while(!S[p].next[id]&&p)p=S[p].fail;
				if(!S[p].next[id])continue;
				p=S[p].next[id];
				++S[p].cnt_dp;/*匹配成功則它所有後綴都可以被匹配(DP計算)*/
			}
			for(i=qe-1;i>=0;--i){
				ans+=S[q[i]].cnt_dp*S[q[i]].ed;
				if(~S[q[i]].fail)S[S[q[i]].fail].cnt_dp+=S[q[i]].cnt_dp;
			}
			return ans;
		}
		/*多串匹配走efl邊並傳回所有字串被s匹配成功的次數O(N*M^1.5)*/ 
		int match_1(const char *s)const{
			int ans=0,id,p=0,t;
			for(int i=0;s[i];++i){
				id=s[i]-L;
				while(!S[p].next[id]&&p)p=S[p].fail;
				if(!S[p].next[id])continue;
				p=S[p].next[id];
				if(S[p].ed)ans+=S[p].ed;
				for(t=S[p].efl;~t;t=S[t].efl){
					ans+=S[t].ed;/*因為都走efl邊所以保證匹配成功*/
				}
			}
			return ans;
		}
		/*枚舉(s的子字串∩A)的所有相異字串各恰一次並傳回次數O(N*M^(1/3))*/
		int match_2(const char *s){
			int ans=0,id,p=0,t;
			++vt;
			/*把戳記vt+=1，只要vt沒溢位，所有S[p].vis==vt就會變成false
			這種利用vt的方法可以O(1)歸零vis陣列*/ 
			for(int i=0;s[i];++i){
				id=s[i]-L;
				while(!S[p].next[id]&&p)p=S[p].fail;
				if(!S[p].next[id])continue;
				p=S[p].next[id];
				if(S[p].ed&&S[p].vis!=vt){
					S[p].vis=vt;
					ans+=S[p].ed;
				}
				for(t=S[p].efl;~t&&S[t].vis!=vt;t=S[t].efl){
					S[t].vis=vt;
					ans+=S[t].ed;/*因為都走efl邊所以保證匹配成功*/
				}
			}
			return ans;
		}
		/*把AC自動機變成真的自動機*/
		void evolution(){
			for(qs=1;qs!=qe;){
				int p=q[qs++];
				for(int i=0;i<=R-L;++i)
					if(S[p].next[i]==0)S[p].next[i]=S[S[p].fail].next[i];
			}
		}
};
