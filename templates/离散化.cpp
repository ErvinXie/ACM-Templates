
int Discrete_cnt;
int Discrete[MAXN];
void Discrete_initial(int a[],int n)
{
    for(int i=1;i<=n;i++)
        Discrete[i]=a[i];
    sort(Discrete+1,Discrete+1+n);
    Discrete_cnt = unique(Discrete+1,Discrete+1+n)-Discrete-1;
}
int get_Discrete(int x)
{
    return lower_bound(Discrete+1,Discrete+1+Discrete_cnt,x)-Discrete;
}

