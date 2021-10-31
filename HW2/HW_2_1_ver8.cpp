#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;


vector<long long> p(bool pn,vector<vector<long long>>&V,
vector<vector<vector<long long>>>&P,vector<vector<vector<long long>>>&N,
vector<vector<vector<pair<int,int>>>>&Ppre,vector<vector<vector<pair<int,int>>>>&Npre,
int i,int j,int k){
    if(k==0){
        return (vector<long long>){V[i][j],i,j};
    }
    if(k==1){
        if(pn){
            vector<long long>tmp=max((vector<long long>){V[i][max(0,j-1)],i,max(0,j-1)},(vector<long long>){V[max(0,i-1)][j],max(0,i-1),j});
            tmp=max(tmp,{V[i][j],i,j});
            return tmp;
        }else{
            vector<long long>tmp=max((vector<long long>){V[i][min((int)V[0].size()-1,j+1)],i,min((int)V[0].size()-1,j+1)},(vector<long long>){V[min((int)V.size()-1,i+1)][j],min((int)V.size()-1,i+1),j});
            tmp=max(tmp,{V[i][j],i,j});
            return tmp;
        }
    }
    if(pn and P[i][j][k]!=LLONG_MIN){
        return (vector<long long>){P[i][j][k],Ppre[i][j][k].first,Ppre[i][j][k].second};
    }
    if(!pn and N[i][j][k]!=LLONG_MIN){
        return (vector<long long>){N[i][j][k],Npre[i][j][k].first,Npre[i][j][k].second};
    }
    if(pn){
        vector<long long> tmp=max(p(true,V,P,N,Ppre,Npre,i, j, k/2),p(true,V,P,N,Ppre,Npre,i, max(0,j-k/2), k/2+k%1));
        tmp=max(tmp,p(true,V,P,N,Ppre,Npre,max(0,i-k/2), j, k/2+k%1));
        if(i-k/2<0 or j-k/2<0){
            tmp=max(tmp,p(false,V,P,N,Ppre,Npre,max(0,i-k/2), max(0,j-k/2), min(i,j)));
        }
        else{
            tmp=max(tmp,p(false,V,P,N,Ppre,Npre,max(0,i-k/2), max(0,j-k/2), k/2));
        }
        
        P[i][j][k]=tmp[0];
        Ppre[i][j][k]=make_pair(tmp[1],tmp[2]);
        return tmp;
    }else{
        vector<long long> tmp=max(p(false,V,P,N,Ppre,Npre,i, j, k/2),p(false,V,P,N,Ppre,Npre,i, min((int)V[0].size()-1,j+k/2), k/2+k%1));
        tmp=max(tmp,p(false,V,P,N,Ppre,Npre,min(i+k/2,(int)V.size()-1), j, k/2+k%1));
        tmp=max(tmp,p(true,V,P,N,Ppre,Npre,min(i+k/2,(int)V.size()-1), min((int)V[0].size()-1,j+k/2), k/2));
        N[i][j][k]=tmp[0];
        Npre[i][j][k]=make_pair(tmp[1],tmp[2]);
        return tmp;
    }
    
}




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
            vector<vector<vector<long long>>>P(m,vector<vector<long long>>(n,vector<long long>(k+1,LLONG_MIN)));
            vector<vector<vector<long long>>>N(m,vector<vector<long long>>(n,vector<long long>(k+1,LLONG_MIN)));
            vector<vector<vector<pair<int,int>>>>Npre(m,vector<vector<pair<int,int>>>(n,vector<pair<int,int>>(k+1)));
            vector<vector<vector<pair<int,int>>>>Ppre(m,vector<vector<pair<int,int>>>(n,vector<pair<int,int>>(k+1)));
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
                    vector<long long> tmp=p(true,dp,P,N,Ppre,Npre,i-1,0,k-1);
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
                    vector<long long> tmp=p(true,dp,P,N,Ppre,Npre,0,i-1,k-1);
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
                        vector<long long> tmp1=p(true,dp,P,N,Ppre,Npre,i-1,j,k-1);
                        vector<long long> tmp2=p(true,dp,P,N,Ppre,Npre,i,j-1,k-1);
                        if (tmp1[0]==LLONG_MIN and tmp2[0]==LLONG_MIN ){
                            dp[i][j]=LLONG_MIN;
                        }
                        else if(tmp1[0]>tmp2[0]){
                            dp[i][j]=tmp1[0]+v[i][j];
                            pre[i][j]=make_pair(tmp1[1],tmp1[2]);
                        }else{
                            dp[i][j]=tmp2[0]+v[i][j];
                            pre[i][j]=make_pair(tmp2[1],tmp2[2]);
                        }
                    }
                    
                    
                }
            }
            
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