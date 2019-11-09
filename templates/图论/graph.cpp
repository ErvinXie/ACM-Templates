const int MAXN = 1e5+4;
const int MAXE = 2e5+4;
struct graph {
    int head[MAXN];
    int cnt=0;
    struct edge {
        int v,nex;
        int w;
    }edges[MAXE];
    void initial(){
        SET_1(head);
        cnt=0;
    }
    graph(){initial();}
    
    void add(int u,int v,int w){
        edges[cnt].v=v;
        edges[cnt].w=w;
        edges[cnt].nex=head[u];
        head[u]=cnt;
        cnt++;
    }
    
    void debug(int n){
        for(int i=1;i<=n;i++){
            for(int k=head[i];k!=-1;k=edges[k].nex){
                int v=edges[k].v;
                int w=edges[k].w;
                printf("%d -> %d with %d\n",i,v,w);
            }
        }
    }

    void debuge(){
        for(int i=0;i<cnt;i++){
            printf("x -> %d with %d\n",edges[i].v,edges[i].w);
        }
    }
}g;