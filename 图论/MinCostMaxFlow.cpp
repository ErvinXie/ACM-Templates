//-----------------------这个板子身经百战---------------------

const int INF = 0x3f3f3f3f;
const int MAXN = 2e4;
const int MAXE = 2e5+5;
struct _edge{
    int u,v,nex;
    int cap,cost;
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
    void add(int u,int v,int cap,int cost)
    {
        edges[edge_cnt].v=v;
        edges[edge_cnt].u=u;
        edges[edge_cnt].nex=head[u];
        edges[edge_cnt].cap=cap;
        edges[edge_cnt].cost=cost;
        head[u]=edge_cnt;
        edge_cnt++;
        
        edges[edge_cnt].v=u;
        edges[edge_cnt].u=v;
        edges[edge_cnt].nex=head[v];
        edges[edge_cnt].cap=0;
        edges[edge_cnt].cost=-cost;
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
                printf("%d-->%d  %d %d\n",now,v,edges[k].cap,edges[k].cost);
            }
        }
    }
};
struct min_cost_max_flow{
    adj_graph g;
    int dis[MAXN];
    int pre[MAXN];
    bool inq[MAXN];
    queue<int> q;
    bool spfa(int start,int terminal)
    {
        while (q.size())
            q.pop();
        for(int i=0;i<MAXN;i++)
            dis[i]=INF;
        SET_1(pre);
        SET0(inq);
        
        q.push(start);
        inq[start]=1;
        dis[start]=0;
        while (q.size()) {
            int u=q.front();
            q.pop();
            inq[u]=0;
            for(int k=g.head[u];k!=-1;k=g.edges[k].nex)
            {
                int v=g.edges[k].v;
                if(g.edges[k].cap&&dis[u]+g.edges[k].cost<dis[v])
                {
                    dis[v]=dis[u]+g.edges[k].cost;
                    pre[v]=k;
                    if(!inq[v])
                    {
                        q.push(v);
                        inq[v]=1;
                    }
                }
            }
        }
        return dis[terminal]<INF;
    }
    int solve(int start,int terminal,int &maxflow)
    {
        //            static int no=0;
        int mincost=0;
        maxflow=0;
        while (spfa(start,terminal)) {
            
            //                printf("no:%d",no++);
            int flow=INF;
            for(int k=pre[terminal];k!=-1;k=pre[g.edges[k].u])
                flow=min(flow,g.edges[k].cap);
            for(int k=pre[terminal];k!=-1;k=pre[g.edges[k].u])
            {
                g.edges[k].cap -= flow;
                g.edges[k^1].cap += flow;
                mincost += g.edges[k].cost * flow;
            }
            maxflow+=flow;
            
            //            printf(" %d %d\n",mincost,maxflow);
        }
        return mincost;
    }
}mcmf;
