#include <iostream>

using namespace std;

struct node {
    int y, v, sz;
    node *left;
    node *right;

    explicit node(int v_) {
        y = rand(), v = v_, sz = 1;
        left = nullptr, right = nullptr;
    }

    node() = default;
};

node *update(node *t) {
    t->sz = 1;
    if (t->left)
        t->sz += t->left->sz;
    if (t->right)
        t->sz += t->right->sz;
    return t;
}

pair<node *, node *> split(node *t, int k) {
    if (t == nullptr)
        return {nullptr, nullptr};

    int s = 0;
    if (t->left)
        s += t->left->sz;
    if (s >= k) {
        auto[t1, t2] = split(t->left, k);
        t->left = t2;
        t = update(t);
        return {t1, t};
    } else {
        auto[t1, t2] = split(t->right, k - s - 1);
        t->right = t1;
        t = update(t);
        return {t, t2};
    }
}

node *merge(node *t1, node *t2) {
    if (t2 == nullptr)
        return t1;
    if (t1 == nullptr)
        return t2;

    else if (t1->y < t2->y) {
        t1->right = merge(t1->right, t2);
        update(t1);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        update(t2);
        return t2;
    }
}

node *insert(node *t, int ind, node *a) {
    if (t == nullptr)
        return a;

    if (t->y > a->y) {
        int s = 0;
        if (t->left)
            s += t->left->sz;

        if (s < ind) {
            t->right = insert(t->right, ind - s, a);
        } else {
            t->left = insert(t->left, ind, a);
        }
        update(t);
        return t;
    } else {
        auto[t1, t2] = split(t, ind);
        a->left = t1;
        a->right = t2;
        update(a);
        return a;
    }
}

void cout_dfs(node *t) {
    if (t == nullptr)
        return;
    cout_dfs(t->left);
    cout << t->v + 1 << " ";
    cout_dfs(t->right);
}

signed main() {
    int n, m;
    cin >> n >> m;

    node *t = nullptr;
    for (int i = 0; i < n; i++) {
        node *add = new node(i);
        t = insert(t, i, add);
    }

    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;
        auto[t_, t2] = split(t, b);
        auto[t0, t1] = split(t_, a);
        t = merge(t1, merge(t0, t2));
    }
    cout_dfs(t);
    cout << endl;
    return 0;
}
