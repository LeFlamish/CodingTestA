#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> PI;
#define X first
#define Y second

int N, M, K, cnt;
int board[100][100];
bool visited[100][100];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
bool used;

void check() {
	cout << "====================\n";
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cout << visited[y][x] << ' ';
		}
		cout << '\n';
	}
	cout << "--------------------\n";
	cout << cnt << '\n';
	cout << "====================\n";
}

void init() {
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> board[y][x];
		}
	}
}

bool OOB(int x, int y) {
	return (x < 0 || x >= N || y < 0 || y >= N);
}

void BFS(int x, int y) {
	queue<PI> Q;
	visited[y][x] = true;
	Q.push({ x, y });
	while (!Q.empty()) {
		PI cur = Q.front(); Q.pop();
		cnt++;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (OOB(nx, ny)) continue;
			if (visited[ny][nx] || board[ny][nx]) continue;
			visited[ny][nx] = true;
			Q.push({ nx, ny });
		}
	}
}

bool solve() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (!visited[y][x] && !board[y][x]) {
				cnt = 0;
				BFS(x, y);
				// check();
				M -= (cnt / K) + (cnt % K != 0 ? 1 : 0);
				used = true;
				if (M < 0) return false;
			}
		}
	}
	return true;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	if (solve() && used) cout << "POSSIBLE\n" << M;
	else cout << "IMPOSSIBLE";
	return 0;
}
