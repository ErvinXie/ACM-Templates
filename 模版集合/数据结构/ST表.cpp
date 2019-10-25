//  ST表

#include <iostream>
#include <algorithm>
#include <cmath>

#define MAXN 400000
using namespace std;
int st[MAXN][20] = {0};
int data[MAXN] = {0};
int lg2[MAXN] = {0};

void initial(int *value, int n) {
    for (int i = 1; i <= n; i++) {
        st[i][0] = value[i];
        lg2[i] = log2(i);
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}

int query(int L, int R) {
    int k = lg2[R - L + 1];
    return max(st[L][k], st[R - (1 << k) + 1][k]);
}

int main(int argc, const char *argv[]) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> data[i];
    }
    initial(data, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= lg2[n]; j++) {
            cout << st[i][j] << " ";
        }
        cout << endl;
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int L, R;
        cin >> L >> R;
        cout << query(L, R) << endl;
    }
    return 0;
}

