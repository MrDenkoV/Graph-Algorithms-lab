//#include<bits/stdc++.h>
//using namespace std;
//
//#define all(X) begin(X),end(X)
//#define sz(X) (int)(X).size()
//#define pb push_back
//typedef long long ll;
//typedef vector<bool> vb;
//typedef vector<int> vi;
//typedef vector<vector<int> > vvi;
//typedef pair<int,int> pii;
//
//// Debug
//#define DEBUG 1
//#define COUT if(DEBUG) cout<<"\e[36m"
//#define ENDL "\e[39m"<<endl;
//template<typename t>
//void print_vec(vector<t> v){
//#if DEBUG
//    cout<<"\\e[36m";
//    for(auto i : v)
//        cout<<(int)i<<' ';
//    cout<<"\\e[39m"<<endl;
//#endif
//}
//
//// Solution
//struct Road{
//    int to;
//    int low;
//    int high;
//    Road(int t, int l, int h):to(t),low(l),high(h){}
//};
//
//void read(vector<vector<Road> > &G){
//    int n,m;
//    cin>>n>>m;
//    G.clear();
//    G.resize(n);
//    while(m--){
//        int from, to, low, high;
//        cin>>from>>to>>low>>high;
//        from--;to--;
//        G[from].pb(Road(to,low,high));
//    }
//    cout<<"?"<<endl;
//}
//
//bool solve(vector<vector<Road> > &G, vector<pii> &res,vector<bool> &seen, int i=0,int low=numeric_limits<int>::min(), int high=numeric_limits<int>::max()){
//    // cout<<"I "<<i<<" L"<<low<<" H"<<high<<endl;
//    if(i>=sz(G)){
//        res.pb(make_pair(low,high));
//        return true;
//    }
//    if(sz(G[i])==0)
//        return false;
//
//    // cout<<"A"<<endl;
//    res.pb(make_pair(i,G[i][0].to));
//
//    // cout<<"C "<<G[i][0].low<<" : "<<G[i][0].high<<endl;
//    if(!seen[G[i][0].to]){
//        seen[G[i][0].to] = true;
//        if(G[i][0].low <= high
//           && G[i][0].high >= low
//           && solve(G,res,seen,i+1,max(low,G[i][0].low),min(high,G[i][0].high)))
//            return true;
//        seen[G[i][0].to] = false;
//    }
//    // cout<<"B"<<endl;
//    res.pop_back();
//
//    if(G[i].size()<2)
//        return false;
//    // cout<<"C"<<endl;
//    res.pb(make_pair(i,G[i][1].to));
//
//    // cout<<"D "<<G[i][1].low<<" : "<<G[i][1].high<<endl;
//    if(!seen[G[i][1].to]){
//        seen[G[i][1].to] = true;
//        if(G[i][1].low <= high
//           && G[i][1].high >= low
//           && solve(G,res,seen, i+1,max(low,G[i][1].low),min(high,G[i][1].high)))
//            return true;
//        seen[G[i][1].to] = false;
//    }
//    // cout<<"D"<<endl;
//    res.pop_back();
//    return false;
//}
//
//int main(){
//    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//    int z;
//    cin>>z;
//    while(z--){
//        vector<vector<Road> > G;
//        read(G);
//        vector<pii> res;
//        vector<bool> seen(sz(G),false);
//        if(solve(G, res, seen)){
//            pii low_high = res[res.size()-1];
//            res.pop_back();
//            cout<<low_high.first<<endl;
//            for(auto v : res){
//                cout<<v.first+1<<" "<<v.second+1<<endl;
//            }
//        }else
//        {
//            cout<<-1<<endl;
//        }
//
//    }
//}