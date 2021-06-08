#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;

struct node {
    vector<int> link;
    int suf = -1;
    int ssuf = -1;
    vector <int> term_for;

    node() { link.assign(26, -1); };
};

const int N = 1e6 + 100;
int fre = 1;
node trie[N + 1];
void add(const string& s, int num) {
    int now = 0;
    for (char c : s) {
        if (trie[now].link[c - 'a'] == -1) {
            trie[now].link[c - 'a'] = fre++;
        }
        now = trie[now].link[c - 'a'];
    }
    trie[now].term_for.push_back(num);
}

void build_aho() {
    deque <int> q = {0};

    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        int sf = trie[v].suf;

        if (!trie[sf].term_for.empty()) {
            trie[v].ssuf = trie[v].suf;
        } else {
            trie[v].ssuf = trie[sf].ssuf;
        }

        for (int c = 0; c < 26; c++) {
            if (trie[v].link[c] == -1) {
                trie[v].link[c] = trie[sf].link[c];
            } else {
                q.push_back(trie[v].link[c]);
                trie[trie[v].link[c]].suf = trie[sf].link[c];
            }
        }
    }
}


signed main() {
    for (int i = 0; i < 26; i++) {
        trie[N].link[i] = 0;
    }
    trie[0].suf = N;

    // add words
    build_aho();
    return 0;
}
