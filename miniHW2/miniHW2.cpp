#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void dfs(int curr,unordered_set<int>& seen,unordered_map<int,vector<int> >& edges){
    if(seen.find(curr)!=seen.end()){
        return ;
    }
    cout<<curr<<" ";
    seen.insert(curr);
    for(auto i:edges[curr]){
        dfs(i,seen,edges);
    }
}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int v,u,n,x;
    
    while(cin>>x>>n){
        unordered_map<int,vector<int> > edges;
        for(int i=0;i<n;i++){
            cin>>u>>v;
            edges[v].push_back(u);
            edges[u].push_back(v);
        }
        for(int i=1;i<=x;i++){
            sort(edges[i].begin(),edges[i].end());
            reverse(edges[i].begin(),edges[i].end());
        }

        unordered_set<int> seen;
        vector<int> stk;
        stk.push_back(1);
        while(!stk.empty()){
            int curr=stk[stk.size()-1];
            stk.pop_back();
            if(seen.find(curr)==seen.end()){
                cout<<curr<<" ";
                seen.insert(curr);
                for(auto i:edges[curr]){
                    stk.push_back(i);
                }
            }
        }
        cout<<endl;
        unordered_set<int> seen2;
        vector<int> que;
        que.push_back(1);
        while(!que.empty()){
            sort(que.begin(),que.end());
            vector<int> tmp;
            for(auto curr:que){
                if(seen2.find(curr)==seen2.end()){
                    cout<<curr<<" ";
                    seen2.insert(curr);
                    for(auto i:edges[curr]){
                        tmp.push_back(i);
                    }
                }
            }
            que=tmp;
        }
    }
    return 0;
}