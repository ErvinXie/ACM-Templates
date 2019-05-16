const int MAXN = 5e5+4;
#define Lp(x) (x/2-Len[x]/2)
#define Rp(x) (x/2+(Len[x]-1)/2-1)
char s[MAXN],ns[MAXN*2];
//s[i] == ns[i*2+2];
//nslen == slen*2+2;
char* get_ns(const char *s,char *ns)
{
    int l=strlen(s);
    ns[0]='$';
    for(int i=1;i<=l*2;i++)
    {
        ns[i++]='#';
        ns[i]=s[(i-1)/2];
    }
    ns[l*2+1]='#';
    ns[l*2+2]=0;
    return ns;
}

int Len[MAXN*2];
//Len[i] - 1 就是回文串长度

void manacher(const char *s){
    int i;
    int mx=0,id;
    get_ns(s,ns);
    int nslen=strlen(ns);
    memset(Len,0,sizeof(Len));
    
    for(i=1;i<nslen-1;i++){
        if(mx>i)
            Len[i]=min(Len[2*id-i],mx-i);  //2*id-i是i关于id的对称点
        else   //越过mx则暴力判断
            Len[i]=1;
        while(ns[i+Len[i]]==ns[i-Len[i]])  //回文匹配
            Len[i]++;
        if(Len[i]+i>mx){    //更新mx和id
            mx=Len[i]+i;
            id=i;
        }
    }
}
bool ispali(int L,int R)
{
    return Len[L+R+2]>=R-L+2 ? 1 : 0;
}


