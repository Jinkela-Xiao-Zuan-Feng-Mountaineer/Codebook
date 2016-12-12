int whatday(int y,int m,int d){
    if(m<=2)m+=12,--y;
    if(y<1752||y==1752&&m<9||y==1752&&m==9&&d<3)
        return (d+2*m+3*(m+1)/5+y+y/4+5)%7;
    return (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
}