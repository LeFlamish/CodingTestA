#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N;
queue<int> Q;
string command;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> command;

        if (command == "push") {
            int x;
            cin >> x;
            Q.push(x);
        }
        else if (command == "pop") {
            if (Q.empty()) cout << -1 << '\n';
            else {
                cout << Q.front() << '\n';
                Q.pop();
            }
        }
        else if (command == "size") cout << Q.size() << '\n';
        else if (command == "empty") cout << Q.empty() << '\n';
        else if (command == "front") {
            if (Q.empty()) cout << -1 << '\n';
            else cout << Q.front() << '\n';
        }
        else if (command == "back") {
            if (Q.empty()) cout << -1 << '\n';
            else cout << Q.back() << '\n';
        }
    }
    return 0;
}
