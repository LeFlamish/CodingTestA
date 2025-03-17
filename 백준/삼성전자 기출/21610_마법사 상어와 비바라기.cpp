#include <bits/stdc++.h>
using namespace std;

struct Order {
	int D;
	int S;
};

int N, M;
int board[51][51];
Order order[100];
int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
bool cloud[51][51];
bool tmp[51][51];

void check() {
	cout << "====================\n";
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cout << board[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (cloud[y][x]) cout << "1 ";
			else cout << "0 ";
		}
		cout << '\n';
	}
	cout << "====================\n";
}

void init() {
	cin >> N >> M;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> board[y][x];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> order[i].D >> order[i].S;
	}
	for (int y = N - 1; y <= N; y++) {
		for (int x = 1; x <= 2; x++) {
			cloud[y][x] = true;
		}
	}
}

void moveCloud(int d, int s) {
	memset(tmp, false, sizeof(tmp));
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (cloud[y][x]) {
				int nx = x;
				int ny = y;
				for (int i = 0; i < s; i++) {
					nx += dx[d];
					ny += dy[d];
					if (nx < 1) nx = N;
					else if (nx > N) nx = 1;
					if (ny < 1) ny = N;
					else if (ny > N) ny = 1;
				}
				tmp[ny][nx] = true;
			}
		}
	}
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cloud[y][x] = tmp[y][x];
		}
	}
}

void makeRain() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (cloud[y][x]) board[y][x]++;
		}
	}
}

void waterCopy() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (cloud[y][x]) {
				int cnt = 0;
				for (int dir = 2; dir <= 8; dir += 2) {
					int nx = x + dx[dir];
					int ny = y + dy[dir];
					if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
					if (board[ny][nx] > 0) cnt++;
				}
				board[y][x] += cnt;
			}
		}
	}
	memset(cloud, false, sizeof(cloud));
}

void makeCloud() {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (board[y][x] >= 2 && !tmp[y][x]) {
				cloud[y][x] = true;
				board[y][x] -= 2;
			}
		}
	}
}

void solve() {
	for (int m = 0; m < M; m++) {
		moveCloud(order[m].D, order[m].S);
		makeRain();
		waterCopy();
		makeCloud();
	}
}

int getScore() {
	int ret = 0;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			ret += board[y][x];
		}
	}
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	cout << getScore();
	return 0;
}
