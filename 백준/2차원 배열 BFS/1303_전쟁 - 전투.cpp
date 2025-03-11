#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> CD;
#define X first
#define Y second

int N, M, W, B;
string board[100];
bool visited[100][100];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void init() {
	cin >> N >> M;
	for (int y = 0; y < M; y++) {
		cin >> board[y];
	}
}

void BFS(int x, int y) {
	int cnt = 1;
	queue<CD> Q;
	visited[y][x] = true;
	char check = board[y][x];
	Q.push(make_pair(x, y));
	while (!Q.empty()) {
		CD cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (visited[ny][nx] || board[ny][nx] != check) continue;
			visited[ny][nx] = true;
			Q.push(make_pair(nx, ny));
			cnt++;
		}
	}
	if (check == 'W') W += cnt * cnt;
	else B += cnt * cnt;
}

void solve() {
	for (int y = 0; y < M; y++) {
		for (int x = 0; x < N; x++) {
			if (!visited[y][x]) BFS(x, y);
		}
	}
	cout << W << ' ' << B;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
