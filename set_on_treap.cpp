#include <iostream>
#include <random>

using namespace std;

random_device rd;

struct node {
    int val = 0, prior = rd();
    node *left = nullptr;
    node *right = nullptr;

    explicit node(int v_) {
        prior = rd(), val = v_;
        left = nullptr, right = nullptr;
    }

    node() = default;
};

pair<node *, node *> split(node *t, int k) {
    if (t == nullptr)
        return {nullptr, nullptr};

    if (t->val <= k) {
        auto[a, b] = split(t->right, k);
        t->right = a;
        return {t, b};
    } else {
        auto[a, b] = split(t->left, k);
        t->left = b;
        return {a, t};
    }
}

node *merge(node *t1, node *t2) {
    if (t2 == nullptr)
        return t1;
    if (t1 == nullptr)
        return t2;

    else if (t1->prior < t2->prior) {
        t1->right = merge(t1->right, t2);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        return t2;
    }
}

node *insert(node *root, int v) {
    auto [left, temp] = split(root, v - 1);
    auto [m, right] = split(temp, v);

    if (m != nullptr) {
        return merge(left, merge(m, right));
    }

    node *mid = new node(v);
    return merge(merge(left, mid), right);
}

node *find(node* root, int v) {
    node *ans = root;
    while (ans != nullptr && ans -> val != v) {
        if (v < ans -> val)
            ans = ans -> left;
        else
            ans = ans -> right;
    }
    return ans;
}

node *erase(node *root, int v) {
    auto [left, temp] = split(root, v - 1);
    auto [m, right] = split(temp, v);

    return merge(left, right);
}

pair <node *, node *> next(node *root, int v) {
    auto [le, gr] = split(root, v);
    node *ans = gr;

    while (true) {
        if (ans != nullptr && ans->left != nullptr)
            ans = ans -> left;
        else
            return {ans, merge(le, gr)};
    }
}

pair <node *, node *> prev(node *root, int v) {
    auto [l, ge] = split(root, v - 1);
    node *ans = l;

    while (true) {
        if (ans != nullptr && ans->right != nullptr)
            ans = ans -> right;
        else
            return {ans, merge(l, ge)};
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string op;
    int val;

    node *root = nullptr;

    while (cin >> op >> val) {
        if (op == "insert") {
            root = insert(root, val);
        } else if (op == "delete") {
            root = erase(root, val);
        } else if (op == "exists") {
            node *ans = find(root, val);
            if (ans == nullptr)
                cout << "false\n";
            else
                cout << "true\n";
        } else if (op == "next") {
            auto [ans, root_] = next(root, val);
            root = root_;
            if (ans == nullptr) {
                cout << "none\n";
            } else {
                cout << ans -> val << "\n";
            }
        } else if (op == "prev") {
            auto [ans, root_]  = prev(root, val);
            root = root_;

            if (ans == nullptr) {
                cout << "none\n";
            } else {
                cout << ans -> val << "\n";
            }
        }
    }
    return 0;
}
