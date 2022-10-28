using PT=point<T>; using CPT=const PT;
PT circumcenter(CPT &a,CPT &b,CPT &c){
	PT u=b-a, v=c-a;
	T c1=u.abs2()/2,c2=v.abs2()/2;
	T d=u.cross(v);
	return PT(a.x+(v.y*c1-u.y*c2)/d,a.y+(u.x*c2-v.x*c1)/d);
}
void solve(PT p[],int n,PT &c,T &r2){
	random_shuffle(p,p+n);
	c=p[0]; r2=0; // c,r2 = 圓心,半徑平方
for(int i=1;i<n;i++)if((p[i]-c).abs2()>r2){
		c=p[i]; r2=0;
for(int j=0;j<i;j++)if((p[j]-c).abs2()>r2){
			c.x=(p[i].x+p[j].x)/2;
			c.y=(p[i].y+p[j].y)/2;
			r2=(p[j]-c).abs2();
for(int k=0;k<j;k++)if((p[k]-c).abs2()>r2){
				c=circumcenter(p[i],p[j],p[k]);
				r2=(p[i]-c).abs2();
			}
		}
	}
}