template<typename T>
struct point{
	T x,y;
	point(){}
	point(const T&x,const T&y):x(x),y(y){}
	point operator+(const point &b)const{return point(x+b.x,y+b.y);}
	point operator-(const point &b)const{return point(x-b.x,y-b.y);}
	point operator*(const T &b)const{return point(x*b,y*b);}
	point operator/(const T &b)const{return point(x/b,y/b);}
	bool operator==(const point &b)const{
		return x==b.x&&y==b.y;
	}
	T dot(const point &b)const{
		return x*b.x+y*b.y;
	}
	T cross(const point &b)const{
		return x*b.y-y*b.x;
	}
	point normal()const{/*求法向量*/
		return point(-y,x);
	}
	T abs2()const{/*向量長度的平方*/
		return dot(*this);
	}
	T rad(const point &b)const{/*兩向量的弧度(夾角)*/
		return fabs(atan2(fabs(cross(b)),dot(b)));
	}
};
template<typename T>
struct line{
	line(){}
	point<T> p1,p2;
	T a,b,c;/*ax+by+c=0*/
	line(const point<T>&x,const point<T>&y):p1(x),p2(y){}
	void pton(){/*轉成一般式*/ 
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;
	}
	T cross(const point<T> &p)const{/*點和有向直線的關係，>0左邊、=0在線上<0右邊*/
		return (p2-p1).cross(p-p1);
	}
	bool point_on_segment(const point<T>&p)const{/*點是否線段上*/ 
		return cross(p)==0&&(p1-p).dot(p2-p)<=0; 
	}
	T dis2(const point<T> &p,bool is_segment=0)const{/*點跟直線/線段的距離平方*/ 
		point<T> v=p2-p1,v1=p-p1;
		if(is_segment){
			point<T> v2=p-p2;
			if(v.dot(v1)<=0)return v1.abs2();
			if(v.dot(v2)>=0)return v2.abs2();
		}
		T tmp=v.cross(v1);
		return tmp*tmp/v.abs2();
	}
	point<T> projection(const point<T> &p)const{//點對直線的投影
		point<T> n=(p2-p1).normal();
		return p-n*(p-p1).dot(n)/n.abs2();
	}
	point<T> mirror(const point<T> &p)const{/*點對直線的鏡射*/ 
		/*要先呼叫pton轉成一般式*/
		point<T> ans;
		T d=a*a+b*b;
		ans.x=(b*b*p.x-a*a*p.x-2*a*b*p.y-2*a*c)/d;
		ans.y=(a*a*p.y-b*b*p.y-2*a*b*p.x-2*b*c)/d;
		return ans;
	}
	bool equal(const line &l)const{/*直線相等*/ 
		return cross(l.p1)==0&&cross(l.p2)==0;
	}
	bool parallel(const line &l)const{/*直線平行*/ 
		return (p1-p2).cross(l.p1-l.p2)==0;
	}
	bool cross_seg(const line &l)const{/*直線是否交線段*/
		return (p2-p1).cross(l.p1)*(p2-p1).cross(l.p2)<=0;
	}
	char line_intersect(const line &l)const{/*直線相交情況，-1無限多點、1交於一點、0不相交*/ 
		return parallel(l)?(cross(l.p1)==0?-1:0):1;
	}
	char seg_intersect(const line &l)const{/*線段相交情況，-1無限多點、1交於一點、0不相交*/ 
		T c1=(p2-p1).cross(l.p1-p1);
		T c2=(p2-p1).cross(l.p2-p1);
		T c3=(l.p2-l.p1).cross(p1-l.p1);
		T c4=(l.p2-l.p1).cross(p2-l.p1);
		if(c1==0&&c2==0){
			if(p1==l.p1&&(p2-p1).dot(l.p2)<=0)return 1;
			if(p1==l.p2&&(p2-p1).dot(l.p1)<=0)return 1;
			if(p2==l.p1&&(p1-p2).dot(l.p2)<=0)return 1;
			if(p2==l.p2&&(p1-p2).dot(l.p1)<=0)return 1;
			return -1;
		}else if(c1*c2<=0&&c3*c4<=0)return 1;
		return 0;
	}
	point<T> line_intersection(const line &l)const{/*直線交點*/ 
		point<T> a=p2-p1,b=l.p2-l.p1,s=l.p1-p1;
		//if(a.cross(b)==0)return INF;
		return p1+a*s.cross(b)/a.cross(b);
	}
	point<T> seg_intersection(const line &l)const{/*線段交點*/ 
		T c1=(p2-p1).cross(l.p1-p1);
		T c2=(p2-p1).cross(l.p2-p1);
		T c3=(l.p2-l.p1).cross(p1-l.p1);
		T c4=(l.p2-l.p1).cross(p2-l.p1);
		if(c1==0&&c2==0){
			if(p1==l.p1&&(p2-p1).dot(l.p2)<=0)return p1;
			if(p1==l.p2&&(p2-p1).dot(l.p1)<=0)return p1;
			if(p2==l.p1&&(p1-p2).dot(l.p2)<=0)return p2;
			if(p2==l.p2&&(p1-p2).dot(l.p1)<=0)return p2;
		}else if(c1*c2<=0&&c3*c4<=0)return line_intersection(l);
		//return INF;
	}
};
template<typename T>
struct polygon{
	polygon(){}
	vector<point<T> > p;//逆時針順序 
	T area()const{/*多邊形面積*/ 
		T ans=0;
		for(int i=p.size()-1,j=0;j<(int)p.size();i=j++)
			ans+=p[i].cross(p[j]);
		return ans/2;
	}
	point<T> center_of_mass()const{/*多邊形重心*/
		T cx=0,cy=0,w=0;
		for(int i=p.size()-1,j=0;j<(int)p.size();i=j++){
			T a=p[i].cross(p[j]);
			cx+=(p[i].x+p[j].x)*a;
			cy+=(p[i].y+p[j].y)*a;
			w+=a;
		}
		return point<T>(cx/3/w,cy/3/w);
	}
	char ahas(const point<T>& t)const{/*點是否在簡單多邊形內，是的話回傳1、在邊上回傳-1、否則回傳0*/ 
		bool c=0;
		for(int i=0,j=p.size()-1;i<p.size();j=i++)
			if(line<T>(p[i],p[j]).point_on_segment(t))return -1;
			else if((p[i].y>t.y)!=(p[j].y>t.y)&&
			t.x<(p[j].x-p[i].x)*(t.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
				c=!c;
		return c;
	}
	char point_in_convex(const point<T>&x)const{
		int l=1,r=(int)p.size()-2;
		while(l<=r){/*點是否在凸多邊形內，是的話回傳1、在邊上回傳-1、否則回傳0*/
			int mid=(l+r)/2;
			T a1=(p[mid]-p[0]).cross(x-p[0]);
			T a2=(p[mid+1]-p[0]).cross(x-p[0]);
			if(a1>=0&&a2<=0){
				T res=(p[mid+1]-p[mid]).cross(x-p[mid]);
				return res>0?1:(res>=0?-1:0);
			}else if(a1<0)r=mid-1;
			else l=mid+1;
		}
		return 0;
	}
	polygon cut(const line<T> &l)const{/*凸包對直線切割，得到直線l左側的凸包*/
		polygon ans;
		for(int n=p.size(),i=n-1,j=0;j<n;i=j++){
			if(l.cross(p[i])>=0){
				ans.p.push_back(p[i]); 
				if(l.cross(p[j])<0)
					ans.p.push_back(l.line_intersection(line<T>(p[i],p[j])));
			}else if(l.cross(p[j])>0)
				ans.p.push_back(l.line_intersection(line<T>(p[i],p[j])));
		}
		return ans;
	}
	static bool graham_cmp(const point<T>& a,const point<T>& b){
		return (a.x<b.x)||(a.x==b.x&&a.y<b.y);/*凸包排序函數*/
	}
	void graham(vector<point<T> > &s){/*凸包*/
		sort(s.begin(),s.end(),graham_cmp);
		p.resize(s.size()+1);
		int m=0;
		for(int i=0;i<(int)s.size();++i){
			while(m>=2&&(p[m-1]-p[m-2]).cross(s[i]-p[m-2])<=0)--m;
			p[m++]=s[i];
		}
		for(int i=s.size()-2,t=m+1;i>=0;--i){
			while(m>=t&&(p[m-1]-p[m-2]).cross(s[i]-p[m-2])<=0)--m;
			p[m++]=s[i];
		}
		if(s.size()>1)--m; 
		p.resize(m);
	}
	inline static char sign(const point<T>&t){
		return (t.y==0?t.x:t.y)<0;
	}
	inline static bool angle_cmp(const line<T>& A,const line<T>& B){
		point<T> a=A.p2-A.p1,b=B.p2-B.p1;
		return sign(a)<sign(b)||(sign(a)==sign(b)&&a.cross(b)>0);
	}
	int halfplane_intersection(vector<line<T> > &s){//半平面交 
		sort(s.begin(),s.end(),angle_cmp);//線段左側為該線段半平面 
		int L,R,n=s.size();
		vector<point<T> > px(n);
		vector<line<T> > q(n);
		q[L=R=0]=s[0];
		for(int i=1;i<n;++i){
			while(L<R&&s[i].cross(px[R-1])<=0)--R;
			while(L<R&&s[i].cross(px[L])<=0)++L;
			q[++R]=s[i];
			if(q[R].parallel(q[R-1])){
				--R;
				if(q[R].cross(s[i].p1)>0)q[R]=s[i];
			}
			if(L<R)px[R-1]=q[R-1].line_intersection(q[R]);
		}
		while(L<R&&q[L].cross(px[R-1])<=0)--R;
		p.clear();
		if(R-L<=1)return 0;
		px[R]=q[R].line_intersection(q[L]);
		for(int i=L;i<=R;++i)p.push_back(px[i]);
		return R-L+1;
	}
};
template<typename T>
struct triangle{
	point<T> a,b,c;
	triangle(){}
	triangle(const point<T> &a,const point<T> &b,const point<T> &c):a(a),b(b),c(c){}
	T area()const{
		T t=(b-a).cross(c-a)/2;
		return t>0?t:-t;
	}
	point<T> barycenter()const{/*重心*/
		return (a+b+c)/3;
	}
	point<T> circumcenter()const{/*外心*/
		static line<T> u,v;
		u.p1=(a+b)/2; 
		u.p2=point<T>(u.p1.x-a.y+b.y,u.p1.y+a.x-b.x);
		v.p1=(a+c)/2;
		v.p2=point<T>(v.p1.x-a.y+c.y,v.p1.y+a.x-c.x);
		return u.line_intersection(v);
	}
	point<T> incenter()const{/*內心，用到根號*/
		T A=sqrt((b-c).abs2()),B=sqrt((a-c).abs2()),C=sqrt((a-b).abs2());
		return point<T>(A*a.x+B*b.x+C*c.x,A*a.y+B*b.y+C*c.y)/(A+B+C);
	}
	point<T> perpencenter()const{/*垂心*/
		return barycenter()*3-circumcenter()*2;
	}
};
template<typename T>
struct point3D{
	T x,y,z;
	point3D(){}
	point3D(const T&x,const T&y,const T&z):x(x),y(y),z(z){}
	point3D operator+(const point3D &b)const{
		return point3D(x+b.x,y+b.y,z+b.z);
	}
	point3D operator-(const point3D &b)const{
		return point3D(x-b.x,y-b.y,z-b.z);
	}
	point3D operator*(const T &b)const{
		return point3D(x*b,y*b,z*b);
	}
	point3D operator/(const T &b)const{
		return point3D(x/b,y/b,z/b);
	}
	bool operator==(const point3D &b)const{
		return x==b.x&&y==b.y&&z==b.z;
	}
	T dot(const point3D &b)const{
		return x*b.x+y*b.y+z*b.z;
	}
	point3D cross(const point3D &b)const{
		return point3D(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);
	}
	T abs2()const{/*向量長度的平方*/
		return dot(*this);
	}
	T area2(const point3D &b)const{//和b、原點圍成面積的平方 
		return cross(b).abs2()/4;
	}
};
template<typename T>
struct line3D{
	point3D<T> p1,p2;
	line3D(){}
	line3D(const point3D<T> &p1,const point3D<T> &p2):p1(p1),p2(p2){}
	T dis2(const point3D<T> &p,bool is_segment=0)const{/*點跟直線/線段的距離平方*/ 
		point3D<T> v=p2-p1,v1=p-p1;
		if(is_segment){
			point3D<T> v2=p-p2;
			if(v.dot(v1)<=0)return v1.abs2();
			if(v.dot(v2)>=0)return v2.abs2();
		}
		point3D<T> tmp=v.cross(v1);
		return tmp.abs2()/v.abs2();
	}
	pair<point3D<T>,point3D<T> > closest_pair(const line3D<T> &l)const{
		point3D<T> v1=(p1-p2),v2=(l.p1-l.p2);
		point3D<T> N=v1.cross(v2),ab(p1-l.p1);
		//if(N.abs2()==0)return NULL;平行或重合
		T tmp=N.dot(ab),ans=tmp*tmp/N.abs2();//最近點對距離
		point3D<T> d1=p2-p1,d2=l.p2-l.p1,D=d1.cross(d2);
		T t1=((l.p1-p1).cross(d2)).dot(D)/D.abs2();  
    	T t2=((l.p1-p1).cross(d1)).dot(D)/D.abs2();
    	return make_pair(p1+d1*t1,l.p1+d2*t2);
	}
	bool same_side(const point3D<T> &a,const point3D<T> &b)const{
		return (p2-p1).cross(a-p1).dot((p2-p1).cross(b-p1))>0;
	}
};
template<typename T>
struct plane{
	point3D<T> p0,n;//平面上的點和法向量 
	plane(){}
	plane(const point3D<T> &p0,const point3D<T> &n):p0(p0),n(n){}
	T dis2(const point3D<T> &p)const{//點到平面距離的平方 
		T tmp=(p-p0).dot(n);
		return tmp*tmp/n.abs2();
	}
	point3D<T> projection(const point3D<T> &p)const{
		return p-n*(p-p0).dot(n)/n.abs2();
	}
	point3D<T> line_intersection(const line3D<T> &l)const{
		T tmp=n.dot(l.p2-l.p1);//等於0表示平行或重合該平面 
		return l.p1+(l.p2-l.p1)*(n.dot(p0-l.p1)/tmp);
	}
	line3D<T> plane_intersection(const plane &pl)const{
		point3D<T> e=n.cross(pl.n),v=n.cross(e);
		T tmp=pl.n.dot(v);//等於0表示平行或重合該平面 
		point3D<T> q=p0+(v*(pl.n.dot(pl.p0-p0))/tmp);
		return line3D<T>(q,q+e);
	}
};
template<typename T>
struct triangle3D{
	point3D<T> a,b,c;
	triangle3D(){}
	triangle3D(const point3D<T> &a,const point3D<T> &b,const point3D<T> &c):a(a),b(b),c(c){}
	bool point_in(const point3D<T> &p)const{//點在該平面上的投影在三角形中 
		return line3D<T>(b,c).same_side(p,a)&&line3D<T>(a,c).same_side(p,b)&&line3D<T>(a,b).same_side(p,c);
	}
};
template<typename T>
struct tetrahedron{//四面體 
	point3D<T> a,b,c,d;
	tetrahedron(){}
	tetrahedron(const point3D<T> &a,const point3D<T> &b,const point3D<T> &c,const point3D<T> &d):a(a),b(b),c(c),d(d){}
	T volume6()const{//體積的六倍 
		return (d-a).dot((b-a).cross(c-a));
	}
	point3D<T> centroid()const{
		return (a+b+c+d)/4;
	}
	bool point_in(const point3D<T> &p)const{
		return triangle3D<T>(a,b,c).point_in(p)&&triangle3D<T>(c,d,a).point_in(p);
	}
};
template<typename T>
struct convexhull3D{
	static const int MAXN=105;
	struct face{
		int a,b,c;
		bool use;
		face(){}
		face(int a,int b,int c):a(a),b(b),c(c),use(1){}
	};
	vector<point3D<T> > pt;
	vector<face> fc;
	int fid[MAXN][MAXN];
	static bool point_cmp(const point3D<T> &a,const point3D<T> &b){
		return a.x<b.x||(a.x==b.x&&(a.y<b.y||(a.y==b.y&&a.z<b.z)));
	}
	bool outside(int p,int a,int b,int c)const{
		return tetrahedron<T>(pt[a],pt[b],pt[c],pt[p]).volume6()<0;
	}
	bool outside(int p,int f)const{return outside(p,fc[f].a,fc[f].b,fc[f].c);}
	void add_face(int a,int b,int c,int p){
		if(outside(p,a,b,c))fid[c][b]=fid[b][a]=fid[a][c]=fc.size(),fc.push_back(face(c,b,a));
		else fid[a][b]=fid[b][c]=fid[c][a]=fc.size(),fc.push_back(face(a,b,c));
	}
	bool dfs(int p,int f){
		if(!fc[f].use)return true;
		if(outside(p,f)){
			int a=fc[f].a,b=fc[f].b,c=fc[f].c;
			fc[f].use=false;
			if(!dfs(p,fid[b][a]))add_face(p,a,b,c);
			if(!dfs(p,fid[c][b]))add_face(p,b,c,a);
			if(!dfs(p,fid[a][c]))add_face(p,c,a,b);
			return true;
		}else return false;
	}
	void build(){
		bool ok=false;
		fc.clear();
		sort(pt.begin(),pt.end(),point_cmp);
		pt.resize(unique(pt.begin(),pt.end())-pt.begin());
		for(size_t i=2;i<pt.size();++i){
			if((pt[0]-pt[i]).area2(pt[1]-pt[i])!=0){
				ok=true;
				swap(pt[i],pt[2]);
				break;
			}
		}
		if(!ok)return;
		ok=false;
		for(size_t i=3;i<pt.size();++i){
			if(tetrahedron<T>(pt[0],pt[1],pt[2],pt[i]).volume6()!=0){
				ok=true;
				swap(pt[i],pt[3]);
				break;
			}
		}
		if(!ok)return;
		for(int i=0;i<4;++i)add_face(i,(i+1)%4,(i+2)%4,(i+3)%4);
		for(size_t i=4;i<pt.size();++i){
			for(int j=fc.size()-1;j>=0;--j){
				if(outside(i,j)){
					dfs(i,j);
					break;
				}
			}
		}
		size_t sz=0;
		for(size_t i=0;i<fc.size();++i)if(fc[i].use)fc[sz++]=fc[i];
		fc.resize(sz);
	}
	point3D<T> centroid()const{
		point3D<T> res(0,0,0);
		T vol=0;
		for(size_t i=0;i<fc.size();++i){
			T tmp=pt[fc[i].a].dot(pt[fc[i].b].cross(pt[fc[i].c]));
			res=res+(pt[fc[i].a]+pt[fc[i].b]+pt[fc[i].c])*tmp;
			vol+=tmp;
		}
		return res/(vol*4);
	}
};