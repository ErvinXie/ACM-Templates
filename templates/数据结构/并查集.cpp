//  并查集
//  ⚠️查询时要用query(x)不能直接parent[x]⚠️

const int MAXN = 10005;
int parent[MAXN];
int query(int x)
{
    if(x!=parent[x]) return parent[x]=query(parent[x]);
    return parent[x];
}
void combine(int a,int b)
{
    parent[query(b)]=query(a);
}
void initial()
{
    for(int i=0;i<MAXN;i++)
        parent[i]=i;
}

