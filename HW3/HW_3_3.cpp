//dijkstra and prim's



#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
using namespace std;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int v1,u,w,e,n;
    
    while(cin>>n>>e){
        vector<unordered_map<int,pair<int,int> > > adj(n+1,unordered_map<int,pair<int,int> > ());
        //vector<unordered_map<int,int> > edgesindx(n+1,unordered_map<int,int> ());
        for(int i=0;i<e;i++){
            cin>>u>>v1>>w;
            if (adj[v1].find(u)==adj[v1].end()){
                adj[v1][u]=make_pair(w,i+1);
                adj[u][v1]=make_pair(w,i+1);
                // edgesindx[v1][u]=i+1;
                // edgesindx[u][v1]=i+1;
            }else if(adj[v1][u].first>w){
                    adj[v1][u]=make_pair(w,i+1);
                    adj[u][v1]=make_pair(w,i+1);
                    // edgesindx[v1][u]=i+1;
                    // edgesindx[u][v1]=i+1;
            }
            
        }
        long mincost=0;
        vector<bool> nseen(n+1,false);
        int cnt=0;
        vector<int>edgs(n+1,INT_MAX);
        priority_queue< pair<int,int>, vector<pair<int,int> > , greater<pair<int,int> > > pq;
        pq.push(make_pair(0,1));
        while(cnt<n){
            pair<int,int> v=pq.top();
            pq.pop();
            
            if(!nseen[v.second]){
                nseen[v.second]=true;
                cnt++;
                //nseen.erase(v.second);
                mincost+=v.first;
                for(auto& i:adj[v.second]){
                    if (!nseen[i.first] and edgs[i.first]>i.second.first){
                        pq.push(make_pair(i.second.first,i.first));
                        edgs[i.first]=i.second.first;
                    }
                }
            }
        }
        cnt=0;
        vector<long> dist(n+1,LONG_MAX);
        dist[1]=0;
        vector<int> parent(n+1);
        priority_queue< pair<long,int>, vector<pair<long,int> > , greater<pair<long,int> > > pq2;
        long tmp=0;
        pq2.push(make_pair(0,1));
        while(cnt<n){
            pair<long,int> v=pq2.top();
            pq2.pop();
            if(nseen[v.second]){
                nseen[v.second]=false;
                cnt++;
                tmp+=adj[parent[v.second]][v.second].first;
                for(auto& i:adj[v.second]){
                    if(nseen[i.first] and dist[i.first]==dist[v.second]+i.second.first){
                        parent[i.first]=v.second;
                    }else if(nseen[i.first] and dist[i.first]>dist[v.second]+i.second.first){
                        dist[i.first]=dist[v.second]+i.second.first;
                        pq2.push(make_pair(dist[i.first],i.first));
                        parent[i.first]=v.second;
                    }
                }
            }
        }
        //print(parent)
        if(tmp==mincost){
            cout<<"Yes\n";
            for(int i=2;i<=n;i++){
                cout<<adj[parent[i]][i].second<<"\n";
            }
        }else{
            cout<<"No\n";
        }
        


    }
    return 0;
}