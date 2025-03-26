#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define FOR(i, N) for(int i = 0; i < N; i++)

struct State {
	int x, y;
};

int T, W, H;
string board[1000];
int dist[1000][1000];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
queue<State> fire;
queue<State> human;

void init() {
	memset(dist, 0, sizeof(dist));
	while (!fire.empty()) fire.pop();
	while (!human.empty()) human.pop();
	cin >> W >> H;
	FOR(y, H) {
		cin >> board[y];
		FOR(x, W) {
			if (board[y][x] == '*') fire.push({ x, y });
			else if (board[y][x] == '@') {
				human.push({ x, y });
				dist[y][x] = 1;
			}
		}
	}
}

inline bool OOB(int x, int y) {
	return x < 0 || x >= W || y < 0 || y >= H;
}

void moveFire() {
	int size = fire.size();
	FOR(i, size) {
		State cur = fire.front(); fire.pop();
		FOR(dir, 4) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (board[ny][nx] == '#' || board[ny][nx] == '*') continue;
			board[ny][nx] = '*';
			fire.push({ nx, ny });
		}
	}
}

int moveHuman() {
	int size = human.size();
	FOR(i, size) {
		State cur = human.front(); human.pop();
		FOR(dir, 4) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) return dist[cur.y][cur.x];
			if (dist[ny][nx] || board[ny][nx] == '#' || board[ny][nx] == '*') continue;
			dist[ny][nx] = dist[cur.y][cur.x] + 1;
			human.push({ nx, ny });
		}
	}
	return 0;
}

void solve() {
	while (!human.empty()) {
		moveFire();
		int ret = moveHuman();
		if (ret) {
			cout << ret << '\n';
			return;
		}
	}
	cout << "IMPOSSIBLE\n";
	return;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> T;
	FOR(t, T) {
		init();
		solve();
	}
	return 0;
}
