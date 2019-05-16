
int boy_num,girl_num;
bool adj[501][501];
bool used[501];
int pat[501];

bool is_match(int now)
{
    for(int i=1;i<=girl_num;i++)
    {
        if(adj[now][i]&&used[i]==0)
        {
            used[i]=1;
            if(pat[i]==0||is_match(pat[i])){
                pat[i]=now;
                return true;
            }
        }
    }
    return 0;
}
int hungarian()
{
    SET0(pat);
    int re=0;
    for(int i=1;i<=boy_num;i++)
    {
        SET0(used);
        re+=is_match(i);
    }
    return re;
}
//-------------------------------邻接表------------------------------------

struct _edge{
    int v,nex;
};
const int MAXE = 3e5+5;
struct adj_graph{
    _edge edges[MAXE];
    int head[MAXN];
    int edge_cnt;
    void initial()
    {
        edge_cnt=0;
        memset(head,-1,sizeof(head));
    }
    void add(int u,int v)
    {
        edges[edge_cnt].v=v;
        edges[edge_cnt].nex=head[u];
        head[u]=edge_cnt;
        edge_cnt++;
    }
    adj_graph(){initial();}
    void debug(int n)
    {
        for(int now=0;now<n;now++)
        {
            for(int k=head[now];k!=-1;k=edges[k].nex)
            {
                int v=edges[k].v;
                printf("%d-->%d\n",now,v);
            }
        }
    }
}g;
bool tried_match[MAXN];
int hus[MAXN];
bool is_match(int now)
{
    for(int k=g.head[now];k!=-1;k=g.edges[k].nex)
    {
        int v=g.edges[k].v;
        if(tried_match[v]==0)
        {
            tried_match[v]=1;
            if(hus[v]==-1||is_match(hus[v]))
            {
                hus[v]=now;
                return true;
            }
        }
    }
    return false;
}
bool isgirl[MAXN];
int hungarian(int n)
{
    SET_1(hus);
    int re=0;
    for(int i=0;i<n;i++)
    {
        if(!isgirl[i]){
            SET0(tried_match);
            re+=is_match(i);
        }
    }
    return re;
}
