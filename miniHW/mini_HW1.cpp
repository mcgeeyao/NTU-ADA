#include <iostream>
#include <vector>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,x,y,z;
    long ans,tmp,vi,currmax;
    
    while(cin>>n>>x>>y>>z){
        vector<long> v,prefixsum;
        for(int i=0;i<n;i++){
            cin>>vi;
            v.push_back(vi);
        }
        currmax=x*v[0]+z*v[1];
        ans=currmax;
        for(int i=2;i<n;i++){
            currmax=max(currmax-z*v[i-1]+y*v[i-1]+z*v[i],x*v[i-1]+z*v[i]);
            ans=max(ans,currmax);
        }
        
        cout<<ans<<endl;
	
    }return 0;
}