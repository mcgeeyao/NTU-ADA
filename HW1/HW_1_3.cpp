#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
bool comp_y(pair<int,int> a,pair<int,int> b){
    return a.second>b.second;
}
bool comp_x(pair<int,int> a,pair<int,int> b){
    return a.first<b.first;
}
long long dc(vector<pair<int,int>>& points,int left,int right){

    long long ans=0;
    if(left>=right){
        return 0;
    }
    int mid=(left+right)/2;
    int bound=points[mid].first;

    long long lans=dc(points,left,mid);
    long long rans=dc(points,mid+1,right);
    vector<pair<int,int>> tmp(right-mid,pair<int,int>());
    for(int i=0;i<right-mid;i++){
        tmp[i]=points[mid+i+1];
    }
    int m=right-mid-1;
    int n=mid;
    int k=right;
    while(n>=left and m>=0){
        if(points[n].second < tmp[m].second){
            points[k--] = points[n--];
        }else{
            points[k--] = tmp[m--];
        }      
    }
    while(m>=0){
        points[k--] = tmp[m--];
    }
    vector<pair<int,int>>leftstk,rightstk;//filled first(x)
    for(int i=left;i<=right;i++){
        if (points[i].first<=bound){
            while(leftstk.size()>0 and points[i].first>leftstk[leftstk.size()-1].first){
                leftstk.pop_back();
            }
            int upbd;
            if(leftstk.size()>0){
                upbd=leftstk[leftstk.size()-1].second;
            }else{
                upbd=1000000000;
            }
            leftstk.push_back(points[i]);
            if(!rightstk.empty()){
                vector<pair<int,int>>::iterator a=upper_bound(rightstk.begin(),rightstk.end(),make_pair(0,upbd),comp_y);
                ans+=rightstk.end()-a;
            }
        }else{
            while(rightstk.size()>0 and points[i].first<rightstk[rightstk.size()-1].first){
                rightstk.pop_back();
            }
            int upbd;
            if(rightstk.size()>0){
                upbd=rightstk[rightstk.size()-1].second;
            }else{
                upbd=1000000000;
            }
            rightstk.push_back(points[i]);
            if(!leftstk.empty()){
                vector<pair<int,int>>::iterator a=upper_bound(leftstk.begin(),leftstk.end(),make_pair(0,upbd),comp_y);
                ans+=leftstk.end()-a;
            }
        }
    }
    return ans+lans+rans;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,x,y;
    long long ans,tmp;
    while(cin>>n){
        vector<pair<int,int>> points;
        for(int i=0;i<n;i++){
            cin>>x>>y;
            points.push_back(make_pair(x,y));
        }
        sort(points.begin(),points.end(),comp_x);
        ans=dc(points,0,points.size()-1);
        cout<<ans<<endl;
    }
    return 0;
}