//Dinic
const int INF = 0x5fffffff;
const int MAXN = 4e2+5;

struct adj_graph{
    int n;
    int adj[MAXN][MAXN];
    inline void update(int u,int v,int a){
        adj[u][v]+=a;
    }
    void initial()
    {
        SET0(adj);
    }
    adj_graph(){
        initial();
    }
    
    
    void debug()
    {
        static int dbnum=1;
        printf("dbnum:%d\n",dbnum++);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(adj[i][j])
                {
                    printf("%d-->%d  w:%d\n",i,j,adj[i][j]);
                }
            }
        }
    }
}g;


int level[MAXN];
bool get_level(int start,int terminal)
{
    SET0(level);
    queue<int> q;
    q.push(start);
    level[start]=1;
    
    while(q.size()) {
        int now=q.front();
        q.pop();
        for(int v=1;v<=g.n;v++)
        {
            if(g.adj[now][v]>0){
                if(!level[v]){
                    level[v]=level[now]+1;
                    if(v==terminal)
                        return true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int augment_cur_dfs(int now,int terminal,int low_cap)
{
    if(now==terminal){
        return low_cap;
    }
    for(int v=1;v<=g.n;v++)
    {
        if(g.adj[now][v]>0
         &&level[v]==level[now]+1)
        {
            int re=augment_cur_dfs(v,terminal,min(low_cap,g.adj[now][v]));
            
            if(re)
            {
                g.update(now,v,-re);
                g.update(v,now,re);
                return re;
            }
        }
    }
    return 0;
}

int dinic(int start,int terminal)
{
    int re=0;
    while (get_level(start,terminal)) {
//        g.debug();
        re+=augment_cur_dfs(start,terminal,INF);
    }
    return re;
}

//-------------------结构体版本-----------------

const int INF = 0x3f3f3f3f;
const int MAXN = 5e4+5;
const int MAXE = 2e6+5;
struct _edge{
    int u,v,nex;
    int cap;
};
struct adj_graph{
    _edge edges[MAXE];
    int head[MAXN];
    int edge_cnt;
    void initial()
    {
        edge_cnt=0;
        memset(head,-1,sizeof(head));
    }
    void add(int u,int v,int cap)
    {
        edges[edge_cnt].v=v;
        edges[edge_cnt].u=u;
        edges[edge_cnt].nex=head[u];
        edges[edge_cnt].cap=cap;
        head[u]=edge_cnt;
        edge_cnt++;
        
        edges[edge_cnt].v=u;
        edges[edge_cnt].u=v;
        edges[edge_cnt].nex=head[v];
        edges[edge_cnt].cap=0;
        head[v]=edge_cnt;
        edge_cnt++;
    }
    adj_graph(){initial();}
    void debug(int n)
    {
        for(int now=0;now<=n;now++)
        {
            for(int k=head[now];k!=-1;k=edges[k].nex)
            {
                int v=edges[k].v;
                printf("%d-->%d  %d\n",now,v,edges[k].cap);
            }
        }
    }
};

struct dinic{
    adj_graph g;
    int level[MAXN];
    bool get_level(int start,int terminal)
    {
        SET0(level);
        queue<int>q;
        q.push(start);
        level[start]=1;
        while(q.size()){
            int now=q.front();
            q.pop();
            
            for(int k=g.head[now];k!=-1;k=g.edges[k].nex){
                int v=g.edges[k].v;
                if(g.edges[k].cap>0&&!level[v]){
                    level[v]=level[now]+1;
                    if(v==terminal)
                        return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    int augment_cur_dfs(int now,int terminal,int max_flow)
    {
        if(now==terminal)
            return max_flow;
        int re=0;
        for(int k=g.head[now];k!=-1;k=g.edges[k].nex)
        {
            int v=g.edges[k].v;
            if(level[v]==level[now]+1)
            {
                int f=augment_cur_dfs(v,terminal,min(max_flow-re,g.edges[k].cap));
                g.edges[k].cap-=f;
                g.edges[k^1].cap+=f;
                re+=f;
                if(re==max_flow)return re;
            }
        }
        return re;
    }
    
    int solve(int start,int terminal){
        int maxflow=0;
        while(get_level(start,terminal)){
            maxflow+=augment_cur_dfs(start,terminal,INF);
        }
        return maxflow;
    }
}din;

