#include <iostream>
using namespace std;

int player;
int board[4][4];

// 3과 7로 한 이유는 숫자 3개를 더했을 때, 3과 7일 경우 어떠한 경우의 수에서도 겹치는 합이 없기 때문.
void init() {
	cin >> player;
	if (player == 1) player = 3;
	else player = 7;
}

bool check() {
	int flag = 0;
	for (int y = 1; y <= 3; y++) {
		flag = 0;
		for (int x = 1; x <= 3; x++) {
			flag += board[y][x];
		}
		if (flag == 9 || flag == 21) return true;
	}

	for (int x = 1; x <= 3; x++) {
		flag = 0;
		for (int y = 1; y <= 3; y++) {
			flag += board[y][x];
		}
		if (flag == 9 || flag == 21) return true;
	}

	flag = board[1][1] + board[2][2] + board[3][3]; // 2중 for문이 굳이 필요가 없음. 간단하니까.
	if (flag == 9 || flag == 21) return true;

	flag = board[1][3] + board[2][2] + board[3][1]; // 마찬가지로 2중 for문 필요 없음.
	if (flag == 9 || flag == 21) return true;

	return false;
}

void solve() {
	for (int i = 0; i < 9; i++) {
		int x, y;
		cin >> y >> x;
		board[y][x] = player;
		if (check()) {
			if (player == 3) cout << 1;
			else cout << 2;
			return;
		}
		if (player == 3) player = 7;
		else player = 3;
	}
	cout << 0;
}

void debug() {
	for (int y = 1; y <= 3; y++) {
		for (int x = 1; x <= 3; x++) {
			cout << board[y][x] << ' ';
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
