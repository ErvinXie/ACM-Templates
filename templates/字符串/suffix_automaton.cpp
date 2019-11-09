#include <bits/stdc++.h>
using namespace std;

const int CHARSET = 26;
struct SAM_MIN {

    struct State {
        State *par, *go[CHARSET];
        int maxl;
        int minl(){
            return par->maxl+1;
        }
        State(int maxl = 0) : par(nullptr), maxl(maxl) {
            memset(go, 0, sizeof(go));
        }
    };

    State *root, *last;

    void init(){
        root = new State();
        last = root;
    }

    void extend(int w) {
        State *p = last;

        State *np = new State(p->maxl + 1);//next last node

        while (p && p->go[w] == nullptr) {
            p->go[w] = np;
            p = p->par;
        }
        if (p == nullptr) {
            np->par = root;
        } else {
            State *x = p->go[w];
            if (p->maxl + 1 == x->maxl) {
                np->par = x;
            } else {
                State *nx = new State(p->maxl + 1);
                memcpy(nx->go, x->go, sizeof(x->go));
                nx->par = x->par;
                x->par = nx;
                np->par = nx;
                while (p && p->go[w] == x) {
                    p->go[w] = nx;
                    p = p->par;
                }
            }
        }
        last = np;
    }
}sam;

int longest_common_substring(char a[],char b[]){
    sam.init();
    int alen = strlen(a),blen = strlen(b);
    for(int i=0;i<alen;i++){
        sam.extend(a[i]-'a');
    }
    int ans=0;

    auto now = sam.root;
    int len = 0;
    for(int i=0;i<blen;i++){
        if(now->go[b[i]-'a']){
            now = now->go[b[i]-'a'];
            len++;
            ans = max(len,ans);
        }else{
            // find the parent node, throw away some of the prefix
            while(now!=sam.root){
                now=now->par;
                len = now->maxl;
            }
        }
    }
    return ans;
}