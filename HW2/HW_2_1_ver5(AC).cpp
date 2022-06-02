//triangle DP

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

long long N = -456456456457;
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k, m, n, cases;
    string x;
    while(cin >> cases){
        for (int c = 0;c<cases;c++){
            cin >> m >> n >> k;
            vector<vector<long long>> v(m, vector<long long>(n, LLONG_MIN));
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    cin >> x;
                    if(x != "X"){
                        v[i][j] = stol(x);
                    }
                }
            }
            vector<int> log32k;
            if (k > 1) {
                int tmp = k;
                log32k.push_back(tmp);
                while (tmp > 2){
                    tmp -= tmp / 3;
                    log32k.push_back(tmp);
                }
                log32k.push_back(1);
            } else {
                log32k.push_back(1);
            }
            int ksize = log32k.size();
            reverse(log32k.begin(), log32k.end());
            // for(auto i:log32k){
            //     cout<<i<<" ";
            // }
            vector<vector<vector<long long>>>dp(m, vector<vector<long long>>(n, vector<long long>(ksize, LLONG_MIN)));
            vector<vector<vector<pair<int, int>>>>pre(m, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(ksize)));
            for (int i = 0;i < ksize; i++) {
                dp[0][0][i] = 0;
            }
            for (int i = 1;i < m; i++) {
                dp[i][0][0] = dp[i-1][0][ksize-1];
                pre[i][0][0] = make_pair(i-1, 0);
                
                if (k > 1) {
                    if (dp[i - 1][0][0] > dp[i][0][0]) {
                        dp[i][0][1] = dp[i - 1][0][0];
                        pre[i][0][1] = pre[i - 1][0][0];
                    } else {
                        dp[i][0][1] = dp[i][0][0];
                        pre[i][0][1] = pre[i][0][0];
                    }
                    for (int l = 2; l < ksize; l++) {
                        long long tmp3;
                        if (i - log32k[l] / 3 < 0) {
                            tmp3 = LLONG_MIN;
                        } else {
                            tmp3 = dp[i - log32k[l] / 3][0][l - 1];
                        }
                        long long tmp = max(dp[i][0][l - 1], tmp3);
                        if (tmp == dp[i][0][l - 1]) {
                            dp[i][0][l] = dp[i][0][l - 1];
                            pre[i][0][l] = pre[i][0][l - 1];
                        } else {
                            dp[i][0][l] = dp[i - log32k[l] / 3][0][l - 1];
                            pre[i][0][l] = pre[i - log32k[l] / 3][0][l - 1];
                        }
                    }  
                }
                
                if (dp[i][0][ksize - 1] != LLONG_MIN) {
                    dp[i][0][ksize - 1] += v[i][0];
                }
                if (v[i][0] == LLONG_MIN) {
                    dp[i][0][ksize - 1] = LLONG_MIN;
                }
            }
            for (int i = 1; i < n; i++) {
                if (k == 1 && v[0][i] == LLONG_MIN) {
                    dp[0][i][0] = LLONG_MIN;
                } else {
                    dp[0][i][0] = dp[0][i - 1][ksize - 1];
                    pre[0][i][0] = make_pair(0, i - 1);
                }
                
                if (k > 1) {
                    if (dp[0][i - 1][0] > dp[0][i][0]) {
                        dp[0][i][1] = dp[0][i - 1][0];
                        pre[0][i][1] = pre[0][i - 1][0];
                    } else {
                        dp[0][i][1] = dp[0][i][0];
                        pre[0][i][1] = pre[0][i][0];
                    }
                    
                    for (int l = 2;l < ksize; l++) {
                        long long tmp3;
                        if (i - log32k[l] / 3 < 0) {
                            tmp3 = LLONG_MIN;
                        } else {
                            tmp3 = dp[0][i - log32k[l] / 3][l - 1];
                        }
                        long long tmp = max(dp[0][i][l - 1], tmp3);
                        if (tmp == dp[0][i][l - 1]) {
                            dp[0][i][l] = dp[0][i][l - 1];
                            pre[0][i][l] = pre[0][i][l - 1];
                        } else {
                            dp[0][i][l] = dp[0][i - log32k[l] / 3][l - 1];
                            pre[0][i][l] = pre[0][i - log32k[l] / 3][l - 1];
                        }
                    }
                }
                
                if (dp[0][i][ksize - 1] != LLONG_MIN) {
                    dp[0][i][ksize - 1] += v[0][i];
                }
                if (v[0][i] == LLONG_MIN) {
                    dp[0][i][ksize - 1] = LLONG_MIN;
                }
            }
            for (int i = 1; i < m; i++) {
                for (int j = 1; j < n; j++) {
                    if (dp[i - 1][j][ksize - 1] == LLONG_MIN && dp[i][j - 1][ksize - 1] == LLONG_MIN) {
                        dp[i][j][0] = LLONG_MIN;
                    } else if (dp[i - 1][j][ksize - 1]>dp[i][j - 1][ksize - 1]) {
                        dp[i][j][0] = dp[i - 1][j][ksize - 1];
                        pre[i][j][0] = make_pair(i - 1, j);
                    } else {
                        dp[i][j][0] = dp[i][j - 1][ksize - 1];
                        pre[i][j][0] = make_pair(i, j - 1);
                    }
                    
                    if (k > 1) {
                        long long tmp = max(dp[i - 1][j][0], dp[i][j - 1][0]);
                        tmp = max(tmp, dp[i][j][0]);
                        if (tmp == dp[i - 1][j][0]) {
                            dp[i][j][1] = dp[i - 1][j][0];
                            pre[i][j][1] = pre[i - 1][j][0];
                        } else if (tmp =  = dp[i][j - 1][0]) {
                            dp[i][j][1] = dp[i][j - 1][0];
                            pre[i][j][1] = pre[i][j - 1][0];
                        } else {
                            dp[i][j][1] = dp[i][j][0];
                            pre[i][j][1] = pre[i][j][0];
                        }
                        
                        for (int l = 2; l < ksize; l++) {
                            long long tmp2;
                            long long tmp3;
                            if (j - log32k[l] / 3 < 0) {
                                tmp2 = LLONG_MIN;
                            } else {
                                tmp2 = dp[i][j - log32k[l]/3][l - 1];
                            }
                            if (i - log32k[l] / 3 < 0) {
                                tmp3 = LLONG_MIN;
                            } else {
                                tmp3 = dp[i - log32k[l] / 3][j][l - 1];
                            }
                            long long tmp = max(dp[i][j][l - 1], tmp2);
                            tmp = max(tmp, tmp3);
                            if (tmp == dp[i][j][l - 1]) {
                                dp[i][j][l] = dp[i][j][l - 1];
                                pre[i][j][l] = pre[i][j][l - 1];
                            } else if (tmp =  = tmp2) {
                                dp[i][j][l] = dp[i][j - log32k[l] / 3][l - 1];
                                pre[i][j][l] = pre[i][j - log32k[l] / 3][l - 1];
                            } else {
                                dp[i][j][l] = dp[i - log32k[l]/3][j][l - 1];
                                pre[i][j][l] = pre[i - log32k[l]/3][j][l - 1];
                            }
                        }
                    }
                    
                    if (dp[i][j][ksize - 1] != LLONG_MIN) {
                        dp[i][j][ksize - 1] += v[i][j];
                    } 
                    if (v[i][j] == LLONG_MIN) {
                        dp[i][j][ksize - 1] = LLONG_MIN;
                    }
                }
            }
            // cout<<ksize;
            // cout<<"的:"<<endl;
            // for(auto i:dp){
            //     for(auto j:i){
            //         cout<<j[0]<<" ";
            //     }cout<<endl;
            // }cout<<"k的:"<<endl;
            // for(auto i:dp){
            //     for(auto j:i){
            //         cout<<j[ksize - 1]<<" ";
            //     }cout<<endl;
            // }
            // for(auto i:v){
            //     for(auto j:i){
            //         cout<<j<<" ";
            //     }cout<<endl;
            // }
            
            if (dp[m - 1][n - 1][ksize - 1] == LLONG_MIN) {
                cout << "Impassable" << endl;
                continue;
            }
            cout << "Passable" << endl;
            cout << dp[m - 1][n - 1][ksize - 1] << endl;
            pair<int, int> p = make_pair(m - 1, n - 1);
            vector<pair<int, int>> path;
            while (pre[p.first][p.second][ksize - 1].first != 0 or pre[p.first][p.second][ksize - 1].second != 0) {
                path.push_back(p);
                p = pre[p.first][p.second][ksize - 1];
            }
            path.push_back(p);
            path.push_back(make_pair(0, 0));
            reverse(path.begin(), path.end());
            cout << path.size() << endl;
            for (auto pa: path) {
                cout << pa.first + 1 << " " << pa.second + 1 << endl;
            }
        }
    }
    return 0;
}
