#include"Geometry.cpp"
#include<vector>
struct Circle{
    typedef point<double> p;
    typedef const point<double> cp;
    p x;
    double r2;
    bool incircle(cp &c)const{return (x-c).abs2()<=r2;}
};

Circle TwoPointCircle(Circle::cp &a, Circle::cp &b) {
    Circle::p m=(a+b)/2;
    return (Circle){m,(a-m).abs2()};
}

Circle outcircle(Circle::p a, Circle::p b, Circle::p c) {
    if(TwoPointCircle(a,b).incircle(c)) return TwoPointCircle(a,b);
    if(TwoPointCircle(b,c).incircle(a)) return TwoPointCircle(b,c);
    if(TwoPointCircle(c,a).incircle(b)) return TwoPointCircle(c,a);
    Circle::p ret;
    double a1=b.x-a.x, b1=b.y-a.y, c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x, b2=c.y-a.y, c2=(a2*a2+b2*b2)/2;
    double d = a1*b2 - a2*b1;
    ret.x=a.x+(c1*b2-c2*b1)/d;
    ret.y=a.y+(a1*c2-a2*c1)/d;
    return (Circle){ret,(ret-a).abs2()};
}
//rand required
Circle SmallestCircle(std::vector<Circle::p> &p){
    int n=p.size();
    if(n==1) return (Circle){p[0],0.0};
    if(n==2) return TwoPointCircle(p[0],p[1]);
    random_shuffle(p.begin(),p.end());
    Circle c = {p[0],0.0};
    for(int i=0;i<n;++i){
        if(c.incircle(p[i])) continue;
        c=Circle{p[i],0.0};
        for(int j=0;j<i;++j){
            if(c.incircle(p[j])) continue;
            c=TwoPointCircle(p[i],p[j]);
            for(int k=0;k<j;++k){
                if(c.incircle(p[k])) continue;
                c=outcircle(p[i],p[j],p[k]);
            }
        }
    }
    return c;
}
