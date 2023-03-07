#include <bits/stdc++.h>

using namespace std;

bool DFS(vector<vector<int> >& V, vector<int>& S, vector<int>& odw, int ob){
    if(odw[ob]==0)
        return false;
    odw[ob]=0;
    for(int i=0; i<V[ob].size(); i++){
        if(odw[V[ob][i]]==-1 && S[V[ob][i]]==-1)
        {
            S[V[ob][i]]=ob;
            S[ob]=V[ob][i];
            return true;
        }
        if(odw[V[ob][i]]==-1 && DFS(V, S, odw, S[V[ob][i]]))
        {
            S[V[ob][i]]=ob;
            S[ob]=V[ob][i];
            return true;
        }
    }
    return false;
}

void solvebipart(vector<vector<int> >& V, vector<int>& S, vector<int>& odw, int n){
    bool f = true;
    while (f) {
        f = false;
        odw.resize(n, -1);
        for (int i = 0; i < n; i++) {
            if (S[i] == -1 && DFS(V, S, odw, i))
                f = true;
        }
        odw.clear();
    }

    int nr = 0;
    for (int i = 0; i < n; i++)
        if (S[i] != -1)
            nr++;

    cout << nr / 2 << endl;;
    for (int i = 0; i < n; i++)
        if (S[i] != -1 && S[i] > i)
            cout << i << ' ' << S[i] << endl;
}


int LCA(vector<int>& S, vector<int>& par, vector<int>& base, int root, int u, int v, int n)
{
    vector<bool> inp;
    inp.resize(n, false);
//    cout<<u<<' '<<v<<endl;
    while(true)
    {
//        cout<<u<<endl;
        u=base[u];
        inp[u]=true;
        if (u==root) break;
        u=par[S[u]];
    }
    while(true)
    {
        //cout<<'!'<<v<<' '<<endl;
        v=base[v];
        if (inp[v]) return v;
        else
            v=par[S[v]];
    }
}

void mark_blossom(vector<int>& S, vector<int>& par, vector<int>& base, vector<bool>& blos, int lca, int u)
{
    while (base[u]!=lca)
    {
        int v=S[u];
        blos[base[u]]=true;
        blos[base[v]]=true;
        u=par[v];
        if (base[u]!=lca) par[u]=v;
    }
}

void bloscontr(vector<int>& S, vector<int>& par, vector<int>& base, vector<bool>& odw, queue<int>& Q, int s, int u, int v, int n)
{
    int lca=LCA(S, par, base, s, u, v, n);
    vector<bool> blos;
    blos.resize(n, false);
    mark_blossom(S, par, base, blos, lca, u);
    mark_blossom(S, par, base, blos, lca, v);
    if (base[u]!=lca)
        par[u]=v;
    if (base[v]!=lca)
        par[v]=u;
    for (int i=0; i<n; i++)
        if (blos[base[i]]){
            base[i]=lca;
            if (!odw[i]){
                Q.push(i);
                odw[i]=true;
            }
        }
}

int augmentpath(vector<vector<int> >& V, vector<int>& S, vector<int>& par, int st, int n)
{
    vector<bool> odw;
    vector<int> base;
    odw.resize(n, false);
    par.resize(n, -1);
    for (int i=0; i<n; i++) base.push_back(i);
    queue<int> Q;
    Q.push(st);
    odw[st]=true;
    while (!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        for(int i=0; i<V[u].size(); i++){
            int v=V[u][i];
            if (base[u]!=base[v]&&S[u]!=v) {
                if ((v == st) || (S[v] != -1 && par[S[v]] != -1))
                    bloscontr(S, par, base, odw, Q, st, u, v, n);
                else if (par[v] == -1) {
                    par[v] = u;
                    if (S[v] == -1)
                        return v;
                    else if (!odw[S[v]]) {
                        Q.push(S[v]);
                        odw[S[v]]=true;
                    }
                }
            }
        }
    }
    return -1;
}

int find_path (vector<vector<int> >& V, vector<int>& S, vector<int>& par, int root, int n) {
    vector<bool> used;
    vector<int> base;
    used.resize(n, false);
    par.resize(n, -1);
//    memset (used, 0, sizeof used);
//    memset (p, -1, sizeof p);
    for (int i=0; i<n; ++i)
        base.push_back(i);
    vector<int> Q;
    Q.resize(2*n, 0);
    used[root] = true;
    int qh=0, qt=0;
    Q[qt++] = root;
    while (qh < qt) {
        int v = Q[qh++];
        for (size_t i=0; i<V[v].size(); ++i) {
            int to = V[v][i];
            if (base[v] == base[to] || S[v] == to)  continue;
            if (to == root || S[to] != -1 && par[S[to]] != -1) {
                int curbase = LCA (S, par, base, v, S[v], to, n);
                vector<bool> blos;
                blos.resize(n, 0);
                mark_blossom(S, par, base, blos, curbase, v);
                mark_blossom(S, par, base, blos, curbase, S[v]);
                for (int i=0; i<n; ++i)
                    if (blos[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) {
                            used[i] = true;
                            Q[qt++] = i;
                        }
                    }
            }
            else if (par[to] == -1) {
                par[to] = v;
                if (S[to] == -1)
                    return to;
                to = S[to];
                used[to] = true;
                Q[qt++] = to;
            }
        }
    }
    return -1;
}

void solveall(vector<vector<int> >& V, vector<int>& S, int n)
{
    vector<int> par;
    S.resize(n, -1);
    for (int i=0; i<n; i++)
        if (S[i]==-1) {
            int tmp=find_path(V, S, par, i, n);//augmentpath(V, S, par, i, n);
            int v, m;
            while(tmp!=-1){
                //cout<<'?'<<endl;
                v=par[tmp];
                m=S[v];
                S[v]=tmp;
                S[tmp]=v;
                tmp=m;
            }
        }


    int nr = 0;
    for (int i = 0; i < n; i++)
        if (S[i] != -1)
            nr++;

    cout << nr / 2 << endl;;
    for (int i = 0; i < n; i++)
        if (S[i] != -1 && S[i] > i)
            cout << i << ' ' << S[i] << endl;
}

int main() {
    string name;
    ios_base::sync_with_stdio(0);
    cin>>name;
    vector<vector<int> > V;
    vector<int> S, odw;
    int n, u;
    cin>>n;
    cin>>u;
    set<int> U;
    V.resize(n);
    S.resize(n, -1);

    for(int i=0; i<u; i++){
        int tmp;
        cin>>tmp;
        U.insert(tmp);
    }

    int m;
    cin>>m;
    bool bipart=true;
    for(int i=0; i<m; i++){
        int a, b;
        cin>>a>>b;
        if(U.find(a)!=U.end() && U.find(b)!=U.end()) {
            bipart = false;
        }
        V[a].push_back(b);
        V[b].push_back(a);
    }

    for(int i=0; i<n; i++) {
        if (S[i] == -1) {
            for (int j = 0; j < V[i].size(); j++)
                if (S[V[i][j]] == -1) {
                    S[V[i][j]]=i;
                    S[i]=V[i][j];
                    break;
                }
        }
    }

    if(bipart) {
        solvebipart(V,S,odw,n);
    }
    else{
//        return -1;
        solveall(V, S, n);
//        solvebipart(V,S,odw,n);
    }

    return 0;
}
