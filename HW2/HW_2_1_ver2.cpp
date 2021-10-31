#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;


long long N=-456456456457;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k,m,n,cases;
    string x;
    while(cin>>cases){
        for(int c=0;c<cases;c++){
            cin>>m>>n>>k;
            vector<vector<long long>>v(m,vector<long long>(n,N));
            vector<vector<vector<pair<long long,int>>>>dp(m,vector<vector<pair<long long,int>>>(n,vector<pair<long long,int>>()));
            vector<vector<vector<pair<int,int>>>>curr(m,vector<vector<pair<int,int>>>(n,vector<pair<int,int>>()));
            vector<vector<pair<int,int>>>pre(m,vector<pair<int,int>>(n));
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    cin>>x;
                    if(x!="X"){
                        v[i][j]=stol(x);
                    }
                }
            }
            dp[0][0].push_back(make_pair(0,k));
            curr[0][0].push_back(make_pair(0,0));
            pre[0][0]=make_pair(-1,-1);

            for(int i=1;i<n;i++){
                if(v[0][i]!=N){
                    long long tmp=LLONG_MIN;
                    pair<int,int> pre_pair;
                    bool check=false;
                    for(int pres=0;pres<dp[0][i-1].size();pres++){
                        if(dp[0][i-1][pres].second>0){
                            if(dp[0][i-1][pres].first+v[0][i]>tmp){
                                tmp=dp[0][i-1][pres].first+v[0][i];
                                pre_pair=curr[0][i-1][pres];
                                check=true;
                            }
                        }
                    }
                    if(check){
                        for(int pres=0;pres<dp[0][i-1].size();pres++){
                            if(dp[0][i-1][pres].second>0 and dp[0][i-1][pres].first>tmp){
                                dp[0][i].push_back(make_pair(dp[0][i-1][pres].first,dp[0][i-1][pres].second-1));
                                curr[0][i].push_back(make_pair(curr[0][i-1][pres].first,curr[0][i-1][pres].second));
                            }
                        }
                        dp[0][i].push_back(make_pair(tmp,k));
                        curr[0][i].push_back(make_pair(0,i));
                        
                        pre[0][i]=pre_pair;
                    }else{
                        pre[0][i]=make_pair(-1,-1);
                    }
                    //cout<<0<<" "<<i<<" :"<<tmp<<endl;
                }else{
                    //cout<<0<<" "<<i<<" :"<<endl;
                    for(int pres=0;pres<dp[0][i-1].size();pres++){
                        if(dp[0][i-1][pres].second>0){
                            //cout<<dp[0][i-1][pres].first<<","<<dp[0][i-1][pres].second<<endl;
                            dp[0][i].push_back(make_pair(dp[0][i-1][pres].first,dp[0][i-1][pres].second-1));
                            curr[0][i].push_back(make_pair(curr[0][i-1][pres].first,curr[0][i-1][pres].second));
                        }
                    }
                }
            }

            for(int i=1;i<m;i++){
                if(v[i][0]!=N){
                    long long tmp=LLONG_MIN;
                    pair<int,int> pre_pair;
                    bool check=false;
                    for(int pres=0;pres<dp[i-1][0].size();pres++){
                        if(dp[i-1][0][pres].second>0){
                            if(dp[i-1][0][pres].first+v[i][0]>tmp){
                                tmp=dp[i-1][0][pres].first+v[i][0];
                                pre_pair=curr[i-1][0][pres];
                                check=true;
                            }
                        }
                    }
                    if(check){
                        for(int pres=0;pres<dp[i-1][0].size();pres++){
                            if(dp[i-1][0][pres].second>0 and dp[i-1][0][pres].first>tmp){
                                dp[i][0].push_back(make_pair(dp[i-1][0][pres].first,dp[i-1][0][pres].second-1));
                                curr[i][0].push_back(make_pair(curr[i-1][0][pres].first,curr[i-1][0][pres].second));
                            }
                        }
                        dp[i][0].push_back(make_pair(tmp,k));
                        curr[i][0].push_back(make_pair(i,0));
                        pre[i][0]=pre_pair;
                    }else{
                        pre[i][0]=make_pair(-1,-1);
                    }
                    ////cout<<i<<" "<<0<<" :"<<tmp<<endl;
                }else{
                    //cout<<i<<" "<<0<<" :"<<tmp<<endl;
                    for(int pres=0;pres<dp[i-1][0].size();pres++){
                        if(dp[i-1][0][pres].second>0){
                            //cout<<dp[i-1][0][pres].first<<","<<dp[i-1][0][pres].second<<endl;
                            dp[i][0].push_back(make_pair(dp[i-1][0][pres].first,dp[i-1][0][pres].second-1));
                            curr[i][0].push_back(make_pair(curr[i-1][0][pres].first,curr[i-1][0][pres].second));
                        }
                    }
                }
            }


            for(int i=1;i<m;i++){
                for(int j=1;j<n;j++){
                    if(v[i][j]!=N){
                        long long tmp=LLONG_MIN;
                        pair<int,int> pre_pair;
                        bool check=false;
                        for(int pres=0;pres<dp[i-1][j].size();pres++){
                            if(dp[i-1][j][pres].second>0){
                                if(dp[i-1][j][pres].first+v[i][j]>tmp){
                                    tmp=dp[i-1][j][pres].first+v[i][j];
                                    pre_pair=curr[i-1][j][pres];
                                    check=true;
                                }
                            }
                        }
                        for(int pres=0;pres<dp[i][j-1].size();pres++){
                            if(dp[i][j-1][pres].second>0){
                                if(dp[i][j-1][pres].first+v[i][j]>tmp){
                                    tmp=dp[i][j-1][pres].first+v[i][j];
                                    pre_pair=curr[i][j-1][pres];
                                    check=true;
                                }
                            }
                        }

                        if(check){
                            for(int pres=0;pres<dp[i-1][j].size();pres++){
                                if(dp[i-1][j][pres].second>0 and dp[i-1][j][pres].first>tmp){
                                    dp[i][j].push_back(make_pair(dp[i-1][j][pres].first,dp[i-1][j][pres].second-1));
                                    curr[i][j].push_back(make_pair(curr[i-1][j][pres].first,curr[i-1][j][pres].second));
                                }
                            }
                            for(int pres=0;pres<dp[i][j-1].size();pres++){
                                if(dp[i][j-1][pres].second>0 and dp[i][j-1][pres].first>tmp){
                                    dp[i][j].push_back(make_pair(dp[i][j-1][pres].first,dp[i][j-1][pres].second-1));
                                    curr[i][j].push_back(make_pair(curr[i][j-1][pres].first,curr[i][j-1][pres].second));
                                }
                            }


                            dp[i][j].push_back(make_pair(tmp,k));
                            curr[i][j].push_back(make_pair(i,j));
                            pre[i][j]=pre_pair;
                        }else{
                            pre[i][j]=make_pair(-1,-1);
                        }
                        // //cout<<i<<" "<<j<<" :"<<tmp<<endl;
                        // //cout<<pre[i][j].first<<" "<<pre[i][j].second<<endl;

                    }else{
                        //cout<<i<<" "<<j<<" :"<<endl;
                        for(int pres=0;pres<dp[i][j-1].size();pres++){
                            if(dp[i][j-1][pres].second>0){
                                //cout<<dp[i-1][0][pres].first<<","<<dp[i-1][0][pres].second<<endl;
                                dp[i][j].push_back(make_pair(dp[i][j-1][pres].first,dp[i][j-1][pres].second-1));
                                curr[i][j].push_back(make_pair(curr[i][j-1][pres].first,curr[i][j-1][pres].second));
                            }
                        }
                        for(int pres=0;pres<dp[i-1][j].size();pres++){
                            if(dp[i-1][j][pres].second>0){
                                //cout<<dp[i-1][0][pres].first<<","<<dp[i-1][0][pres].second<<endl;
                                dp[i][j].push_back(make_pair(dp[i-1][j][pres].first,dp[i-1][j][pres].second-1));
                                curr[i][j].push_back(make_pair(curr[i-1][j][pres].first,curr[i-1][j][pres].second));
                            }
                        }
                    }
                }
            }
            //cout<<pre[m-1][n-1].first<<" "<<pre[m-1][n-1].second<<endl;
            if(pre[m-1][n-1].first==-1){
                cout<<"Impassable"<<endl;
                continue;
            }
            cout<<"Passable"<<endl;
            cout<<dp[m-1][n-1].size()<<endl;
            cout<<dp[m-1][n-1][dp[m-1][n-1].size()-1].first<<endl;
            pair<int,int> p=make_pair(m-1,n-1);
            vector<pair<int,int>>path;
            while (pre[p.first][p.second].first!=-1){
                path.push_back(p);
                p=pre[p.first][p.second];
            }path.push_back(p);
            reverse(path.begin(),path.end());
            cout<<path.size()<<endl;
            for(auto pa:path){
                cout<<pa.first+1<<" "<<pa.second+1<<endl;
            }
            



        }
    }
    return 0;
}