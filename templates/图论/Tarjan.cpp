//Tarjan
#include <cstring>
#include<stack>
const int MAXN = 5e5+5;
const int MAXE = 5e5+5;
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
stack<int> st;
bool inst[MAXN]={0};
int belong[MAXN]={0};
int taj_cnt=0;
int total=0;

void tarjan_dfs(int x)
{
    total++;
    dfn[x]=total;
    low[x]=total;
    inst[x]=1;
    st.push(x);
    
    for(int k=g.head[x];k;k=g.edges[k].nex)
    {
        int v=g.edges[k].v;
        if(dfn[v]==0)
        {
            tarjan_dfs(v);
            low[x]=min(low[x],low[v]);
        }
        else if(inst[v])
        {
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(low[x]==dfn[x])
    {
        int u;
        ++taj_cnt;
        while(1)
        {
            u=st.top();
            st.pop();
            inst[u]=0;
            belong[u]=taj_cnt;
            
            //            cout<<u<<" ";
            if(u==x)
                break;
        }
        //        cout<<endl;
    }
}
void tarjan(int n)
{
    total=0;taj_cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(inst,0,sizeof(inst));
    memset(low,0,sizeof(low));
    while(!st.empty()) st.pop();
    for(int i=1;i<=n;i++)
        if(dfn[i]==0)tarjan_dfs(i);
}

graph ta;
set<int> inset[MAXN];
void build_taj_graph(int n)
{
    ta.initial();
    for(int i=1;i<=n;i++)
    {
        for(int k=g.head[i];k;k=g.edges[k].nex)
        {
            int v=g.edges[k].v;
            if(belong[i]!=belong[v]&&!inset[i].count(v))
            {
                ta.add(belong[i],belong[v]);
                inset[belong[i]].insert(belong[v]);
            }
        }
    }
}


int outde[MAXN],inde[MAXN];
graph ta;
set<int> inset[MAXN];
void build_taj_graph(int n)
{
    memset(outde,0,sizeof(outde));
    memset(inde,0,sizeof(inde));
    for(int i=1;i<=taj_cnt;i++)
        inset[i].clear();
    
    ta.initial();
    
    
    for(int i=1;i<=n;i++)
    {
        for(int k=g.head[i];k;k=g.edges[k].nex)
        {
            int v=g.edges[k].v;
            if(belong[i]!=belong[v]&&!inset[belong[i]].count(belong[v]))
            {
                ta.add(belong[i],belong[v]);
                outde[belong[i]]++;
                inde[belong[v]]++;
                
                inset[belong[i]].insert(belong[v]);
            }
        }
    }
}
void test_taj_graph()
{
    for(int i=1;i<=taj_cnt;i++){
        printf("%d->(no:%d size:%d)->%d:",inde[i],i,p_size[i],outde[i]);
        for(int k=ta.head[i];k;k=ta.edges[k].nex)
        {
            printf(" %d",ta.edges[k].v);
        }
        printf("\n");
    }
}
