#include <cstring>
const int MAXN = 1e5+5;
bool is_prime[MAXN+1];
int prime[MAXN],prime_cnt=0;
//欧拉筛 O(n) prime[0]=2;
void e_getlist()
{
    memset(is_prime,1,sizeof(is_prime));
    is_prime[1]=0;
    for(int i=2;i<=MAXN;i++)
    {
        if(is_prime[i])
        {
            prime[prime_cnt++]=i;
        }
        for(int j=0;j<prime_cnt&&i*prime[j]<=MAXN;j++)
        {
            is_prime[i*prime[j]]=0;
            if(i%prime[j]==0)break;
        }
    }
}
//O(logn)求欧拉函数
int get_phi_logn(int n)
{
//    e_getlist();
    
    for(int i=0;prime[i]<=n;i++)
        if(n%prime[i]==0){
            n=n/prime[i]*(prime[i]-1);
        }
    return n;
}

//埃拉托尼斯特尼筛 O(n*loglogn)
void a_getlist()
{
    memset(is_prime,1,sizeof(is_prime));
    is_prime[1]=0;
    for(int i=2;i<=MAXN;i++)
    {
        if(is_prime[i])
            for(int j=i+i;j<=MAXN;j+=i)
                is_prime[j]=0;
    }
}

//O(n^(1/2))求欧拉函数
int get_phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans = ans/n*(n-1);
    return ans;
}



int P;
int qp(int a,int x)
{
    if(x==1)
        return a%P;
    else if(x==0)
        return 1;
    else{
        int re=1;
        if(x%2)
            re=a;
        int y=qp(a,x/2);
        return y*y%P*re%P;
    }
}
