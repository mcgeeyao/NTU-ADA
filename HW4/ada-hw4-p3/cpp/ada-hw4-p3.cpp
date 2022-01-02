#include "ada-hw4-p3.h"
#include <iostream>
#define print(v)\
for (auto i:v)\
cout<<i<<" ";\
cout<<endl;
using namespace std;

vector<int> contest,conceal,origin,pairs;
vector<bool> inconceal;

vector<int> init(int N) {
    origin.clear();
    contest.clear();
    conceal.clear();
    pairs.clear();
    inconceal.clear();
    for (int i = 0; i < N; ++i){
        origin.push_back(i);
        if(contest.empty()){
            contest.push_back(i);
            inconceal.push_back(false);
            pairs.push_back(-1);
        }
        else{
            if(!compare(contest[contest.size()-1],i)){
                conceal.push_back(contest.back());
                conceal.push_back(i);
                inconceal[contest.back()]=true;
                inconceal.push_back(true);
                pairs[contest.back()]=i;
                pairs.push_back(contest.back());
                contest.pop_back();
            }else{
                inconceal.push_back(false);
                pairs.push_back(-1);
                contest.push_back(i);
            }
        }
    }
    
    // print(origin)
    // print(contest)
    // print(conceal)
    // print(pairs)
    // print(inconceal)
    return conceal;
}

vector<int> insert(int p, int id) {
    int left=p-1,right=p;
    bool leftcon=true,rightcon=true;
    while(left>=0 and inconceal[left]==true)left--;
    while(right<inconceal.size() and inconceal[right]==true)right++;
    if(left>=0)leftcon=compare(origin[left],id);
    if(right<inconceal.size())rightcon=compare(id,origin[right]);
    if(leftcon and rightcon){
        inconceal.insert(inconceal.begin()+p,false);
        pairs.insert(pairs.begin()+p,-1);
    }else if(!leftcon){
        inconceal[left]=true;
        pairs[left]=id;
        inconceal.insert(inconceal.begin()+p,true);
        pairs.insert(pairs.begin()+p,origin[left]);
        conceal.push_back(origin[left]);
        conceal.push_back(id);
    }else{
        inconceal[right]=true;
        pairs[right]=id;
        inconceal.insert(inconceal.begin()+p,true);
        pairs.insert(pairs.begin()+p,origin[right]);
        conceal.push_back(origin[right]);
        conceal.push_back(id);
    }
    origin.insert(origin.begin()+p, id);
    return conceal;
}

vector<int> remove(int p) {
    int id=origin[p];
    if(inconceal[p]){
        int tmp=0;
        while(tmp<conceal.size() and conceal[tmp]!=id)tmp++;
        conceal.erase(conceal.begin()+tmp);

        int pid=pairs[p];

        int pairpos=0;
        while(pairpos<origin.size() and origin[pairpos]!=pid)pairpos++;
        int pairfind=0;
        while(pairfind<conceal.size() and conceal[pairfind]!=pid)pairfind++;

        if(pairpos<origin.size()){
            int left=pairpos-1,right=pairpos;
            bool leftcon=true,rightcon=true;
            while(left>=0 and inconceal[left]==true)left--;
            while(right<inconceal.size() and inconceal[right]==true)right++;
            if(left>=0)leftcon=compare(origin[left],pid);
            if(right<inconceal.size())rightcon=compare(pid,origin[right]);

            if(leftcon and rightcon){
                inconceal[pairpos]=false;
                conceal.erase(conceal.begin()+pairfind);
                pairs[pairpos]=-1;
            }else if(!leftcon){
                inconceal[left]=true;
                pairs[left]=pid;
                pairs[pairpos]=origin[left];
                conceal.push_back(origin[left]);
            }else{
                inconceal[right]=true;
                pairs[right]=pid;
                pairs[pairpos]=origin[right];
                conceal.push_back(origin[right]);
            }

        }
    }
    pairs.erase(pairs.begin() + p);
    inconceal.erase(inconceal.begin() + p);
    
    origin.erase(origin.begin() + p);

    return conceal;
}
