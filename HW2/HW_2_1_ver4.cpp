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
            vector<vector<vector<long long>>>dp(m,vector<vector<long long>>(n,vector<long long>(k+1,LLONG_MIN)));
            vector<vector<vector<pair<int,int>>>>curr(m,vector<vector<pair<int,int>>>(n,vector<pair<int,int>>(k+1)));
            vector<vector<pair<int,int>>>pre(m,vector<pair<int,int>>(n));
            vector<vector<vector<int>>>exist(m,vector<vector<int>>(n,vector<int>()));
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    cin>>x;
                    if(x!="X"){
                        v[i][j]=stol(x);
                    }
                }
            }
            dp[0][0][k]=0;
            curr[0][0][k]=(make_pair(0,0));
            pre[0][0]=make_pair(-1,-1);
            exist[0][0].push_back(k);

            for(int i=1;i<n;i++){
                if(v[0][i]!=N){
                    long long tmp=LLONG_MIN;
                    pair<int,int> pre_pair;
                    bool check=false;
                    for(auto pres:exist[0][i-1]){
                            if(dp[0][i-1][pres]+v[0][i]>tmp and pres>0){
                                tmp=dp[0][i-1][pres]+v[0][i];
                                pre_pair=curr[0][i-1][pres];
                                check=true;
                            }
                    }
                    if(check){
                        for(auto pres:exist[0][i-1]){
                            if(dp[0][i-1][pres]>tmp and pres>0){
                                dp[0][i][pres-1]=dp[0][i-1][pres];
                                curr[0][i][pres-1]=curr[0][i-1][pres];
                                exist[0][i].push_back(pres-1);
                            }
                        }
                        dp[0][i][k]=tmp;
                        curr[0][i][k]=(make_pair(0,i));
                        exist[0][i].push_back(k);
                        pre[0][i]=pre_pair;
                    }else{
                        pre[0][i]=make_pair(-1,-1);
                    }
                    //cout<<0<<" "<<i<<" :"<<tmp<<endl;
                }else{
                    //cout<<0<<" "<<i<<" :"<<endl;
                    for(auto pres:exist[0][i-1]){
                        if(pres>0){
                            //cout<<dp[0][i-1][pres].first<<","<<dp[0][i-1][pres].second<<endl;
                            dp[0][i][pres-1]=dp[0][i-1][pres];
                            curr[0][i][pres-1]=curr[0][i-1][pres];
                            exist[0][i].push_back(pres-1);
                        }
                    }
                }
            }

            for(int i=1;i<m;i++){
                if(v[i][0]!=N){
                    long long tmp=LLONG_MIN;
                    pair<int,int> pre_pair;
                    bool check=false;
                    for(auto pres:exist[i-1][0]){
                        if(dp[i-1][0][pres]+v[i][0]>tmp and pres>0){
                            tmp=dp[i-1][0][pres]+v[i][0];
                            pre_pair=curr[i-1][0][pres];
                            check=true;
                        }
                    }
                    if(check){
                        for(auto pres:exist[i-1][0]){
                            if(dp[i-1][0][pres]>tmp and pres>0){
                                dp[i][0][pres-1]=dp[i-1][0][pres];
                                curr[i][0][pres-1]=curr[i-1][0][pres];
                                exist[i][0].push_back(pres-1);
                            }
                        }
                        dp[i][0][k]=tmp;
                        curr[i][0][k]=(make_pair(i,0));
                        exist[i][0].push_back(k);
                        pre[i][0]=pre_pair;
                    }else{
                        pre[i][0]=make_pair(-1,-1);
                    }
                    ////cout<<i<<" "<<0<<" :"<<tmp<<endl;
                }else{
                    //cout<<i<<" "<<0<<" :"<<tmp<<endl;
                    for(auto pres:exist[i-1][0]){
                        if(pres>0){
                            //cout<<dp[i-1][0][pres].first<<","<<dp[i-1][0][pres].second<<endl;
                            dp[i][0][pres-1]=dp[i-1][0][pres];
                            curr[i][0][pres-1]=curr[i-1][0][pres];
                            exist[i][0].push_back(pres-1);
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
                        vector<long long>tmpk(k+1,LLONG_MIN);
                        vector<pair<int,int>>tmppair(k+1);
                        vector<int>tmpexist;
                        int l=0,u=0;

                        while(l<exist[i][j-1].size() and u<exist[i-1][j].size()){
                            if(exist[i][j-1][l] < exist[i-1][j][u]){
                                tmpexist.push_back(exist[i][j-1][l]);
                                l++;
                            }else if(exist[i][j-1][l] > exist[i-1][j][u]){
                                tmpexist.push_back(exist[i-1][j][u]);
                                u++;
                            }else{
                                tmpexist.push_back(exist[i-1][j][u]);
                                u++;
                                l++;
                            }
                        }
                        while(l<exist[i][j-1].size()){
                            tmpexist.push_back(exist[i][j-1][l]);
                            l++;
                        }
                        while(u<exist[i-1][j].size()){
                            tmpexist.push_back(exist[i-1][j][u]);
                            u++;
                        }


                        for(auto pres:tmpexist){
                            if(dp[i-1][j][pres]!=LLONG_MIN and dp[i-1][j][pres]>=dp[i][j-1][pres]){
                                tmpk[pres]=dp[i-1][j][pres];
                                tmppair[pres]=curr[i-1][j][pres];
                            }else if(dp[i-1][j][pres]!=LLONG_MIN and dp[i-1][j][pres]<dp[i][j-1][pres]){
                                tmpk[pres]=dp[i][j-1][pres];
                                tmppair[pres]=curr[i][j-1][pres];
                            }else if(dp[i][j-1][pres]!=LLONG_MIN){
                                tmpk[pres]=dp[i][j-1][pres];
                                tmppair[pres]=curr[i][j-1][pres];
                            }
                        }
                        for(auto pres:tmpexist){
                            if(tmpk[pres]+v[i][j]>tmp and pres>0){
                                tmp=tmpk[pres]+v[i][j];
                                pre_pair=tmppair[pres];
                                check=true;
                            }
                        }

                        if(check){
                            for(auto pres:tmpexist){
                                if(tmpk[pres]>tmp and pres>0){
                                    dp[i][j][pres-1]=tmpk[pres];
                                    curr[i][j][pres-1]=tmppair[pres];
                                    exist[i][j].push_back(pres-1);
                                }
                            }


                            dp[i][j][k]=tmp;
                            curr[i][j][k]=(make_pair(i,j));
                            exist[i][j].push_back(k);
                            pre[i][j]=pre_pair;
                        }else{
                            pre[i][j]=make_pair(-1,-1);
                        }
                        // //cout<<i<<" "<<j<<" :"<<tmp<<endl;
                        // //cout<<pre[i][j].first<<" "<<pre[i][j].second<<endl;

                    }else{
                        vector<long long>tmpk(k+1,LLONG_MIN);
                        vector<pair<int,int>>tmppair(k+1);
                        vector<int>tmpexist;
                        int l=0,u=0;

                        while(l<exist[i][j-1].size() and u<exist[i-1][j].size()){
                            if(exist[i][j-1][l] < exist[i-1][j][u]){
                                tmpexist.push_back(exist[i][j-1][l]);
                                l++;
                            }else if(exist[i][j-1][l] > exist[i-1][j][u]){
                                tmpexist.push_back(exist[i-1][j][u]);
                                u++;
                            }else{
                                tmpexist.push_back(exist[i-1][j][u]);
                                u++;
                                l++;
                            }
                        }
                        while(l<exist[i][j-1].size()){
                            tmpexist.push_back(exist[i][j-1][l]);
                            l++;
                        }
                        while(u<exist[i-1][j].size()){
                            tmpexist.push_back(exist[i-1][j][u]);
                            u++;
                        }


                        for(auto pres:tmpexist){
                            if(dp[i-1][j][pres]!=LLONG_MIN and dp[i-1][j][pres]>=dp[i][j-1][pres]){
                                tmpk[pres]=dp[i-1][j][pres];
                                tmppair[pres]=curr[i-1][j][pres];
                            }else if(dp[i-1][j][pres]!=LLONG_MIN and dp[i-1][j][pres]<dp[i][j-1][pres]){
                                tmpk[pres]=dp[i][j-1][pres];
                                tmppair[pres]=curr[i][j-1][pres];
                            }else if(dp[i][j-1][pres]!=LLONG_MIN){
                                tmpk[pres]=dp[i][j-1][pres];
                                tmppair[pres]=curr[i][j-1][pres];
                            }
                        }
                        //cout<<i<<" "<<j<<" :"<<endl;
                        for(auto pres:tmpexist){
                            if(pres>0){
                                //cout<<dp[i-1][0][pres].first<<","<<dp[i-1][0][pres].second<<endl;
                                dp[i][j][pres-1]=tmpk[pres];
                                curr[i][j][pres-1]=tmppair[pres];
                                exist[i][j].push_back(pres-1);
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
            auto a=max_element(dp[m-1][n-1].begin(), dp[m-1][n-1].end());
            cout<<*a<<endl;
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
            
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    dp[i][j].clear();
                    curr[i][j].clear();
                    exist[i][j].clear();
                }
                dp[i].clear();
                curr[i].clear();
                exist[i].clear();
            }
            dp.clear();
            curr.clear();
            exist.clear();

        }
    }
    return 0;
}