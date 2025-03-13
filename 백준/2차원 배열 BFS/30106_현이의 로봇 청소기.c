#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
typedef pair<int, int> PI;
#define X first
#define Y second

int N, M, K, ret;
int board[500][500];
bool visited[500][500];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void init() {
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> board[y][x];
		}
	}
}

bool OOB(int x, int y) {
	return (x < 0 || x >= M || y < 0 || y >= N);
}

void BFS(int x, int y) {
	queue<PI> Q;
	visited[y][x] = true;
	Q.push({ x, y });
	while (!Q.empty()) {
		PI cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || abs(board[cur.Y][cur.X] - board[ny][nx]) > K) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
	ret++;
}

void solve() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (!visited[y][x]) BFS(x, y);
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	cout << ret;
	return 0;
}
