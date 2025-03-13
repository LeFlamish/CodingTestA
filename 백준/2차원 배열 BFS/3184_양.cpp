#include <iostream>
#include <queue>
#include <string>
using namespace std;
typedef pair<int, int> CD;
#define X first
#define Y second

int R, C, O, V;
string board[250];
bool visited[250][250];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void init() {
	cin >> R >> C;
	for (int y = 0; y < R; y++) {
		cin >> board[y];
	}
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (board[y][x] == 'o') O++;
			else if (board[y][x] == 'v') V++;
			else if (board[y][x] == '#') visited[y][x] = true;
		}
	}
}

void BFS(int x, int y) {
	int cntO = 0, cntV = 0;
	queue<CD> Q;
	visited[y][x] = true;
	Q.push(make_pair(x, y));
	while (!Q.empty()) {
		CD cur = Q.front(); Q.pop();
		if (board[cur.Y][cur.X] == 'o') cntO++;
		else if (board[cur.Y][cur.X] == 'v') cntV++;
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];
			if (nx < 0 || nx >= C || ny < 0 || ny >= R) continue;
			if (visited[ny][nx]) continue;
			visited[ny][nx] = true;
			Q.push(make_pair(nx, ny));
		}
	}
	if (cntO > cntV) cntO = 0;
	else cntV = 0;
	O -= cntO; V -= cntV;
}

void solve() {
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (!visited[y][x]) BFS(x, y);
		}
	}
	cout << O << ' ' << V;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
	return 0;
}
