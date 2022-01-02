#include "ypglpk.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <assert.h>
#define print(v)\
for (auto i:v)\
cout<<i<<" ";\
cout<<endl;
using namespace std;
using namespace ypglpk;

int clique_num;

void Bron(unordered_set<int> &R,unordered_set<int> &P,unordered_set<int> &X, vector<unordered_set<int>> &adj,vector<vector<int>> &maximal_clique,vector<vector<int> > &overlap){
    if(P.empty() and X.empty()){
        vector<int> tmp;
        for(auto i:R){
            tmp.push_back(i);
            overlap[i].push_back(clique_num);
        }
        clique_num++;
        maximal_clique.push_back(tmp);
        return;
    }
    unordered_set<int> P_union_X;
    for(auto i:P)P_union_X.insert(i);
    for(auto i:X)P_union_X.insert(i);

    int u=*P_union_X.begin();

    unordered_set<int> P_adju_diff;
    for(auto i:P)if(adj[u].find(i)==adj[u].end())P_adju_diff.insert(i);
    for(auto v:P_adju_diff){
        unordered_set<int> P_intersect_adjv,X_intersect_adjv;
        R.insert(v);
        for(auto i:P)if(adj[v].find(i)!=adj[v].end())P_intersect_adjv.insert(i);
        for(auto i:X)if(adj[v].find(i)!=adj[v].end())X_intersect_adjv.insert(i);        
        Bron(R,P_intersect_adjv,X_intersect_adjv,adj,maximal_clique,overlap);
        R.erase(v);
        P.erase(v);
        X.insert(v);
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int v,u,n,m,cases;

    while(cin>>cases){
        for(int c=0;c<cases;c++){
            pair<double,vector<double>> lp_res;
            clique_num=0;
            cin>>n>>m;
            vector<vector<int> > res,maximal_clique;
            vector<unordered_set<int> > adj(n,unordered_set<int> ());
            vector<vector<int> > overlap(n,vector<int> ());
            for(int i=0;i<m;i++){
                cin>>v>>u;
                if(v!=u){
                    adj[v].insert(u);
                    adj[u].insert(v);
                }
                
            }
            unordered_set<int> R,P,X;
            for(int i=0;i<n;i++)P.insert(i);
            Bron(R,P,X,adj,maximal_clique,overlap);

            vector<vector<double>> A(n+clique_num*2,vector<double>(clique_num,0));
            vector<double> B(n+clique_num*2,1),C(clique_num,-1);
            vector<bool> isint(clique_num,true);
            for(int i=0;i<n;i++){
                for(auto cl:overlap[i]){
                    A[i][cl]=-1;
                }
                B[i]=-1;
            }
            for(int i=0;i<clique_num;i++){
                A[i+n][i]=-1;
                B[i+n]=0;
                A[i+n+clique_num][i]=1;
            }


            lp_res=mixed_integer_linear_programming(A,B,C,isint); 
            cout<<-lp_res.first<<endl;
            vector<bool> vis(n,false);
            for(int i=0;i<maximal_clique.size();i++){
                if(lp_res.second[i]){
                    assert(lp_res.second[i]==1);
                    vector<int> tmp;
                    for(int j:maximal_clique[i]){
                        if(!vis[j]){
                            tmp.push_back(j);
                            vis[j]=true;
                        }
                    }cout<<tmp.size()<<" ";
                    print(tmp)
                }
            }

        }
    }
    return 0;
}