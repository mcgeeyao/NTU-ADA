//DAG 
//topological sort
//無情TLE


#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;


void dfs( unordered_map<int,vector<int>> &edges ,vector<int> &color ,vector<int> &finish_time ,int v ){
    color[v] = 1;
    for(int u:edges[v]){
        if (color[u]==0){
            dfs(edges, color, finish_time, u);
        }
    }
    color[v] = 2;
    finish_time.push_back(v);
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k,m,n,cases;
    string x;
    while(cin>>cases){
        for(int c=0;c<cases;c++){
            cin>>m>>n>>k;
            vector<vector<int>>v;
            vector<pair<int,int>>nodes;
            unordered_map<int,vector<int>>edges;
            vector<long>val;
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    cin>>x;
                    if(x!="X"){
                        for(int nodesnum=0;nodesnum<nodes.size();nodesnum++){
                            if(i+j-nodes[nodesnum].first-nodes[nodesnum].second<=k and i>=nodes[nodesnum].first and j>=nodes[nodesnum].second){
                                edges[nodesnum].push_back(nodes.size());
                            }
                        }
                        val.push_back(-stoll(x));
                        nodes.push_back(make_pair(i,j));
                    }
                }
            } 
            // int a=0;
            // for(auto i:nodes){
            //     cout<<a<<":"<<i.first<<" "<<i.second<<" "<<endl;
            //     a++;
            // }cout<<endl;

            // 0:white 1:gray 2:black  
            vector<int>color(nodes.size(),0);
            vector<int>finish_time;
            dfs(edges, color, finish_time, 0);

            if(color[nodes.size()-1]==0){
                cout<<"Impassable";
                continue;
            }
            
            reverse(finish_time.begin(),finish_time.end());
            vector<long long>dist(nodes.size(),LLONG_MAX);
            dist[0]=0;
            vector<int>pre(nodes.size(),-1);
            for(auto i:finish_time){
                for(auto adj:edges[i]){
                    if(dist[i]+val[adj]<dist[adj]){
                        dist[adj]=dist[i]+val[adj];
                        pre[adj]=i;
                    }
                }
            }


            vector<int>path;
            int tmp=nodes.size()-1;
            while (pre[tmp]!=-1){
                path.push_back(tmp);
                tmp=pre[tmp];
            }path.push_back(0);
            reverse(path.begin(),path.end());
            cout<<"Passable"<<endl;
            cout<<-dist[nodes.size()-1]<<endl;
            cout<<path.size()<<endl;
            for(auto i:path){
                cout<<nodes[i].first+1<<" "<<nodes[i].second+1<<endl;
            }

            // cout<<"finish_time:"<<endl;
            // for(auto i:finish_time){
            //     cout<<i<<" ";
            // }cout<<endl;
            // cout<<"edges:"<<endl;
            // for(int i=0;i<nodes.size();i++){
            //     cout<<i<<":";
            //     for(auto j:edges[i]){
            //         cout<<j;
            //     }cout<<endl;
            // }
            // cout<<"dist:"<<endl;
            // for(auto i:dist){
            //     cout<<i<<" ";
            // }cout<<endl;
            // cout<<"pre:"<<endl;
            // for(auto i:pre){
            //     cout<<i<<" ";
            // }cout<<endl;
            // cout<<"path:"<<endl;
            // for(auto i:path){
            //     cout<<i<<" ";
            // }cout<<endl;
        }
    }
    return 0;
}