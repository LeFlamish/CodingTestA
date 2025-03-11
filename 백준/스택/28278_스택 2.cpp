#include <iostream>
#include <stack>
using namespace std;
stack<int> S;
int N, order, x;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> order;
        if (order == 1) {
            cin >> x;
            S.push(x);
        }
        else if (order == 2) {
            if (!S.empty()) {
                cout << S.top() << '\n'; S.pop();
            }
            else cout << -1 << '\n';
        }
        else if (order == 3) {
            cout << S.size() << '\n';
        }
        else if (order == 4) {
            if (S.empty()) cout << 1 << '\n';
            else cout << 0 << '\n';
        }
        else {
            if (!S.empty()) cout << S.top() << '\n';
            else cout << -1 << '\n';
        }
    }
    return 0;
}
