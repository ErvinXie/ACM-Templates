const int MAXN = 5e4+4;
char s[MAXN],t[MAXN];
int nex[MAXN];
//kmp 匹配
void get_nex(const char *pat,int next[])
{
    int p,patlen=strlen(pat);
    next[0]=-1;
    for(int i=1;i<patlen;i++)
    {
        p=next[i-1];
        while (p!=-1&&pat[p+1]!=pat[i])
            p=next[p];
        if(p==-1)
            next[i]=pat[0]==pat[i]?0:-1;
        else
            next[i]=p+1;
    }
}

vector<int> ans;
void KMP_match(char *s,char *t)
{
    get_nex(t,nex);
    int ps=0,pt=0,tlen=strlen(t);
    while(s[ps]) {
        if(s[ps]==t[pt]){
            ps++;pt++;
        }
        else{
            if(pt==0)
                ps++;
            else
                pt=nex[pt-1]+1;
        }
        if(pt==tlen){
            ans.push_back(ps);
            pt=0;
        }
    }
}

//拓展KMP
void ext_get_next(const char* pat,int next[])
{
    int patlen=strlen(pat);
    int a,p;
    next[0]=patlen;
    for(int i=1,j=-1;i<patlen;i++,j--)
    {
        if(j<0||i+next[i-a]>=p){
            if(j<0){
                p=i;
                j=0;
            }
            while (p<patlen&&pat[p]==pat[j]) {
                p++;
                j++;
            }
            next[i]=j;
            a=i;
        }
        else
            next[i]=next[i-a];
    }
}
