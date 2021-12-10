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

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long v1,u;
    unsigned long long w,e,n;
    
    while(cin>>n>>e){
        vector<unordered_map<long long,unsigned long long> > adj(n+1,unordered_map<long long,unsigned long long> ());
        vector<unordered_map<long long,unsigned long long> > edgesindx(n+1,unordered_map<long long,unsigned long long> ());
        for(int i=0;i<e;i++){
            cin>>u>>v1>>w;
            adj[v1][u]=w;
            adj[u][v1]=w;
            edgesindx[v1][u]=i+1;
            edgesindx[u][v1]=i+1;
        }
        unsigned long long mincost=0;
        unordered_set<long long> nseen;
        for(long long i=1;i<=n;i++){
            nseen.insert(i);
        }
        vector<unsigned long long>edgs(n+1,ULLONG_MAX);
        edgs[1]=0;
        priority_queue< pair<unsigned long long,long long>, vector<pair<unsigned long long,long long> > , greater<pair<unsigned long long,long long> > > pq;
        pq.push(make_pair(0,1));
        while(!nseen.empty()){
            pair<unsigned long long,long long> v=pq.top();
            pq.pop();
            if(nseen.find(v.second)!=nseen.end() and edgs[v.second]==v.first){
                nseen.erase(v.second);
                mincost+=v.first;
                for(auto& i:adj[v.second]){
                    if (nseen.find(i.first)!=nseen.end() and edgs[i.first]>i.second){
                        pq.push(make_pair(i.second,i.first));
                        edgs[i.first]=i.second;
                    }
                }
            }
        }
        unordered_set<long long> nseen2;
        for(long long i=1;i<=n;i++){
            nseen2.insert(i);
        }
        vector<unsigned long long> dist(n+1,ULLONG_MAX);
        dist[1]=0;
        vector<long long> parent(n+1,0);
        priority_queue< pair<unsigned long long,long long>, vector<pair<unsigned long long,long long> > , greater<pair<unsigned long long,long long> > > pq2;
        // for (long long i=2;i<=n; i++){
        //     pq2.push(make_pair(ULLONG_MAX,i));
        // }
        
        pq2.push(make_pair(0,1));
        while(!nseen2.empty()){
            pair<unsigned long long,long long> v=pq2.top();
            pq2.pop();
            if(nseen2.find(v.second)!=nseen2.end() and dist[v.second]==v.first){
                // cout<<v.second<<endl;
                // print(dist)
                // print(parent)
                nseen2.erase(v.second);
                for(auto& i:adj[v.second]){
                    if(nseen2.find(i.first)!=nseen2.end() and dist[i.first]==dist[v.second]+i.second){
                        parent[i.first]=v.second;
                    }
                    if(nseen2.find(i.first)!=nseen2.end() and dist[i.first]>dist[v.second]+i.second){
                        pq2.push(make_pair(dist[v.second]+i.second,i.first));
                        dist[i.first]=dist[v.second]+i.second;
                        parent[i.first]=v.second;
                    }
                }
            }
        }
        vector<unsigned long long> res;
        unsigned long long tmp=0;
        for(long long i=2;i<=n;i++){
            res.push_back(edgesindx[i][parent[i]]);
            tmp+=adj[i][parent[i]];
        }
        //print(parent)
        if(tmp<=mincost){
            cout<<"Yes\n";
            for(unsigned long long i:res){
                cout<<i<<"\n";
            }
        }else{
            cout<<"No\n";
        }
        


    }
    return 0;
}