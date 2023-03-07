//#include <bits/stdc++.h>
//
//using namespace std;
//
//bool DFS(vector<vector<int> >& V, vector<int>& S, vector<int>& odw, int ob){
//    if(odw[ob]==0)
//        return false;
//    odw[ob]=0;
//    for(int i=0; i<V[ob].size(); i++){
//        if(odw[V[ob][i]]==-1 && S[V[ob][i]]==-1)
//        {
//            S[V[ob][i]]=ob;
//            S[ob]=V[ob][i];
//            return true;
//        }
//        if(odw[V[ob][i]]==-1 && DFS(V, S, odw, S[V[ob][i]]))
//        {
//            S[V[ob][i]]=ob;
//            S[ob]=V[ob][i];
//            return true;
//        }
//    }
//    return false;
//}
//
//void solvebipart(vector<vector<int> >& V, vector<int>& S, vector<int>& odw, int n){
//    bool f = true;
//    while (f) {
//        f = false;
//        odw.resize(n + 1, -1);
//        for (int i = 0; i < n; i++) {
//            if (S[i] == -1 && DFS(V, S, odw, i))
//                f = true;
//        }
//        odw.clear();
//    }
//
//    int nr = 0;
//    for (int i = 0; i < n; i++)
//        if (S[i] != -1)
//            nr++;
//
//    cout << nr / 2 << endl;
//    for (int i = 0; i < n; i++)
//        if (S[i] != -1 && S[i] > i)
//            cout << i << ' ' << S[i] << endl;
//}
//
//
//
//int LCA(vector<int>& S, vector<int>& base, vector<int>& par, int root, int u, int v, int n)
//{
//    vector<bool> inp;
//    inp.resize(n+1, 0);
//    while(true)
//    {
//        u=base[u];
//        inp[u]=true;
//        if (u==root) break;
//        u=par[S[u]];
//    }
//    while(true)
//    {
//        v=base[v];
//        if (inp[v]) return v;
//        else v=par[S[v]];
//    }
//}
//
//void markblos(vector<int>& S, vector<int>& base, vector<int>& par, vector<int>& blos, int lca, int u)
//{
//    while (base[u]!=lca)
//    {
//        int v=S[u];
//        blos[base[u]]=true;
//        blos[base[v]]=true;
//        u=par[v];
//        if (base[u]!=lca) par[u]=v;
//    }
//}
//
//void bloscont(vector<int>& S, vector<int>& base, vector<int>& par, queue<int>& Q, vector<bool>& inq, int s, int u, int v, int n)
//{
//    vector<int> blos;
//    int lca=LCA(S, base, par, s, u, v, n);
//    blos.resize(n+1, 0);
//    markblos(S, base, par, blos, lca, u);
//    markblos(S, base, par, blos, lca, v);
//    if (base[u]!=lca)
//        par[u]=v;
//    if (base[v]!=lca)
//        par[v]=u;
//    for (int x=0; x<n; x++)
//        if (blos[base[x]])
//        {
//            base[x]=lca;
//            if (!inq[x])
//                Q.push(x);
//            inq[x]=true;
//        }
//}
//
//int find_aug(vector<vector<int> >& V, vector<int>& par, vector<int>& S, int s, int n){
//    vector<int> base;
//    vector<bool> inq;
//    queue<int> Q;
//    inq.resize(n+1, false);
//    par.resize(n+1, -1);
//    inq[s]=true;
//    Q.push(s);
//    for(int i=0; i<n+1; i++)
//        base.push_back(i);
//
//    while(!Q.empty()){
//        int ob=Q.front();
//        Q.pop();
//        for(int i=0; i<V[ob].size(); i++){
//            int v=V[ob][i];
//            if (base[ob]!=base[V[ob][i]]&&S[ob]!=v) {
//                if ((v == s) || (S[v] != -1 && par[S[v]] != -1)) {
//                    bloscont(S, base, par, Q, inq, s, ob, v, n);
//                } else if (par[v] == -1) {
//                    par[v] = ob;
//                    if (S[v] == -1)
//                        return v;
//                    else if (!inq[S[v]]) {
//                        Q.push(S[v]);
//                        inq[S[v]] = true;
//                    }
//                }
//            }
//        }
//    }
//
//    return -1;
//}
//
//void aug(vector<int>& par, vector<int>& S, int t){
//    int tmp, m;
//    while(t!=-1){
//        cout<<'?'<<t<<' '<<m<<endl;
//        tmp=par[t];
//        m=S[tmp];
//        S[tmp]=t;
//        S[t]=tmp;
//        t=m;
//    }
//}
//
//void solveall(vector<vector<int> >& V, vector<int>& S,  vector<int>& odw, int n){
//    vector<int> par;
//    odw.resize(n+1, -1);
//    for(int i=0; i<n; i++){
//        if(odw[i]==-1){
//            aug(par, S, find_aug(V, par, S, i, n));
//        }
//    }
//
//    int nr = 0;
//    for (int i = 0; i < n; i++)
//        if (S[i] != -1)
//            nr++;
//
//    cout << nr / 2 << endl;
//    for (int i = 0; i < n; i++)
//        if (S[i] != -1 && S[i] > i)
//            cout << i << ' ' << S[i] << endl;
//}
//
//int main() {
//    string name;
//    ios_base::sync_with_stdio(0);
//    cin>>name;
//    vector<vector<int> > V;
//    vector<int> S, odw;
//    int n, u;
//    cin>>n;
//    cin>>u;
//    set<int> U;
//    V.resize(n+1);
//    S.resize(n+1, -1);
//
//    for(int i=0; i<u; i++){
//        int tmp;
//        cin>>tmp;
//        U.insert(tmp);
//    }
//
//    int m;
//    cin>>m;
//    bool bipart=true;
//    for(int i=0; i<m; i++){
//        int a, b;
//        cin>>a>>b;
//        if(U.find(a)!=U.end() && U.find(b)!=U.end()) {
//            bipart = false;
//        }
//        V[a].push_back(b);
//        V[b].push_back(a);
//    }
//
////    if(bipart) {
////        solvebipart(V,S,odw,n);
////    }
////    else{
//    //return -1;
//    solveall(V, S, odw, n);
//    //solvebipart(V,S,odw,n);
////    }
//
//    return 0;
//}
