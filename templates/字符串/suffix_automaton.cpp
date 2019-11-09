
const int CHARSET = 26;
const int MAXN = 1e6+5;
struct SAM{
    int par[MAXN*2];
    int go[MAXN*2][CHARSET];
    int maxl[MAXN*2];
    int getmin(int x){
        if(x==0)
            return 0;
        return maxl[par[x]]+1;
    }
    int epsize[MAXN*2];
    vector<int> topo;


    int root,last;
    int size = 0;
    int newnode(int x = 0){
        par[size]=-1;
        memset(go[size], -1, sizeof(go[size]));
        maxl[size]=x;
        epsize[size]=0;

        size++;
        return size -1;
    }

    void init(){
        size = 0;
        root = last = newnode();
    }

    void extend(int c){
        int p = last;
        int np = newnode(maxl[p]+1);
        epsize[np] = 1;//一定占用一个ep

        while(p!=-1&&go[p][c]==-1){
            go[p][c] = np;
            p = par[p];
        }

        if(p==-1){
            par[np] = root;//新点的minl = 1，直接连root
        }else{
            int x = go[p][c];
            if(maxl[x]==maxl[p]+1){
                par[np]=x;//无需分点
            }else{
                int nx = newnode(maxl[p]+1);
                memcpy(go[nx],go[x], sizeof(go[nx]));
                par[nx] = par[x];
                par[x] = par[np] = nx;
                while(p!=-1&&go[p][c]==x){
                    go[p][c] = nx;
                    p = par[p];
                }
            }
        }
        last = np;
    }

    int withdraw(int now,int len){
        while(par[now]!=-1&&maxl[par[now]]>=len)
            now = par[now];
        return now;
    }

    void toposort(){
        static int buf[MAXN+1];
        memset(buf,0, sizeof(buf));
        int maxmax=0;
        for(int i=0;i<size;i++){
            buf[maxl[i]]++;
            maxmax = max(maxmax,maxl[i]);
        }
        for(int i=1;i<=maxmax;i++){
            buf[i]=buf[i-1]+buf[i];
        }
        topo.resize(size);
        for(int i=0;i<size;i++){
            topo[--buf[maxl[i]]] = i;
        }
    }
    void getepsize(){
        toposort();
        for(int i=size-1;i>=0;i--){
            int p = topo[i];
            epsize[par[p]]+=epsize[p];
        }
    }
    void debug(){
        for(int i=0;i<size;i++){
            printf("id:%d par:%d max:%d min:%d endpos size:%d\n",i,par[i],maxl[i],getmin(i),epsize[i]);
            for(int j=0;j<CHARSET;j++){
                bool ne = false;
                if(go[i][j]!=-1){
                    ne = true;
                    printf("(-%c-> %d) ",j+'a',go[i][j]);
                }
                if(ne)
                    printf("\n");
            }
        }
    }
}sam;