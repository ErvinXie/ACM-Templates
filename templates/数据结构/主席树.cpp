const int MAXN = 1e5+4;
const int M = MAXN * 30;
int Root[MAXN],lson[M],rson[M],data[M];
int build(int l,int r)
{
    int root=tot++;
    data[root]=0;
    if(l!=r)
    {
        int mid=(l+r)>>1;
        lson[root]=build(l,mid);
        rson[root]=build(mid+1,r);
    }
    return root;
}

int update(int root,int pos,int val){
    int newroot = tot++,res=newroot;
    data[newroot]=data[root]+val;
    int l=1,r=Discrete_cnt;
    while (l<r) {
        int mid = (l+r)>>1;
        if(pos<=mid)
        {
            lson[newroot]=tot++;
            rson[newroot]=rson[root];
            newroot=lson[newroot];
            root=lson[root];
            r=mid;
        }
        else
        {
            rson[newroot]=tot++;
            lson[newroot]=lson[root];
            newroot=rson[newroot];
            root=rson[root];
            l=mid+1;
        }
        data[newroot]=data[root]+val;
    }
    return res;
}
