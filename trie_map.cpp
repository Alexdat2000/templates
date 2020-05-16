#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
    map<char, int> link;

    char chr = 0;
    bool term = false;

    node() = default;
};

const int N = 5e5 + 1;
node trie[N];

int fr = 1;

void trie_add(string &s) {
    int x = 0;
    for (char ind : s) {
        if (!trie[x].link.count(ind)) {
            trie[fr] = node();
            trie[x].link[ind] = fr;
            node &b = trie[fr];
            b.chr = ind;
            fr++;
        }
        x = trie[x].link[ind];
    }
    trie[x].term = true;
}


signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        trie_add(w);
    }
    return 0;
}
