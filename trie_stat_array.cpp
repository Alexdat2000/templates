#include <iostream>
#include <vector>

using namespace std;

struct node {
    int link[26]{};
    char chr = 0;
    bool term = false;

    node() {
        for (int &i : link)
            i = -1;
    };
};

const int N = 5e5 + 1;
node trie[N];

int fr = 1; // lowest free element of trie

void add_word(string &s) {
    int x = 0;
    for (char ind : s) {
        if (trie[x].link[ind - 'a'] == -1) {
            trie[fr] = node();
            trie[x].link[ind - 'a'] = fr;
            node &b = trie[fr];
            b.chr = ind;
            fr++;
        }
        x = trie[x].link[ind - 'a'];
    }
    trie[x].term = true;
}


signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        add_word(w);
    }

    // solve
    return 0;
}
