#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <climits>
#include <assert.h>
#define print(v)\
for (auto i:v)\
cout<<i<<" ";\
cout<<endl;
using namespace std;


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m,x,y;
    
    while(cin>>n>>m){
        if(n==2){
            cin>>x>>y;
            cout<<x+y;
        }else{
        vector<long long> list(n);
        for(int i=0;i<n;i++){
            cin>>x;
            list[i]=x;
        }
        long long a=0,tmp;
        for(auto i:list)a+=i;
        vector<long long> b(n),c(n);
        for(int i=0;i<n;i++){
            if(i){
                tmp=list[i]*((list[i-1]&list[i])^(list[i]|list[(i+1)%n])^(list[i-1]+list[(i+1)%n]));
                b[i]=tmp;
                a+=tmp;
            }else{
                tmp=list[i]*((list[n-1]&list[i])^(list[i]|list[i+1])^(list[n-1]+list[i+1]));
                b[i]=tmp;
                a+=tmp;
            }
            
            tmp=-abs(list[i]-list[(i+1)%n]);
            c[i]=tmp;
            a+=tmp;
        }
        // print(b)
        // print(c)


        vector<long long> absline(n-1),XORline(n-2);
        vector<vector<long long> > OPTdp(n-1,vector<long long> (m-1,LLONG_MIN)),endAtDP(n-1,vector<long long> (m-1,LLONG_MIN));
        int firstCut;
        vector<bool> vis(n,false);
        long long res=LLONG_MIN;
        for (int ran=0;ran<min(5*n/m,n-m+2);ran++){
            long long tmpres=0;
            firstCut=rand()%n;
            while(vis[firstCut])firstCut=rand()%n;
            // cout<<(firstCut);
            vis[firstCut]=true;
            // cout<<b[firstCut]<<" "<<b[(firstCut+1)%n]<<" "<<c[firstCut]<<endl;
            tmpres+=b[firstCut];
            tmpres+=b[(firstCut+1)%n];
            tmpres+=c[firstCut];
            for(int i=0;i<n-1;i++)absline[i]=c[(firstCut+i+1)%n];
            for(int i=0;i<n-2;i++)XORline[i]=b[(firstCut+i+2)%n];

            endAtDP[0][0]=absline[0]+XORline[0];
            OPTdp[0][0]=absline[0]+XORline[0];
            // print(absline)
            // print(XORline)

            for(int i=1;i<n-2;i++){
                endAtDP[i][0]=XORline[i-1]+XORline[i]+absline[i];
                OPTdp[i][0]=max(OPTdp[i-1][0],endAtDP[i][0]);
            }
            endAtDP[1][1]=endAtDP[0][0]+XORline[1]+absline[1];
            OPTdp[1][1]=max(OPTdp[0][1],endAtDP[1][1]);
            for(int i=2;i<n-2;i++){
                for(int j=1;j<min(i+1,m-1);j++){
                    endAtDP[i][j]=max(OPTdp[i-2][j-1]+XORline[i-1]+XORline[i]+absline[i],endAtDP[i-1][j-1]+XORline[i]+absline[i]);
                    OPTdp[i][j]=max(OPTdp[i-1][j],endAtDP[i][j]);
                }
            }
            endAtDP[n-2][0]=XORline[n-3]+absline[n-2];
            OPTdp[n-2][0]=max(OPTdp[n-3][0],endAtDP[n-2][0]);
            for(int j=1;j<m-1;j++){
                endAtDP[n-2][j]=max(OPTdp[n-2-2][j-1]+XORline[n-2-1]+absline[n-2],endAtDP[n-2-1][j-1]+absline[n-2]);
                OPTdp[n-2][j]=max(OPTdp[n-2-1][j],endAtDP[n-2][j]);
            }
            res=max(res,tmpres+OPTdp[n-2][m-2]);
            // cout<<"這"<<tmpres+OPTdp[n-2][m-2];
            // for(auto aa:OPTdp){
            //     print(aa)
            // }
        }
        // cout<<a<<endl;
        cout<<a-res;


        }
        




    }
    return 0;
}