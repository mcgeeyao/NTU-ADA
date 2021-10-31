#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;


vector<long long> p(vector<vector<long long>>&V,vector<vector<unordered_map<int,long long>>>&P,vector<vector<unordered_map<int,pair<int,int>>>>pre,int i,int j,int k){
    //cout<<i<<j<<k<<endl;
    if(i<0 or j<0){
        return (vector<long long>){LLONG_MIN,-1,-1};
    }
    if(P[i][j].find(k)!=P[i][j].end()){
        return (vector<long long>){P[i][j][k],pre[i][j][k].first,pre[i][j][k].second};
    }
    if(k==0){
        return (vector<long long>){V[i][j],i,j};
    }
    if(k==1){
        vector<long long>tmp=max((vector<long long>){V[i][max(0,j-1)],i,max(0,j-1)},(vector<long long>){V[max(0,i-1)][j],max(0,i-1),j});
        tmp=max(tmp,{V[i][j],i,j});
        P[i][j][k]=tmp[0];
        pre[i][j][k]=make_pair(tmp[1],tmp[2]);
        return tmp;
    }
    if(k==2){
        vector<long long> tmp=max((vector<long long>){V[i][j],i,j},p(V,P,pre,i, j-1, 1));
        tmp=max(tmp,p(V,P,pre,i-1, j, 1));
        P[i][j][k]=tmp[0];
        pre[i][j][k]=make_pair(tmp[1],tmp[2]);
        return tmp;
    }
    vector<long long> tmp=max(p(V,P,pre,i, j, k-k/3),p(V,P,pre,i, j-k/3, k-k/3));
    tmp=max(tmp,p(V,P,pre,i-k/3, j, k-k/3));
    P[i][j][k]=tmp[0];
    pre[i][j][k]=make_pair(tmp[1],tmp[2]);
    return tmp;
    
}




long long N=-456456456457;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k,m,n,cases;
    string x;
    while(cin>>cases){
        for(int c=0;c<cases;c++){
            cin>>m>>n>>k;
            vector<vector<long long>>v(m,vector<long long>(n,LLONG_MIN));
            vector<vector<long long>>dp(m,vector<long long>(n,LLONG_MIN));
            vector<vector<unordered_map<int,long long>>>P(m,vector<unordered_map<int,long long>>(n,unordered_map<int,long long>()));
            vector<vector<unordered_map<int,pair<int,int>>>>Ppre(m,vector<unordered_map<int,pair<int,int>>>(n,unordered_map<int,pair<int,int>>()));
            vector<vector<pair<int,int>>>pre(m,vector<pair<int,int>>(n));
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    cin>>x;
                    if(x!="X"){
                        v[i][j]=stol(x);
                    }
                }
            }
            dp[0][0]=0;
            for(int i=1;i<m;i++){
                if(v[i][0]==LLONG_MIN){
                        dp[i][0]=LLONG_MIN;
                }else{
                    vector<long long> tmp=p(dp,P,Ppre,i,0,k);
                    if (tmp[0]==LLONG_MIN){
                            dp[i][0]=LLONG_MIN;
                    }
                    else{
                        dp[i][0]=tmp[0]+v[i][0];
                        pre[i][0]=make_pair(tmp[1],tmp[2]);
                    }
                } 
            }
            for(int i=1;i<n;i++){
                if(v[0][i]==LLONG_MIN){
                        dp[0][i]=LLONG_MIN;
                }else{
                    vector<long long> tmp=p(dp,P,Ppre,0,i,k);
                    if (tmp[0]==LLONG_MIN){
                            dp[0][i]=LLONG_MIN;
                    }
                    else{
                        dp[0][i]=tmp[0]+v[0][i];
                        pre[0][i]=make_pair(tmp[1],tmp[2]);
                    }
                }
                
            }
            for(int i=1;i<m;i++){
                for(int j=1;j<n;j++){
                    if(v[i][j]==LLONG_MIN){
                        dp[i][j]=LLONG_MIN;
                    }else{
                        vector<long long> tmp1=p(dp,P,Ppre,i,j,k);
                        if (tmp1[0]==LLONG_MIN){
                            dp[i][j]=LLONG_MIN;
                        }else{
                            dp[i][j]=tmp1[0]+v[i][j];
                            pre[i][j]=make_pair(tmp1[1],tmp1[2]);
                        }
                    }
                    
                    
                }
            }
            // for(auto i:dp){
            //     for(auto j:i){
            //         cout<<j<<" ";
            //     }cout<<endl;
            // }
            
            if(dp[m-1][n-1]==LLONG_MIN){
                cout<<"Impassable"<<endl;
                continue;
            }
            cout<<"Passable"<<endl;
            cout<<dp[m-1][n-1]<<endl;
            pair<int,int> p=make_pair(m-1,n-1);
            vector<pair<int,int>>path;
            while (pre[p.first][p.second].first!=0 or pre[p.first][p.second].second!=0){
                path.push_back(p);
                p=pre[p.first][p.second];
            }path.push_back(p);
            path.push_back(make_pair(0,0));
            reverse(path.begin(),path.end());
            cout<<path.size()<<endl;
            for(auto pa:path){
                cout<<pa.first+1<<" "<<pa.second+1<<endl;
            }
        }
    }
    return 0;
}