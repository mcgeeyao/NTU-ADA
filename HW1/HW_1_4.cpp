#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>
using namespace std;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,numcase,x,flag,cases;
    long long ans,tmp;
    while(cin>>numcase>>flag){
        if(flag){
            for(int cases=0;cases<numcase;cases++){
                vector<int> v;
                cin>>n;
                for(int i=0;i<n;i++){
                    cin>>x;
                    v.push_back(x);
                }
                long long negsum=-9000000000000000000,possum=-9000000000000000000;
                ans=-9000000000000000000;
                vector<int> npath,ppath,anspath;
                for(int i=0;i<n;i++){
                    if(v[i]>0){
                        if(v[i]>possum){
                            ppath={i};
                            possum=v[i];
                        }
                        if(negsum+v[i]>possum){
                            ppath.assign(npath.begin(),npath.end());
                            ppath.push_back(i);
                            possum=negsum+v[i];
                        }
                    }else if(v[i]<0){
                        if(v[i]>negsum){
                            npath={i};
                            negsum=v[i];
                        }
                        if(possum+v[i]>negsum){
                            npath.assign(ppath.begin(),ppath.end());
                            npath.push_back(i);
                            negsum=possum+v[i];
                        }
                    }else{
                        if(0>negsum){
                            npath={i};
                            negsum=0;
                        }
                        if(possum>negsum){
                            npath.assign(ppath.begin(),ppath.end());
                            npath.push_back(i);
                            negsum=possum;
                        }
                        if(0>possum){
                            ppath={i};
                            possum=0;
                        }
                        if(negsum>possum){
                            ppath.assign(npath.begin(),npath.end());
                            ppath.push_back(i);
                            possum=negsum;
                        }
                    }
                    if(negsum>ans){
                        anspath.assign(npath.begin(),npath.end());
                        ans=negsum;
                    }if(possum>ans){
                        anspath.assign(ppath.begin(),ppath.end());
                        ans=possum;
                    }
                }cout<<ans<<endl;
                cout<<anspath.size();
                for(int i:anspath){
                    cout<<" "<<i+1;
                }cout<<endl;
            }
        }else{
            for(int cases=0;cases<numcase;cases++){
                vector<int> v;
                cin>>n;
                for(int i=0;i<n;i++){
                    cin>>x;
                    v.push_back(x);
                }
                long long negsum=-9000000000000000000,possum=-9000000000000000000;
                ans=-9000000000000000000;
                for(int i=0;i<n;i++){
                    if(v[i]>0){
                        possum=max(possum,(long long)v[i]);
                        possum=max(possum,negsum+v[i]);
                    }else if(v[i]<0){
                        negsum=max(negsum,(long long)v[i]);
                        negsum=max(possum+v[i],negsum);
                    }else{
                        negsum=max(possum,negsum);
                        negsum=max((long long)0,negsum);
                        possum=max(possum,negsum);
                        possum=max(possum,(long long)0);
                    }
                    ans=max(ans,possum);
                    ans=max(ans,negsum);
                }cout<<ans<<endl;
            }
        }
        
        
    }
    return 0;
}