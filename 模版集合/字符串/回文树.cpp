const int MAXN = 1e5+4;

const int N = 26 ;

struct Palindromic_Tree {
    int next[MAXN][N] ;//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[MAXN] ;//fail指针，失配后跳转到fail指针指向的节点
    int cnt[MAXN] ; //表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
    int num[MAXN] ; //表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
    int len[MAXN] ;//len[i]表示节点i表示的回文串的长度（一个节点表示一个回文串）
    int S[MAXN] ;//存放添加的字符
    int last ;//指向新添加一个字母后所形成的最长回文串表示的节点。
    int n ;//表示添加的字符个数。
    int p ;//表示添加的节点个数。
    
    int newnode ( int l ) {//新建节点
        for ( int i = 0 ; i < N ; ++ i ) next[p][i] = 0 ;
        cnt[p] = 0 ;
        num[p] = 0 ;
        len[p] = l ;
        return p ++ ;
    }
    
    void init () {//初始化
        p = 0 ;
        newnode (  0 ) ;
        newnode ( -1 ) ;
        last = 0 ;
        n = 0 ;
        S[n] = -1 ;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1 ;
    }
    
    int get_fail ( int x ) {//和KMP一样，失配后找一个尽量最长的
        while ( S[n - len[x] - 1] != S[n] ) x = fail[x] ;
        return x ;
    }
    
    void add ( int c ) {
        c -= 'a' ;
        S[++ n] = c ;
        int cur = get_fail ( last ) ;//通过上一个回文串找这个回文串的匹配位置
        if ( !next[cur][c] ) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode ( len[cur] + 2 ) ;//新建节点
            fail[now] = next[get_fail ( fail[cur] )][c] ;//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now ;
            num[now] = num[fail[now]] + 1 ;
        }
        last = next[cur][c] ;
        cnt[last] ++ ;
    }
    
    void count () {
        for ( int i = p - 1 ; i >= 0 ; -- i ) cnt[fail[i]] += cnt[i] ;
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
} pt;

//双向回文树
const int CHARSET_SIZE = 26;
struct PAM {
    int ch[MAXN * 2], pos[2];
    int node_cnt, last[2];
    int nxt[MAXN][CHARSET_SIZE];
    int len[MAXN];
    int fail[MAXN];

    void init() {
        pos[0] = MAXN;
        pos[1] = MAXN - 1;
        ch[MAXN - 1] = ch[MAXN] = -1;
        node_cnt = 1;
        len[0] = 0;
        len[1] = -1;
        fail[0] = 1;
        last[0] = last[1] = 0;
        SET0(nxt);
    }

    int getFail(int u, int d) {
        if (d)
            for (; ch[pos[1] - len[u] - 1] != ch[pos[1]]; u = fail[u]);
        else
            for (; ch[pos[0] + len[u] + 1] != ch[pos[0]]; u = fail[u]);
        return u;
    }

    void insert(int c, int d) {
        if (!d) {
            ch[--pos[0]] = c;
            ch[pos[0] - 1] = -1;
        } else {
            ch[++pos[1]] = c;
            ch[pos[1] + 1] = -1;
        }
        int u = getFail(last[d], d);
        if (!nxt[u][c]) {
            int v = ++node_cnt;
            len[v] = len[u] + 2;
            fail[v] = nxt[getFail(fail[u], d)][c];
            nxt[u][c] = v;
        }
        u = nxt[u][c];
        last[d] = u;
        if (len[u] == pos[1] - pos[0] + 1)
            last[d ^ 1] = u;
    }

    void debug() {
        printf("0\n");
        dfs(0, 0);
        printf("1\n");
        dfs(1, 0);
        printf("size:%d\n", node_cnt - 1);
    }

    void dfs(int now, int dep) {
        for (int i = 0; i < 26; i++) {
            int nxtnow = nxt[now][i];
            if (nxtnow != 0) {
                for (int j = 0; j < dep; j++) {
                    printf(" ");
                }
                printf("%c\n", i + 'a');
                dfs(nxtnow, dep + 1);
            }
        }
    }
}

//双向可持久化回文树
const int CHARSET_SIZE = 26;

struct PAM {
    int ch[MAXN * 2], pos[2];
    int node_cnt, last[MAXN][2];
    int nxt[MAXN][CHARSET_SIZE];
    int len[MAXN];
    int fail[MAXN];

    //可持久化
    int n;//版本
    int cc[MAXN];//第i个版本插入的字符
    int u[MAXN];//第i个版本的父亲
    int b[MAXN];//第i个版本插入的方向

    inline void init() {
        n = 0;
        SET_1(cc);

        pos[0] = MAXN;
        pos[1] = MAXN - 1;
        ch[MAXN - 1] = ch[MAXN] = -1;
        node_cnt = 1;
        len[0] = 0;
        len[1] = -1;

        fail[0] = 1;
        last[0][0] = last[0][1] = 0;
        SET0(nxt);

    }

    inline int getFail(int u, int d) {
        if (d)
            for (; ch[pos[1] - len[u] - 1] != ch[pos[1]]; u = fail[u]) {
                assert(u != fail[u]);
            }
        else
            for (; ch[pos[0] + len[u] + 1] != ch[pos[0]]; u = fail[u]) {
                assert(u != fail[u]);
            }
        return u;
    }

    inline void back() {
        if (!b[n]) {
            ch[pos[0]] = -1;
            ++pos[0];
        } else {
            ch[pos[1]] = -1;
            --pos[1];
        }

        if (cc[n] != -1) {
            nxt[u[n]][cc[n]] = 0;
            u[n] = 0;
            fail[node_cnt]=0;
            cc[n]=-1;
            node_cnt--;
        }
        n--;
    }


    inline void insert(int c, int d) {
        n++;
        b[n] = d;
        if (!d) {
            pos[0]--;
            ch[pos[0]] = c;
            ch[pos[0] - 1] = -1;
        } else {
            pos[1]++;
            ch[pos[1]] = c;
            ch[pos[1] + 1] = -1;
        }
        u[n] = getFail(last[n - 1][d], d);
        if (!nxt[u[n]][c]) {
            cc[n] = c;
            int v = ++node_cnt;

            len[v] = len[u[n]] + 2;
            fail[v] = nxt[getFail(fail[u[n]], d)][c];

            nxt[u[n]][c] = v;
        }
        int uu = nxt[u[n]][c];
        last[n][d] = uu;
        if (len[uu] == pos[1] - pos[0] + 1)
            last[n][d ^ 1] = uu;
        else
            last[n][d ^ 1] = last[n - 1][d ^ 1];

    }

    void debug() {
        printf("---------------\n");
        printf("0\n");
        dfs(0, 0);
        printf("1\n");
        dfs(1, 0);
        printf("version:%d last[%d][0]:%d last[%d][1]:%d\n", n, n, last[n][0], n, last[n][1]);
        printf("pos[%d][0]:%d pos[%d][1]:%d\n", n - 1, pos[0], n - 1, pos[1]);

        printf("size:%d\n", node_cnt - 1);
        printf("---------------\n");
    }

    void dfs(int now, int dep) {
        printf("fail[%d]=%d len[%d]=%d\n", now, fail[now], now, len[now]);
        for (int i = 0; i < 26; i++) {
            int nxtnow = nxt[now][i];
            if (nxtnow != 0) {
                for (int j = 0; j < dep + 1; j++) {
                    printf("-");
                }
                printf("%c\n", i + 'a');
                dfs(nxtnow, dep + 1);
            }
        }

    }
}  PM;