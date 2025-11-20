/**
 * Author: Mahdi Nasser
 * Description:
 * Time:
 */

bool sort_tin(const int& a, const int& b) { return tin[a] < tin[b]; }

vector<int> vtree(const vector<int>& key) {
    if (key.empty()) return {};
    vector<int> res = key;
    sort(res.begin(), res.end(), sort_tin);
    for (int i = 1; i < (int)key.size(); i++) {
        res.push_back(lca(key[i - 1], key[i]));
    }
    sort(res.begin(), res.end(), sort_tin);
    res.erase(unique(res.begin(), res.end()), res.end());
    for (int v : res) {
        vadj[v].clear();
    }
    for (int i = 1; i < (int)res.size(); i++) {
        vadj[lca(res[i - 1], res[i])].push_back(res[i]);
    }
    return res;
}