#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    long long ans,tmp,x,y;
    while(cin>>n){
        vector<long> v(n);
        for(int i=0;i<n;i++){
            cin>>x;
            v[i]=x;
        }
        int l=v.size();
        vector<vector<long>> dp(l,vector<long>(l,0));

        //for(auto i:dp){
        //    for(auto j:i){
        //        cout<<j<<" ";
        //    }cout<<endl;
        //}
        cout<<dp[0][l-1];
        
        
    }
    return 0;
}