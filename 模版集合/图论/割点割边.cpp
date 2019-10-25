
#include <cstring>

struct _edge{
    int v,nex;
};
struct graph{
    _edge edges[MAXE];
    int head[MAXN];
    int edge_cnt;
    void initial()
    {
        edge_cnt=0;
        memset(head,0,sizeof(head));
        edge_cnt=0;
    }
    void add(int u,int v)
    {
        edge_cnt++;
        edges[edge_cnt].v=v;
        edges[edge_cnt].nex=head[u];
        head[u]=edge_cnt;
    }
}g;


int dfn[MAXN]={0};
int low[MAXN]={0};
int total_dfs=0;
int parent[MAXN]={0};

int is_av[MAXN]={0};
int av_cnt=0;

void articulation_dfs(int now)
{
    total_dfs++;
    dfn[now]=low[now]=total_dfs;
    int son_num=0;
    for(int k=g.head[now];k;k=g.edges[k].nex)
    {
        int v=g.edges[k].v;
        if(!dfn[v]){
            son_num++;
            parent[v]=now;
            
            articulation_dfs(v);
            if(parent[now]!=-1&&low[v]>=dfn[now]){
                is_av[now]=1;
                av_cnt++;
            }
            if(parent[now]==-1&&son_num>1){
                is_av[now]=1;
                av_cnt++;
            }
            low[now]=min(low[now],low[v]);
        }
        else if(v!=parent[now]){
            low[now]=min(low[now],dfn[v]);
        }
    }
}
void at_solve(int n)
{
    SET0(dfn);
    SET0(low);
    SET0(parent);
    SET0(is_av);
    total_dfs=0;
    av_cnt=0;
    
    parent[1]=-1;
    articulation_dfs(1);
}


bool vis[MAXN];
int at_belong[MAXN];
int p_size[MAXN];
int at_cnt;
void build_dfs(int now)
{
    vis[now]=1;
    at_belong[now]=at_cnt;
    p_size[at_cnt]++;
    for(int k=g.head[now];k;k=g.edges[k].nex){
        int v=g.edges[k].v;
        if(!vis[v]&&!is_av[v])
            build_dfs(v);
    }
}

set<int> inset[MAXN];
int outde[MAXN],inde[MAXN];
graph at_g;
void build_arti_graph(int n)
{
    at_g.initial();
    SET0(p_size);
    SET0(vis);
    SET0(at_belong);
    SET0(outde);
    SET0(inde);
    for(int i=1;i<=n;i++)
        inset[i].clear();
    at_cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            at_cnt++;
            if(!is_av[i]){
                build_dfs(i);
            }
            else{
                at_belong[i]=at_cnt;
                p_size[at_cnt]++;
            }
        }
    }
    
    for(int i=1;i<=n;i++){
        //        printf("%d %d\n",i,at_belong[i]);
        for(int k=g.head[i];k;k=g.edges[k].nex){
            int v=g.edges[k].v;
            if(at_belong[i]!=at_belong[v]&&!inset[at_belong[i]].count(at_belong[v])){
                at_g.add(at_belong[i],at_belong[v]);
                outde[at_belong[i]]++;
                inde[at_belong[v]]++;
                inset[at_belong[i]].insert(at_belong[v]);
            }
        }
    }
}
void test_at_graph()
{
    for(int i=1;i<=at_cnt;i++){
        printf("%d->(no:%d size:%d)->%d:",inde[i],i,p_size[i],outde[i]);
        for(int k=at_g.head[i];k;k=at_g.edges[k].nex)
        {
            printf(" %d",at_g.edges[k].v);
        }
        printf("\n");
    }
}

