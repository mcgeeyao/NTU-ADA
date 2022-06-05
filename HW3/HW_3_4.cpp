//union find with node


#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#define print(v)\
for (int i = 0; i < v.size(); i++)\
cout << v[i] << "\n";\
cout << endl;
using namespace std;

long long cn2(long long n) {
    return n * (n - 1) / 2;
};

struct myNode {
    long long val;
    myNode *parent;
    myNode() : val(-1), parent(nullptr) {}
    myNode(long long x) : val(x), parent(nullptr) {}
    myNode(long long x, myNode *parent) : val(x), parent(parent) {}
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q, op, pos;
    long long x, y;
    long long res;
    map<long long, long long>::iterator it;
    set<pair<int, int>>::iterator sit;
    while (cin >> n >> q) {
        map<long long, long long> line; //pos, number
        vector<myNode*> cats(n + 1);
        unordered_map<long long, myNode*> nodelist;

        for (int i = 1; i < n + 1; i++) {
            cin >> pos;
            if (!nodelist[pos]) {
                nodelist[pos] = new myNode(pos);
            }
            line[pos]++;
            cats[i] = nodelist[pos];
        }
        vector<long long> reslist;
        res = 0;
        for (auto i:line) {
            res  +=  cn2(i.second);
        }
        for (int c = 0; c < q; c++) {
            cin >> op >> x >> y;
            if (op - 1) {
                myNode* firstNode = cats[x], * currNode = cats[x];

                while (currNode->val == -1) {
                    currNode = currNode->parent;
                }
                res -= line[currNode->val] - 1;
                line[currNode->val]--;
                if (line[currNode->val] == 0) {
                    line.erase(currNode->val);
                }
                if (nodelist[y]) {
                    cats[x] = nodelist[y];
                    res += line[y];
                    line[y]++;
                } else {
                    nodelist[y] = new myNode(y);
                    cats[x] = nodelist[y];
                    line[y]++;
                }
                reslist.push_back(res);

                while (firstNode->val == -1) {
                    myNode* tmp = firstNode->parent;
                    firstNode->parent = currNode;
                    firstNode = tmp;
                }
            } else {
                myNode* food = new myNode(x);
                long long lost = 0;
                long long get = 0;
                for (it = line.lower_bound(x - y); it != line.end(); it++) {
                    if (it->first > x + y)break;
                    nodelist[it->first]->val = -1;
                    nodelist[it->first]->parent = food;
                    nodelist[it->first] = nullptr;
                    lost += cn2(it->second);
                    get += it->second;
                }
                line.erase(line.lower_bound(x - y), line.upper_bound(x + y));
                if (get) {
                    res -= lost;
                    res += cn2(get);
                    line[x] = get;
                }
                nodelist[x] = food;
                reslist.push_back(res);
            }
        }
        print(reslist)
    }
    return 0;
}