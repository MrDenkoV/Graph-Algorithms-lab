#include <bits/stdc++.h>
using namespace std;

struct trip{
    int min;
    int max;
    int to;
};

bool check(vector<vector<trip> >& V, vector<int>& path, vector<bool>& odw, int n, int ob, int lower, int upper){
    //printf("\t%d\n", ob);
    if(lower>upper)
        return false;
    if(ob==n+1){
        path[0]=lower;
        return true;
    }
    for(int i=0; i<V[ob].size(); i++){
        path[ob]=V[ob][i].to;
        if(odw[V[ob][i].to])
            continue;
        odw[V[ob][i].to]=true;
        if(check(V, path, odw, n, ob+1, max(lower, V[ob][i].min), min(upper, V[ob][i].max)))
            return true;
        odw[V[ob][i].to]=false;
    }
    return false;
}

void solve(vector<vector<trip> >& V, int n){
    vector<int> path;
    vector<bool> odw;
    path.resize(n+1);
    odw.resize(n+1, false);

    if(check(V, path, odw, n, 1, -1e9, 1e9)){
        printf("%d\n", path[0]);
        for(int i=1; i<path.size(); i++)
            printf("%d %d\n", i, path[i]);
    }
    else
        printf("-1\n");
}

int main() {
    int z;
    scanf("%d", &z);
    while(z--){
        int n, m;
        scanf("%d%d", &n, &m);
        vector<vector<trip> > V;
        V.resize(n+1);
        int from, to, min, max;
        trip tmp;
        for(int i=0; i<m; i++){
            scanf("%d%d%d%d", &from, &to, &min, &max);
            tmp.min = min;
            tmp.max = max;
            tmp. to = to;
            V[from].push_back(tmp);
        }

//        printf("?\n");
        solve(V, n);
        V.clear();
    }
    return 0;
}
