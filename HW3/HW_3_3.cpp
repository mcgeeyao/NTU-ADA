#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <map>
#define print(vec)\
for (int i=0;i<vec.size();i++)\
cout<<vec[i]<<" ";\
cout<<endl;
using namespace std;
unordered_map<long long,long long>::iterator it;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long w,e,v1,u,n;
    
    while(cin>>n>>e){
        vector<unordered_map<long long,long long> > adj(n+1,unordered_map<long long,long long> ());
        vector<unordered_map<long long,long long> > edgesindx(n+1,unordered_map<long long,long long> ());
        for(long long i=0;i<e;i++){
            cin>>u>>v1>>w;
            adj[v1][u]=w;
            adj[u][v1]=w;
            edgesindx[v1][u]=i+1;
            edgesindx[u][v1]=i+1;
        }
        long long mincost=0;
        unordered_set<long long> nseen;
        for(long long i=1;i<n+1;i++){
            nseen.insert(i);
        }
        vector<long long>edgs(n+1,LLONG_MAX);
        edgs[1]=0;
        priority_queue< pair<long long,long long>, vector<pair<long long,long long> > , greater<pair<long long,long long> > > pq;
        pq.push(make_pair(0,1));
        while(!nseen.empty()){
            pair<long long,long long> v=pq.top();
            pq.pop();
            if(nseen.find(v.second)!=nseen.end() and edgs[v.second]==v.first){
                nseen.erase(v.second);
                mincost+=v.first;
                for(it=adj[v.second].begin();it!=adj[v.second].end();it++){
                    if (nseen.find(it->first)!=nseen.end() and edgs[it->first]>it->second){
                        pq.push(make_pair(it->second,it->first));
                        edgs[it->first]=it->second;
                    }
                }
            }
        }
        unordered_set<long long> nseen2;
        for(long long i=1;i<n+1;i++){
            nseen2.insert(i);
        }
        vector<long long> dist(n+1,LLONG_MAX);
        dist[1]=0;
        vector<long long> parent(n+1,-1);
        priority_queue< pair<long long,long long>, vector<pair<long long,long long> > , greater<pair<long long,long long> > > pq2;
        // for (long long i=2;i<=n; i++){
        //     pq2.push(make_pair(LLONG_MAX,i));
        // }
        
        pq2.push(make_pair(0,1));
        while(!nseen2.empty()){
            pair<long long,long long> v=pq2.top();
            pq2.pop();
            if(nseen2.find(v.second)!=nseen2.end() and dist[v.second]==v.first){
                // cout<<v.second<<endl;
                // print(dist)
                // print(parent)
                nseen2.erase(v.second);
                for(it=adj[v.second].begin();it!=adj[v.second].end();it++){
                    if(nseen2.find(it->first)!=nseen2.end() and dist[it->first]==dist[v.second]+it->second){
                        parent[it->first]=v.second;
                    }
                    if(nseen2.find(it->first)!=nseen2.end() and dist[it->first]>dist[v.second]+it->second){
                        pq2.push(make_pair(dist[v.second]+it->second,it->first));
                        dist[it->first]=dist[v.second]+it->second;
                        parent[it->first]=v.second;
                    }
                }
            }
        }
        vector<long long> res;
        long long tmp=0;
        for(long long i=2;i<n+1;i++){
            res.push_back(edgesindx[parent[i]][i]);
            tmp+=adj[parent[i]][i];
        }
        //print(parent)
        if(tmp<=mincost){
            cout<<"Yes\n";
            for(long long i:res){
                cout<<i<<"\n";
            }
        }else{
            cout<<"No\n";
        }
        


    }
    return 0;
}