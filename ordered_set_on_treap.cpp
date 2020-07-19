#include <iostream>
#include <random>

using namespace std;

random_device rd;

struct node {
    int val = 0, prior = rd(), sz = 1;
    node *left = nullptr;
    node *right = nullptr;

    explicit node(int v_) {
        prior = rd(), val = v_, sz = 1;
        left = nullptr, right = nullptr;
    }

    node() = default;
};

void update(node *t) {
    t->sz = 1;
    if (t->left)
        t->sz += t->left->sz;
    if (t->right)
        t->sz += t->right->sz;
}

int size(node *t) {
    if (t)
        return t->sz;
    else
        return 0;
}

pair<node *, node *> split(node *t, int k) {
    if (t == nullptr)
        return {nullptr, nullptr};

    if (t->val <= k) {
        auto[a, b] = split(t->right, k);
        t->right = a;
        update(t);
        return {t, b};
    } else {
        auto[a, b] = split(t->left, k);
        t->left = b;
        update(t);
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
        update(t1);
        return t1;
    } else {
        t2->left = merge(t1, t2->left);
        update(t2);
        return t2;
    }
}

node *insert(node *root, int v) {
    auto[left, temp] = split(root, v - 1);
    auto[m, right] = split(temp, v);

    if (m != nullptr) {
        return merge(left, merge(m, right));
    }

    node *mid = new node(v);
    return merge(merge(left, mid), right);
}

node *erase(node *root, int v) {
    auto[left, temp] = split(root, v - 1);
    auto[m, right] = split(temp, v);

    return merge(left, right);
}

node *kth_element(node *root, int k) {
    if (!root)
        return root;

    if (size(root->left) > k)
        return kth_element(root->left, k);
    else if (size(root->left) == k)
        return root;
    else
        return kth_element(root->right, k - size(root->left) - 1);
}

int smaller_cnt(node *root, int v) {
    if (!root)
        return 0;

    if (root -> val == v)
        return size(root -> left);
    else if (root -> val > v) {
        return smaller_cnt(root -> left, v);
    } else {
        return size(root -> left) + 1 + smaller_cnt(root -> right, v);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    node *root = nullptr;

    int q;
    cin >> q;
    while (q--) {
        int t, val;
        cin >> t >> val;
        if (t == 1) {
            val *= -1;
            cout << smaller_cnt(root, val) << "\n";
            root = insert(root, val);
        } else {
            int v = kth_element(root, val) -> val;
            root = erase(root, v);
        }
    }
    return 0;
}
