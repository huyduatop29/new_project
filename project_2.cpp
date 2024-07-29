// huytran
#include <iostream>
#include <climits>
using namespace std;

const int maxN = 100;
const long long MaxLong = 1000000000;

int n;
int a[maxN + 1];
long long F[maxN][maxN];
int T[maxN][maxN];

void Enter() {
    freopen("MULTMAT.INP", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n + 1; ++i) {
        cin >> a[i];
    }
    fclose(stdin);
}

void Optimize() {
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (i == j) {
                F[i][j] = 0;
            } else {
                F[i][j] = MaxLong;
            }
        }
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            for (int k = i; k <= j - 1; ++k) {
                long long p = a[i];
                long long q = a[k + 1];
                long long r = a[j + 1];
                long long x = F[i][k] + F[k + 1][j] + p * q * r;

                if (x < F[i][j]) {
                    F[i][j] = x;
                    T[i][j] = k;
                }
            }
        }
    }
}

void Trace(int i, int j) {
    if (i == j) {
        cout << "M[" << i << "]";
    } else {
        cout << "(";
        int k = T[i][j];
        Trace(i, k);
        cout << " * ";
        Trace(k + 1, j);
        cout << ")";
    }
}

int main() {
    Enter();
    Optimize();
    freopen("MULTMAT.OUT", "w", stdout);
    cout << F[1][n] << endl;
    Trace(1, n);
    fclose(stdout);

    return 0;
}

