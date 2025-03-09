#include <iostream>
using namespace std;

int H, W;
string board[100];

void init() {
	cin >> H >> W;
	for (int h = 0; h < H; h++) {
		cin >> board[h];
	}
}

// 'c'를 만나기 전엔 -1로 ans 2차원 배열에 저장하다가 'c'를 만나면 0으로 초기화하고 이후에 계속 +1를 해주는 식으로 해결하는 것이 효과적.
void solve() {
	for (int h = 0; h < H; h++) {
		for (int w = 0; w < W; w++) {
			if (board[h][w] == 'c') cout << 0 << ' ';
			else {
				bool flag = false;
				for (int x = w - 1; x >= 0; x--) {
					if (board[h][x] == 'c') {
						cout << w - x << ' ';
						flag = true;
						break;
					}
				}
				if (!flag) cout << -1 << ' ';
			}
		}
		cout << '\n';
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
