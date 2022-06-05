// monotone queue
// two pointer
// BFS BFS BFS BFS

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#define print(v)\
for  (int i = 0; i < v.size(); i++)\
cout << v[i] << " ";\
cout << endl;
using namespace std;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int v, u, n, x;
    
    while (cin >> n) {
        unordered_map<int, vector<int> > edges;
        for (int i = 0; i < n-1; i++) {
            cin >> u >> v;
            edges[v].push_back(u);
            edges[u].push_back(v);
        }
        
        unordered_set<int> seen;
        vector<int> que;
        vector<int> dist(n);
        
        que.push_back(1);
        dist[0] = 0;
        while (!que.empty()) {
            vector<int> tmp;
            for (auto curr:que) {
                seen.insert(curr);
                for (auto i:edges[curr]) {
                    if (seen.find(i) == seen.end()) {
                        tmp.push_back(i);
                        dist[i-1] = dist[curr - 1] + 1;
                    }
                }
            }
            que = tmp;
        }
        int maxnode = 0;
        int maxdist = 0;
        for (int i = 0; i < n; i++) {
            //cout<<dist[i]<<" ";
            if (dist[i] > maxdist) {
                maxnode = i + 1;
                maxdist = dist[i];
            }
        }
        seen.clear();
        que.clear();
        dist.clear();

        vector<int> path(n);

        que.push_back(maxnode);
        dist[maxnode - 1] = 0;
        path[maxnode - 1] = -1;
        while (!que.empty()) {
            vector<int> tmp;
            for (auto curr:que) {
                seen.insert(curr);
                for (auto i:edges[curr]) {
                    if (seen.find(i) == seen.end()) {
                        path[i - 1] = curr;
                        tmp.push_back(i);
                        dist[i - 1] = dist[curr - 1] + 1;
                    }
                }
            }
            que = tmp;
        }
        maxnode = 0;
        maxdist = 0;
        for (int i = 0; i < n; i++) {
            //cout<<dist[i]<<" ";
            if (dist[i] > maxdist) {
                maxnode = i + 1;
                maxdist = dist[i];
            }
        }
        vector<int> branch;
        vector<int> longest_path;
        int curr = maxnode;
        seen.clear();
        seen.insert(curr);
        dist.clear();
        longest_path.push_back(curr);
        branch.push_back(0);
        while (path[curr - 1] >= 0) {
            curr = path[curr - 1];
            seen.insert(curr);
        }
        curr = maxnode;
        while (path[curr-1] >= 0) {
            curr = path[curr - 1];
            longest_path.push_back(curr);
            seen.insert(curr);
            que.clear();
            que.push_back(curr);

            dist[curr - 1] = 0;
            int m = 0;
            while (!que.empty()) {
                vector<int> tmp;
                for (auto curr1:que) {
                    seen.insert(curr1);
                    for (auto i:edges[curr1]) {
                        if (seen.find(i) == seen.end()) {
                            tmp.push_back(i);
                            dist[i - 1] = dist[curr1 - 1] + 1;
                            m = max(m, dist[i - 1]);
                        }
                    }
                }
                que = tmp;
            }
            branch.push_back(m);
        }
        // print(longest_path)
        // print(branch)
        int pathlen = longest_path.size();

        vector<int> cut_right(pathlen);
        vector<int> cut_right2(pathlen);
        int p = 1;
        int sh = branch[p];

        vector<int> monoq;
        int monoptr = 0;
        monoq.push_back(p);
        for (int i = 1; i < pathlen; i++) {
            while (sh<pathlen - p - 1) {
                p++;
                sh = max(sh + 1, branch[p]);
                while (monoq.size()>monoptr && branch[p] > branch[monoq[monoq.size() - 1]] + p - monoq[monoq.size() - 1]) {
                    monoq.pop_back();
                }
                monoq.push_back(p);
            }
            cut_right[i] = sh;
            cut_right2[i] = sh + pathlen - p - 1;
            if (monoq[monoptr] == i) {
                monoptr++;
                if (i == p) {
                    monoptr--;
                    p++;
                    sh = branch[p];
                } else {
                    sh -= branch[i];
                    sh -= monoq[monoptr] - i;
                    sh += branch[monoq[monoptr]];
                }
                
            }if (i == p) {
                monoptr--;
                p++;
                sh = branch[p];
            }
            

        }
        //print(cut_right)

        vector<int> cut_left(pathlen);
        vector<int> cut_left2(pathlen);
        p = pathlen - 2;
        sh = branch[p];

        monoq.clear();
        monoptr = 0;
        monoq.push_back(p);
        for (int i = pathlen - 2; i >= 0; i--) {
            while (sh < p) {
                p--;
                sh = max(sh + 1, branch[p]);
                while (monoq.size() > monoptr && branch[p] > branch[monoq[monoq.size() -1 ]] - p + monoq[monoq.size() - 1]) {
                    monoq.pop_back();
                }
                monoq.push_back(p);
            }
            cut_left[i] = sh;
            cut_left2[i] = sh + p;
            if (monoq[monoptr] == i) {
                monoptr++;
                if (i == p) {
                    monoptr--;
                    p--;
                    sh = branch[p];
                } else {
                    sh -= branch[i];
                sh -= i - monoq[monoptr];
                sh += branch[monoq[monoptr]];
                }
            }
        }
        //print(cut_left)
        int res = 100000000;
        for (int i = 0; i < pathlen - 1; i++) {
            int tmp = max(cut_right2[i + 1], cut_left2[i]);
            tmp = max(tmp,cut_right[i + 1] + cut_left[i] + 1);
            res = min(res, tmp);
        }
        cout << res;
    }
    return 0;
}