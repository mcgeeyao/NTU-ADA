#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int gcd(int a,int b){
    while( b!=0 ){
        int t = b;
        b = a%b;
        a = t;
    }
    return a;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,x;
    long ans;
    while(cin>>n){
        vector<int> v(n);
        for(int i=0;i<n;i++){
            cin>>x;
            v[i]=x;
        }
        int l=v.size();
        vector<vector<long>> dp(l,vector<long>(l,0));
        vector<vector<int>> gcdtable(l,vector<int>(l,0));
        for(int i=0;i<l;i++){
            for(int j=i+1;j<l;j++){
                gcdtable[i][j]=gcd(v[i],v[j]);
            }
        }
        for(int i=0;i<l-1;i++){
            if(gcdtable[i][i+1]>1){
                dp[i][i+1]=gcdtable[i][i+1];
            }
        }
        for(int i=0;i<l-2;i++){
            if(gcdtable[i][i+1]>1 and gcdtable[i+1][i+2]>1 and gcdtable[i][i+2]>1){
                dp[i][i+2]=gcdtable[i][i+1]+gcdtable[i+1][i+2];
            }
        }
        for(int k=3;k<l;k++){
            for(int i=0;i<l-k;i++){
                long tmp=0;
                
                if(gcdtable[i][i+k]>1){
                    //1,(),1,(),1
                    for(int a=2;a<k-1;a++){
                        if(dp[i+1][i+a-1]>1 and dp[i+a+1][i+k-1]>1){
                            if(gcdtable[i][i+a]>1 and gcdtable[i+a][i+k]>1){
                                tmp=max(tmp,dp[i+1][i+a-1]+dp[i+a+1][i+k-1]+gcdtable[i][i+a]+gcdtable[i+a][i+k]);
                            }
                        }
                    }
                    //1,(),2
                    if(dp[i+1][i+k-2]>1){
                        if(gcdtable[i][i+k-1]>1 and gcdtable[i+k-1][i+k]>1){
                            tmp=max(tmp,dp[i+1][i+k-2]+gcdtable[i][i+k-1]+gcdtable[i+k-1][i+k]);
                        }
                    }
                    //2,(),1
                    if(dp[i+2][i+k-1]>1){
                        if(gcdtable[i][i+1]>1 and gcdtable[i+1][i+k]>1){
                            tmp=max(tmp,dp[i+2][i+k-1]+gcdtable[i][i+1]+gcdtable[i+1][i+k]);
                        }
                    }
                    //1,(),1
                    if(dp[i+1][i+k-1]>1){
                        tmp=max(tmp,dp[i+1][i+k-1]+gcdtable[i][i+k]);
                    }
                }
                //(),()
                for(int a=1;a<k-1;a++){
                    if(dp[i][i+a]>1 and dp[i+a+1][i+k]>1){
                        tmp=max(tmp,dp[i][i+a]+dp[i+a+1][i+k]);
                    }
                }
                dp[i][i+k]=tmp;
            }
        }
        //for(auto i:dp){
        //    for(auto j:i){
        //        cout<<j<<" ";
        //    }cout<<endl;
        //}
        if(dp[0][l-1]){
            cout<<dp[0][l-1];
        }else{
            cout<<-1;
        }
        
        
    }
    return 0;
}