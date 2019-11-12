//广义后缀自动机，每次添加的时候从root开始重新添加设为
const int CHARSET = 26;
const int MAXN = 2e5 + 5;
const int STRING_NUM = 2;
const int MAX_SIZE = MAXN*STRING_NUM*2;
struct GSAM {
    int par[MAX_SIZE];
    int go[MAX_SIZE][CHARSET];
    int maxl[MAX_SIZE];

    int epsize[MAX_SIZE][STRING_NUM];

    int getmin(int x) {
        if (x == 0)
            return 0;
        return maxl[par[x]] + 1;
    }
    vector<int> topo;

    int root;
    int size;

    int newnode(int x = 0) {
        par[size] = -1;
        memset(go[size], -1, sizeof(go[size]));
        maxl[size] = x;
        memset(epsize[size],0, sizeof(epsize[size]));

        size++;
        return size - 1;
    }

    void init() {
        size = 0;
        root = newnode();
    }

    int extend(int f, int c,int which) {
        if (go[f][c] != -1 && maxl[go[f][c]] == maxl[f] + 1) {
            epsize[go[f][c]][which] = 1;
            return go[f][c];//有了就不用extend了
        }
        int p = f;
        int np = newnode(maxl[p] + 1);

        while (p != -1 && go[p][c] == -1) {
            go[p][c] = np;
            p = par[p];
        }

        if (p == -1) {
            par[np] = root;//新点的minl = 1，直接连root
            epsize[np][which]=1;
            return np;
        } else {
            int x = go[p][c];
            if (maxl[x] == maxl[p] + 1) {
                par[np] = x;//无需分点
                epsize[np][which]=1;
                return np;
            } else {
                bool flag = false;
                int nx = newnode(maxl[p] + 1);
                if (maxl[np] == maxl[p] + 1) {
                    flag = true;//神奇特判，会扔掉np，以后不回再用到（我猜的）
                }
                memcpy(go[nx], go[x], sizeof(go[nx]));
                par[nx] = par[x];
                par[x] = par[np] = nx;
                while (p != -1 && go[p][c] == x) {
                    go[p][c] = nx;
                    p = par[p];
                }
                epsize[flag ? nx : np][which]=1;
                return flag ? nx : np;
            }
        }
    }

    int withdraw(int now, int len) {
        while (par[now] != -1 && maxl[par[now]] >= len)
            now = par[now];
        return now;
    }

    void toposort(){//按 maxl 从小到大计数排序
        static int buf[MAXN + 1];
        memset(buf, 0, sizeof(buf));
        int maxmax = 0;
        for (int i = 0; i < size; i++) {
            buf[maxl[i]]++;
            maxmax = max(maxmax, maxl[i]);
        }
        for (int i = 1; i <= maxmax; i++) {
            buf[i] = buf[i - 1] + buf[i];
        }
        topo.resize(size);
        for (int i = 0; i < size; i++) {
            topo[--buf[maxl[i]]] = i;
        }
    }

    void getepsize(){
        toposort();

        for (int i = size - 1; i >= 0; i--) {
            int p = topo[i];
            for(int j=0;j<STRING_NUM;j++) {
                epsize[par[p]][j] += epsize[p][j];
            }
        }
    }



    void debug() {
        printf("-------------------------------------\n");
        for (int i = 0; i < size; i++) {
            printf("id:%d par:%d max:%d min:%d ", i, par[i], maxl[i], getmin(i));
            for(int j=0;j<STRING_NUM;j++){
                printf("epsize[%d]:%d ",j,epsize[i][j]);
            }
            printf("\n");
            for (int j = 0; j < CHARSET; j++) {
                bool ne = false;
                if (go[i][j] != -1) {
                    ne = true;
                    printf("(--%c-> %d) \n", j + 'a', go[i][j]);
                }
            }
        }
        for (int i = 0; i < size; i++) {
            printf("%d\n", i);
        }
        for (int i = 0; i < size; i++) {
            printf("%d %d *\n", i, par[i]);
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < CHARSET; j++) {
                bool ne = false;
                if (go[i][j] != -1) {
                    printf("%d %d %c\n", i, go[i][j], j + 'a');
                }
            }
        }
        printf("-------------------------------------\n");
    }
} sam;