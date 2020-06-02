struct matrix {
    long long h{}, w{}; // height, width
    vector<vector<long long>> mat;

    matrix(long long a, long long b) {
        h = a, w = b;
        mat.assign(h, vector<long long>(w, 0));
    }

    matrix(long long n) {
        h = n, w = n;
        mat.assign(h, vector<long long>(w, 0));
        for (long long i = 0; i < n; i++)
            mat[i][i] = 1;
    }

    explicit matrix(const vector<vector<long long>> &x) {
        mat = x;
        h = mat.size();
        w = mat[0].size();
    };

    matrix() = default;
};

matrix operator*(matrix &a, matrix &b) {
    long long h = a.h, w = b.w;
    vector<vector<long long>> c(h, vector<long long>(w, 0));

    for (long long i = 0; i < h; i++)
        for (long long j = 0; j < w; j++)
            for (long long k = 0; k < a.w; k++) {
                c[i][j] = (c[i][j] + (a.mat[i][k] * b.mat[k][j]) % MOD) % MOD;
            }

    return matrix(c);
}

matrix pow(matrix &a, long long n) {
    matrix ans = matrix(a.h);
    if (n == 0) {
        return ans;
    }
    if (n % 2 == 0) {
        ans = pow(a, n / 2);
        ans = ans * ans;
    } else {
        ans = pow(a, n - 1);
        ans = ans * a;
    }
    return ans;
}
