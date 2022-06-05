//kosaraju algorithm
//strongly connected component
//minimum addition edges let DAG to strongly connected


#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <climits>
#define print(v)\
for (int i = 0; i < v.size(); i++)\
cout << v[i] << " ";\
cout << endl;
using namespace std;

void dfs1(vector<vector<int>> &edges, vector<bool> &vis, vector<int> &finishStk, int v) {
    vis[v] = true;
    for (int u:edges[v]) {
        if (!vis[u]) {
            dfs1(edges, vis, finishStk, u);
        }
    }
    finishStk.push_back(v);
};

void dfs2( vector<vector<int>> &edges, vector<bool> &vis, int v, int p, vector<int> &parent) {
    vis[v] = true;
    parent[v] = p;
    for (int u:edges[v]) {
        if (!vis[u]) {
            dfs2(edges, vis, u, p, parent);
        }
    }
};

int dfs3(vector<vector<int>> &edges, vector<bool> &vis, int v, vector<int> &outdeg) {
    vis[v] = true;
    if (outdeg[v] == 0) {
        return v;
    }
    for (int u:edges[v]) {
        int tmp;
        if (!vis[u]) {
            tmp = dfs3(edges, vis, u, outdeg);
            if (tmp) return tmp;
        }
    }
    return 0;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k, m, n, cases, x, y, flag;
    while (cin >> cases >> flag) {
        for (int c = 0; c < cases; c++) {
            cin >> n >> m;
            vector<vector<int>> edges(n + 1, vector<int> ());
            vector<bool> vis1(n + 1, false);
            vector<bool> vis2(n + 1, false);
            vector<vector<int>> redges(n + 1, vector<int> ());
            vector<pair<int, int>> edgelist;
            for (int i = 0; i < m; i++) {
                cin >> x >> y;
                    edges[x].push_back(y);
                    redges[y].push_back(x);
                    edgelist.push_back(make_pair(x, y));
            }
            vector<int> finishStk;
            for (int i = 1; i <= n; i++) {
                if (!vis1[i]) {
                    dfs1(redges, vis1, finishStk, i);
                }
            }
            reverse(finishStk.begin(), finishStk.end());
            vector<int> parent(n + 1);
            vector<int> newnodes;
            for (int i:finishStk) {
                if (!vis2[i]) {
                    dfs2(edges, vis2, i, i, parent);
                    newnodes.push_back(i);
                }
            }
            //print(parent)
            vector<vector<int>> nedges(n + 1, vector<int> ());
            vector<pair<int, int>> nedgelist;
            vector<int>indeg(n + 1);
            vector<int>outdeg(n + 1);
            for (auto [u, v]:edgelist) {
                if (parent[u] != parent[v]) {
                    nedges[parent[u]].push_back(parent[v]);
                    indeg[parent[v]] += 1;
                    outdeg[parent[u]] += 1;
                    nedgelist.push_back(make_pair(parent[u], parent[v]));
                }
            }
            
            vector<int> innodes;
            vector<int> outnodes;
            for (int i:newnodes) {
                if (indeg[i] == 0) {
                    innodes.push_back(i);
                }if (outdeg[i] == 0) {
                    outnodes.push_back(i);
                }
            }
            // print(innodes)
            // print(outnodes)
            if (newnodes.size() == 1) {
                cout << 0 << endl;
            }
            else{
                cout << max(innodes.size(), outnodes.size()) << endl;
                
                if (flag) {
                    if (innodes.size()>outnodes.size()) {

                        vector<vector<int>> rnedges(n + 1, vector<int> ());
                        vector<bool> vis3(n + 1);
                        for (auto [u, v]:nedgelist) {
                            rnedges[v].push_back(u);
                        }

                        int i = 1;
                        vector<bool> left(n + 1, true);
                        vector<int> leftout;
                        int lastin = dfs3(rnedges, vis3, outnodes[0], indeg);
                        while (i < outnodes.size()) {
                            int tmp = dfs3(rnedges, vis3, outnodes[i], indeg);
                            if (tmp) {
                                cout << outnodes[i] << " " << lastin << endl;
                                left[lastin] = false;
                                lastin = tmp;
                            } else {
                                leftout.push_back(outnodes[i]);
                            }
                            i++;
                        }
                        cout << outnodes[0] << " " << lastin << endl;
                        left[lastin] = false;
                        int ind = 0;
                        for (int i:innodes) {
                            if (left[i]) {
                                if (leftout.size() == 0) {
                                    cout << outnodes[0] << " " << i << endl;
                                } else {
                                    cout << leftout[min(ind, (int) leftout.size() - 1)] << " " << i << endl;
                                    ind++;
                                }
                            }
                        }
                    } else {
                        vector<bool> vis3(n + 1);
                        int i = 1;
                        vector<bool> left(n + 1, true);
                        vector<int> leftin;
                        int lastout;
                        lastout = dfs3(nedges, vis3, innodes[0], outdeg);
                        while (i < innodes.size()) {
                            int tmp = dfs3(nedges, vis3, innodes[i], outdeg);
                            if (tmp) {
                                cout << lastout << " " << innodes[i] << endl;
                                left[lastout] = false;
                                lastout = tmp;
                            } else {
                                leftin.push_back(innodes[i]);
                            }
                            i++;
                        }cout << lastout << " " << innodes[0] << endl;
                        left[lastout] = false;
                        int ind = 0;
                        for (int i:outnodes) {
                            if (left[i]) {
                                if (leftin.size() == 0) {
                                    cout << i << " " << innodes[0] << endl;
                                } else {
                                    cout << i << " " << leftin[min(ind, (int) leftin.size() - 1) ] << endl;
                                    ind++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}