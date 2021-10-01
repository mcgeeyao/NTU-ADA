#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
bool comp(vector<int> a,vector<int> b){
    return a[1]>b[1];
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,a,b,c,x,y;
    long long ans,tmp;
    while(cin>>n>>a>>b>>c){
        vector<int> pa(n),pb(n),z(n);
        vector<vector<int>> p(n,vector<int>(2));
        for(int i=0;i<n;i++){
            cin>>x>>y;
            p[i]={i,x};
            z.push_back(y);
        }
        cout<<n<<endl;
        for(auto i:p){
            cout<<i[0]<<i[1]<<" ";
        }
        sort(p.begin(),p.end(),comp);
        for(int i=0;i<n;i++){
            pa[i]=p[i][1]*a;
        }
        for(int i=0;i<n;i++){
            pb[i]=p[i][1]*b+c;
        }
        //ans=0;
        tmp=0;
        //for(int i=0;i<n;i++){

        //}
    }
    return 0;
}