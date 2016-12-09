const double EPS=1e-9;
struct Double{
	double d;
	Double(double d=0):d(d){}
	bool operator <(const Double &b)const{return d-b.d<-EPS;}
	bool operator >(const Double &b)const{return d-b.d>EPS;}
	bool operator ==(const Double &b)const{return fabs(d-b.d)<=EPS;}
	bool operator !=(const Double &b)const{return fabs(d-b.d)>EPS;}
	bool operator <=(const Double &b)const{return d-b.d<=EPS;}
	bool operator >=(const Double &b)const{return d-b.d>=-EPS;}
	operator double()const{return d;}
};
