#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#define print(v)\
for (int i=0;i<v.size();i++)\
cout<<v[i]<<"\n";\
cout<<endl;
using namespace std;
long long cn2(long long n){
    return n*(n-1)/2;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n,q,op,pos;
    long long x,y;
    long long res;
    map<long long,long long>::iterator it;
    set<pair<int,int>>::iterator sit;
    while(cin>>n>>q){
        map<long long,long long> line; //pos,number
        unordered_map<int,map<long long,long long>> movelist;
        vector<pair<int,int>> cats(n+1);

        for(int i=1;i<n+1;i++){
            cin>>pos;
            line[pos]++;
            cats[i]=make_pair(0,pos);
        }
        vector<long long> reslist;
        res=0;
        for(auto i:line){
            res+=cn2(i.second);
        }
        for(int c=0;c<q;c++){
            cin>>op>>x>>y;
            if(op-1){
                int time=cats[x].first;
                int currpos=cats[x].second;
                int time1=time;
                int currpos1=currpos;
                it=movelist[currpos].lower_bound(time);
                while(it!=movelist[currpos].end()){
                    time=it->first;
                    currpos=it->second;
                    it=movelist[currpos].lower_bound(time);
                }
                res+=cn2(line[currpos]-1)-cn2(line[currpos]);
                line[currpos]--;
                if(line[currpos]==0){
                    line.erase(currpos);
                }
                res+=cn2(line[y]+1)-cn2(line[y]);
                line[y]++;
                cats[x]=make_pair(c+1,y);
                reslist.push_back(res);

                it=movelist[currpos1].lower_bound(time1);
                while(it!=movelist[currpos1].end()){
                    movelist[currpos1][time1]=currpos;
                    time1=it->first;
                    currpos1=it->second;
                    it=movelist[currpos1].lower_bound(time1);
                }
            }else{
                long long lost=0;
                long long get=0;
                for(it=line.lower_bound(x-y);it!=line.end();it++){
                    if(it->first>x+y)break;
                    lost+=cn2(it->second);
                    get+=it->second;
                    movelist[it->first].insert(make_pair(c+1,x));
                }line.erase(line.lower_bound(x-y),line.upper_bound(x+y));
                if(get){
                    res-=lost;
                    res+=cn2(get);
                    line[x]=get;
                }reslist.push_back(res);
            }
        }
        print(reslist)
        
	
    }return 0;
}