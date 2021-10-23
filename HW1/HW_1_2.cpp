#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int a,b,c;
bool comp_z(pair<long long,long long> a,pair<long long,long long> b){
    return a.second>b.second;
}
bool comp_p(pair<long long,long long> a,pair<long long,long long> b){
    return a.first>b.first;
}
long long dc(vector<pair<long long,long long>>& v,int left,int right){
    long long ans=0;
    if(left>=right){
        return 0;
    }
    int mid=(left+right)/2;
    while(mid<right and v[mid].second==v[mid+1].second){
        mid++;
    }if(mid==right){
        while(mid>left and v[mid].second==v[mid-1].second){
            mid--;
        }
        if(mid==left){
            sort(v.begin()+left,v.begin()+right+1,comp_p);
            return 0;
        }mid--;
    }
    long long lans=dc(v,left,mid);
    long long rans=dc(v,mid+1,right);
    int ind=left;
    for(int i=mid+1;i<=right;i++){
        while(ind<=mid and a*v[ind].first>b*v[i].first+c){
            ind++;
        }
        ans+=(ind-left);
    }
    vector<long long> tmp(right-mid);
    for(int i=0;i<right-mid;i++){
        tmp[i]=v[mid+i+1].first;
    }
    int m=right-mid-1;
    int n=mid;
    int k=right;
    while(n>=left and m>=0){
        if(v[n].first < tmp[m]){
            v[k--].first = v[n--].first;
        }else{
            v[k--].first = tmp[m--];
        }      
    }
    while(m>=0){
        v[k--].first = tmp[m--];
    }
        
    /*
    cout<<left<<" "<<right<<endl;
    for(auto i:v){
        cout<<i.first<<" ";
    }cout<<endl;*/
    //sort(v.begin()+left,v.begin()+right+1,comp_p);
    return ans+lans+rans;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    long long ans,tmp,x,y;
    while(cin>>n>>a>>b>>c){
        vector<pair<long long,long long>> v(n,pair<long long,long long>());
        for(int i=0;i<n;i++){
            cin>>x>>y;
            v[i]=make_pair(x,y);
        }
        sort(v.begin(),v.end(),comp_z);
        ans=dc(v,0,v.size()-1);
        cout<<ans<<endl;
        
    }
    return 0;
}