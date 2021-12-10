#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <map>
#define print(v)\
for (int i=0;i<v.size();i++)\
cout<<v[i]<<" ";\
cout<<endl;
using namespace std;
unsigned long long n;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int v1,u;
    unsigned long long w,e;
    
    while(cin>>n>>e){
        vector<unordered_map<int,unsigned long long> > adj(n,unordered_map<int,unsigned long long> ());
        vector<unordered_map<int,unsigned long long> > edgesindx(n,unordered_map<int,unsigned long long> ());
        for(int i=0;i<e;i++){
            cin>>u>>v1>>w;
            adj[v1-1][u-1]=w;
            adj[u-1][v1-1]=w;
            edgesindx[v1-1][u-1]=i+1;
            edgesindx[u-1][v1-1]=i+1;
        }
        unsigned long long mincost=0;
        unordered_set<int> nseen;
        for(int i=0;i<n;i++){
            nseen.insert(i);
        }
        priority_queue< pair<unsigned long long,int>, vector<pair<unsigned long long,int> > , greater<pair<unsigned long long,int> > > pq;
        pq.push(make_pair(0,0));
        while(!nseen.empty()){
            pair<unsigned long long,int> v=pq.top();
            pq.pop();
            if(nseen.find(v.second)!=nseen.end()){
                nseen.erase(v.second);
                mincost+=v.first;
                for(auto& i:adj[v.second]){
                    if (nseen.find(i.first)!=nseen.end()){
                        pq.push(make_pair(i.second,i.first));
                    }
                }
            }
        }
        unordered_set<int> nseen2;
        for(int i=0;i<n;i++){
            nseen2.insert(i);
        }
        vector<unsigned long long> dist(n,ULLONG_MAX);
        dist[0]=0;
        vector<int> parent(n,-1);
        priority_queue< pair<unsigned long long,int>, vector<pair<unsigned long long,int> > , greater<pair<unsigned long long,int> > > pq2;
        // for (int i=2;i<=n; i++){
        //     pq2.push(make_pair(ULLONG_MAX,i));
        // }
        
        pq2.push(make_pair(0,0));
        while(!nseen2.empty()){
            pair<unsigned long long,int> v=pq2.top();
            pq2.pop();
            if(nseen2.find(v.second)!=nseen2.end() and dist[v.second]==v.first){
                nseen2.erase(v.second);
                for(auto& i:adj[v.second]){
                    if(nseen2.find(i.first)!=nseen2.end() and dist[i.first]==dist[v.second]+i.second /*and i.second<adj[i.first][parent[i.first]]*/){
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
        for(int i=1;i<n;i++){
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