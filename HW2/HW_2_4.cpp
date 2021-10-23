#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <unordered_map>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int cases,flag,n;
    long x;
    while(cin>>cases>>flag){
        for(int c=0;c<cases;c++){
            cin>>n;
            vector<long> v;
            for(int i=0;i<n;i++){
                cin>>x;
                v.push_back(x);
            }
            vector<long> tmpv;
            bool p;
            if(v[0]>0){
                p=true;
            }else{
                p=false;
            }
            tmpv.push_back(v[0]);
            long maxlen=1;
            for(int i=1;i<n;i++){
                if((v[i]<0 and p) or (v[i]>0 and !p)){
                    maxlen++;
                    p=!p;
                    tmpv.push_back(v[i]);
                }else{
                    tmpv[tmpv.size()-1]=max(tmpv[tmpv.size()-1],v[i]);
                }
            }
            long currsum=0;
            for(auto i:tmpv){
                currsum+=i;
            }

            vector<long> ans(n);
            unordered_set<long> used;
            priority_queue< vector<long> , vector<vector<long>> , greater<vector<long>> > pq; 
            unordered_map<long,long> left;
            unordered_map<long,long> right;

            for(int i=0;i<maxlen-1;i++){
                pq.push({tmpv[i]+tmpv[i+1],i,i+1});      
                right[i]=i+1;
                left[i+1]=i;        
            }pq.push({tmpv[0]+tmpv[maxlen-1],maxlen-1,0}); 
            right[maxlen-1]=0;
            left[0]=maxlen-1;
            ans[maxlen-1]=currsum;

            for(int i=maxlen-3;i>=0;i-=2){

                vector<long> tmp=pq.top();
                while(used.count(tmp[1]) or used.count(tmp[2])){
                    pq.pop();
                    tmp=pq.top();
                }pq.pop();
                used.insert(tmp[1]);
                used.insert(tmp[2]);
                currsum-=tmp[0];
                right[left[tmp[1]]]=right[tmp[2]];
                left[right[tmp[2]]]=left[tmp[1]];
                pq.push({tmpv[left[tmp[1]]]+tmpv[right[tmp[2]]],left[tmp[1]],right[tmp[2]]}); 
                ans[i]=currsum;
            }
            if(maxlen>1 and !flag){
                vector<long> newv;
                if(tmpv[0]<tmpv[tmpv.size()-1]){
                    for(int i=0;i<tmpv.size()-1;i++){
                        newv.push_back(tmpv[i+1]);
                    }
                }else{
                    for(int i=0;i<tmpv.size()-1;i++){
                        newv.push_back(tmpv[i]);
                    }
                }
                currsum=0;
                for(auto i:newv){
                    currsum+=i;
                }
                used.clear();
                while (!pq.empty()) pq.pop(); 
                for(int i=0;i<maxlen-2;i++){
                    pq.push({newv[i]+newv[i+1],i,i+1});      
                    right[i]=i+1;
                    left[i+1]=i;        
                }pq.push({newv[0]+newv[maxlen-2],maxlen-2,0}); 
                right[maxlen-2]=0;
                left[0]=maxlen-2;
                ans[maxlen-2]=currsum;


                for(int i=maxlen-4;i>=0;i-=2){
                    vector<long> tmp=pq.top();
                    while(used.count(tmp[1]) or used.count(tmp[2])){
                        pq.pop();
                        tmp=pq.top();
                    }pq.pop();
                    used.insert(tmp[1]);
                    used.insert(tmp[2]);
                    currsum-=tmp[0];
                    right[left[tmp[1]]]=right[tmp[2]];
                    left[right[tmp[2]]]=left[tmp[1]];
                    pq.push({newv[left[tmp[1]]]+newv[right[tmp[2]]],left[tmp[1]],right[tmp[2]]}); 
                    ans[i]=currsum;
                }
                
            }for(auto i:ans){
                cout<<i<<" ";
            }
        }
    }
    return 0;
}