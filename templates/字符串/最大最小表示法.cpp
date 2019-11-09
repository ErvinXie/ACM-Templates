int min_max_expression(const char *s,int slen,bool is_min)
{
    int k=0,p[2]={0,1};
    while(p[0]<slen&&p[1]<slen&&k<slen) {
        int t=s[(p[0]+k)%slen]-s[(p[1]+k)%slen];
        if(t==0)
            k++;
        else{
            if(t>0)
                p[1-is_min]+=k+1;
            else
                p[0+is_min]+=k+1;
            
            if(p[0]==p[1])
                p[1]++;
            k=0;
        }
    }
    return min(p[0],p[1]);
}
