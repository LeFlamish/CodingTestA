#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct State {
	int x, y;
};

const int SIZE = 502;
int N, M, ret, total;
int board[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0 ,-1 };

void init() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> board[y][x];
		}
	}
}

inline bool OOB(int x, int y) {
	return x < 0 || x >= M || y < 0 || y >= N;
}

int BFS(int x, int y) {
	int cnt = 0;
	queue<State> Q;
	visited[y][x] = true;
	Q.push({ x, y });
	while (!Q.empty()) {
		State cur = Q.front(); Q.pop();
		cnt++;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || !board[ny][nx]) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
	return cnt;
}

void solve() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (board[y][x] && !visited[y][x]) {
				total++;
				ret = max(BFS(x, y), ret);
			}
		}
	}
	cout << total << '\n' << ret;
}

int main(void) {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
