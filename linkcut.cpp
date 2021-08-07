#pragma GCC optimize("Ofast,fast-math,unroll-loops,inline,no-stack-protector")

#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;

struct node {
    vector<node *> ch = {nullptr, nullptr};
    node *parent = nullptr;
    int sz = 1;
    bool rev = false;

    node() = default;
};

int sz(node *root) {
    return (root == nullptr ? 0 : root->sz);
}

void push(node *root) {
    if (root == nullptr || !root->rev)
        return;

    for (auto i : root->ch) {
        if (i != nullptr)
            i->rev ^= 1;
    }
    swap(root->ch[0], root->ch[1]);
    root->rev ^= 1;
}

void pull(node *root) {
    if (root == nullptr)
        return;
    root->sz = sz(root->ch[0]) + sz(root->ch[1]) + 1;
}

int find_child(node *target) {
    return target && target->parent && target->parent->ch[1] == target;
}

void connect(node *root, node *child, int num) {
    if (root)
        root->ch[num] = child;
    if (child)
        child->parent = root;
}

bool is_root(node *root) {
    return root == nullptr || root->parent == nullptr || root->parent->ch[find_child(root)] != root;
}

void rotate(node *v) {
    node *parent = v->parent;
    push(parent);
    push(v);
    int num = find_child(v);
    node *u = v->ch[1 - num];
    if (is_root(parent))
        v->parent = parent->parent;
    else
        connect(parent->parent, v, find_child(parent));
    connect(parent, u, num);
    connect(v, parent, 1 - num);
    pull(parent);
    pull(v);
}

void splay(node *v) {
    push(v);
    while (!is_root(v)) {
        if (!is_root(v->parent)) {
            if (find_child(v) == find_child(v->parent))
                rotate(v->parent);
            else
                rotate(v);
        }
        rotate(v);
    }
}

void expose(node *root) {
    splay(root);
    root->ch[1] = nullptr;
    pull(root);

    while (root->parent != nullptr) {
        node *p = root->parent;
        splay(p);
        p->ch[1] = root;
        root->parent = p;
        pull(p);
        splay(root);
    }
}

void make_root(node *root) {
    expose(root);
    root->rev ^= 1;
    push(root);
}

void link(node *a, node *b) {
    make_root(a), make_root(b);
    a->parent = b;
}

void cut(node *a, node *b) {
    make_root(a);
    make_root(b);

    b->ch[find_child(a)] = nullptr;
    a->parent = nullptr;
    pull(b);
}

int get(node *a, node *b) {
    if (a == b)
        return 0;
    make_root(a);
    make_root(b);
    if (a->parent == nullptr)
        return -1;
    return sz(b) - 1;
}


signed main() {
    freopen("linkcut.in", "r", stdin);
    freopen("linkcut.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<node *> root(n);
    for (int i = 0; i < n; i++)
        root[i] = new node();

    for (int i = 0; i < q; i++) {
        string s;
        int a, b;
        cin >> s >> a >> b;
        a--, b--;
        if (s == "get") {
            cout << get(root[a], root[b]) << endl;
        } else if (s == "link") {
            link(root[a], root[b]);
        } else {
            cut(root[a], root[b]);
        }
    }
    return 0;
}