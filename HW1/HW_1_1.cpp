#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#define MOD 998244353
using namespace std;
long long modulo(int a, int b, long long n){
    long long x=1, y=a; 
    while (b > 0) {
        if (b%2 == 1) {
            x = (x*y) % n;
        }
        y = (y*y) % n;
        b /= 2;
    }
    return x % n;
}
int hanoi(vector<vector<int>>& tower,int n,int start,int target){
    if(n==0){
        return 0;
    }
    if(tower[start].size()>0 and tower[start][tower[start].size()-1]==n){
        tower[start].pop_back();
        long long tmp=hanoi(tower,n-1,start,~(start|target)&3);
        if(tmp==-1)return tmp;
        tmp%=MOD;
        long long tmp2=modulo(2,n-1,MOD);
        return tmp+tmp2;
    }else if(tower[target].size()>0 and tower[target][tower[target].size()-1]==n){
        tower[target].pop_back();
        long long tmp=hanoi(tower,n-1,~(start|target)&3,target);
        if(tmp==-1)return tmp;
        tmp%=MOD;
        return tmp;
    }else{
        return -1;
    }
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,x,y;
    long long ans;
    while(cin>>n){
        vector<vector<int>> tower(3,vector<int>());
        for(int i=0;i<3;i++){
            cin>>x;
            for(int j=0;j<x;j++){
                cin>>y;
                tower[i].push_back(y);
            }
            reverse(tower[i].begin(),tower[i].end());
        }
        ans=hanoi(tower,n,0,2);
        if(ans==-1)cout<<ans<<endl;
        else{ans%=MOD;
        cout<<ans<<endl;}
	
    }
    return 0;
}