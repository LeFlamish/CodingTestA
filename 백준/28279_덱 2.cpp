#include <iostream>
#include <deque>
using namespace std;

int N, order;
deque<int> DQ;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> order;
        if (order == 1) {
            int x;
            cin >> x;
            DQ.push_front(x);
        }
        else if (order == 2) {
            int x;
            cin >> x;
            DQ.push_back(x);
        }
        else if (order == 3) {
            if (DQ.empty()) {
                cout << "-1\n";
                continue;
            }
            cout << DQ.front() << '\n';
            DQ.pop_front();
        }
        else if (order == 4) {
            if (DQ.empty()) {
                cout << "-1\n";
                continue;
            }
            cout << DQ.back() << '\n';
            DQ.pop_back();
        }
        else if (order == 5) {
            cout << DQ.size() << '\n';
        }
        else if (order == 6) {
            if (DQ.empty()) cout << "1\n";
            else cout << "0\n";
        }
        else if (order == 7) {
            if (DQ.empty()) {
                cout << "-1\n";
                continue;
            }
            cout << DQ.front() << '\n';
        }
        else if (order == 8) {
            if (DQ.empty()) {
                cout << "-1\n";
                continue;
            }
            cout << DQ.back() << '\n';
        }
	}
	return 0;
}
