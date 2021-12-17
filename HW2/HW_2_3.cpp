//greedy 疊疊樂

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <queue>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,x,y,z,w;
    long long ans;
    while(cin>>n){
        ans=0;
        vector<vector<int>> v(n,vector<int>(4));
        unordered_set<int>tmpPs;
        for(int i=0;i<n;i++){
            cin>>x>>y>>z>>w;
            v[i]={x,y,z,w};
            tmpPs.insert(w);
        }
        vector<int> Ps={0};
        for(auto i:tmpPs){
            Ps.push_back(i);
        }sort(Ps.begin(),Ps.end());
        sort(v.begin(),v.end());
        // for(auto i:Ps){
        //     cout<<i<<" ";
        // }cout<<endl;
        for(int i=1;i<Ps.size();i++){
            long result=0;
            vector<vector<int>> tmpv;
            priority_queue< pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > pq; 
            int maxhour=0;
            for(auto task:v){
                if(task[3]>=Ps[i]){
                    tmpv.push_back(task);
                    maxhour=max(maxhour,task[1]);
                }
            }
            int ind=0;
            int hour=tmpv[0][0];
            while (hour<=maxhour){
                while (ind<tmpv.size() and tmpv[ind][0]<=hour){
                    pq.push(make_pair(tmpv[ind][1],tmpv[ind][2]));
                    ind++;
                }
                while(!pq.empty() and pq.top().first<hour or pq.top().second==0){
                    pq.pop();
                }
                if(ind==tmpv.size()){
                    if(pq.empty()){
                        break;
                    }else{
                        pair<int,int> a=pq.top();
                        pq.pop();
                        if(a.first-hour+1<a.second){
                            result+=a.first-hour+1;
                            hour+=a.first-hour+1;
                        }else{
                            result+=a.second;
                            hour+=a.second;
                        }
                    }
                }else{
                    if(pq.empty()){
                        hour=tmpv[ind][0];
                    }else{
                        pair<int,int> a=pq.top();
                        pq.pop();
                        int remain_time=a.first-hour+1;
                        int remain_job=a.second;
                        int next_start=tmpv[ind][0];
                        int tmp=min(remain_time,remain_job);
                        tmp=min(tmp,next_start-hour);
                        if(tmp==remain_time or tmp==remain_job){
                            result+=tmp;
                            hour+=tmp;
                        }else{
                            result+=tmp;
                            hour=next_start;
                            a.second-=tmp;
                            pq.push(a);
                        }
                    }
                }
            }
            v=tmpv;
            ans+=result*(Ps[i]-Ps[i-1]);
        }
        cout<<ans<<endl;








    }
    return 0;
}